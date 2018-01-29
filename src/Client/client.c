/**
 * \file client.c
 */
#include "client.h"

CDKSCREEN* screen;


/**
 * fonction traitant les signaux reçus
 * \param signal signal reçu
 */
void deroute (int signal)
{
    switch (signal)
    {
        case SIGINT:
            destroyCDKScreen (screen);
            endCDK();
            endwin();
            exit (1);
            break;
    }
}

/**
 * fonction d'un thread traitant une requête ping
 * \param args argument
 */
void* thread_ping (void* args)
{
    T_Socket* socket_addr = args;
    T_Socket socket = *socket_addr;
    int error = 0;
    unsigned long start_time = 0;
    unsigned long end_time = 0;

    while (!error)
    {
        T_Requete requete_ping;
        T_Reponse reponse_pong;
        requete_ping = creareq_ping();
        printf ("[PING] Nouvelle mesure\n");
        // Debut de la mesure du temps
        start_time = get_clock_time();
        writereq (socket, requete_ping);
        printf ("[PING] Requete envoye\n");
        reponse_pong = readrep (socket);

        if (reponse_pong.identifiant == REP_CODE_PONG)
        {
            // Fin de la mesure du temps
            end_time = get_clock_time();
            float ping_time = ( (float) (end_time - start_time) ) / 1000.0;
            printf ("[PING] Temps: %4.2fms\n", ping_time);
        }

        sleep (10);
    }

    pthread_exit (NULL);
}

/**
 * fonction d'envoi d'une requête de deconnexion
 * \param socket socket de liaison vers le serveur
 */
void deconnexion_serveur (T_Socket socket)
{
    T_Requete requete_deconnexion;
    requete_deconnexion = creareq_deconnexion (socket);
    writereq (socket, requete_deconnexion);
}


/**
 * fonction d'envoi d'une requete de connexion
 * \param socket socket de liaison vers le serveur
 */
void connexion_serveur (T_Socket socket)
{
    while (0)
    {
        int a = socket;
        printf ("%d", a);
    }
}

/**
 * fonction de gestion d'un thread de ping
 * \param socket socket de liaison vers le serveur
 */
void dialogue_serveur (T_Socket socket)
{
    // Démarrage du thread des pings, afin de tester la connexion
    pthread_t thread_pingt;
    CHECK (pthread_create (&thread_pingt, NULL, thread_ping, &socket), "ERREUR PTHREAD_CREATE");
    //while(1) {
    sleep (15);
    deconnexion_serveur (socket);
    //}
}

void lister_clients()
{
}

/**
 * fonction gérant l'initialisation du serveur
 */
void init_connexion_serveur()
{
    // Parametres pour la connexion au serveur
    char hote[MCS_CONNEXION_HOTE_MAX + 1];
    int port = 0;
    char pseudo[MCS_CONNEXION_PSEUDO_MAX + 1];
    // Valeurs récupérées par les saisies
    char* hote_input;
    char* port_input;
    char* pseudo_input;
    // Les informations sur le serveur
    struct sockaddr_in* addr_serveur;
    // La socket utilisé par le client
    T_Socket client;
    client = soinit();
    // Les champs de saisies
    CDKENTRY* hote_entry;
    CDKENTRY* port_entry;
    CDKENTRY* pseudo_entry;
    // Le flag
    char ready = 0;
    // On nettoye les chaines
    cleanChar (hote, MCS_CONNEXION_HOTE_MAX + 1, 0);
    cleanChar (pseudo, MCS_CONNEXION_PSEUDO_MAX + 1, 0);
    // Le champ de saisie de l'hote
    hote_entry = newCDKEntry (screen, CENTER, 5,
                              "<C>Connexion",
                              " </B>Hote:  ",
                              A_NORMAL, ' ', vMIXED,
                              MCS_CONNEXION_TAILLE_CHAMPS,
                              MCS_CONNEXION_HOTE_MIN,
                              MCS_CONNEXION_HOTE_MAX,
                              TRUE, FALSE);
    // Le champ de saisie du port
    port_entry = newCDKEntry (screen, CENTER, 9,
                              NULL,
                              " </B>Port:  ",
                              A_NORMAL, ' ', vINT,
                              MCS_CONNEXION_TAILLE_CHAMPS,
                              MCS_CONNEXION_PORT_MIN,
                              MCS_CONNEXION_PORT_MAX,
                              TRUE, FALSE);
    // Le champ de saisie du pseudo
    pseudo_entry = newCDKEntry (screen, CENTER, 12,
                                NULL,
                                "</B>Pseudo: ",
                                A_NORMAL, ' ', vMIXED,
                                MCS_CONNEXION_TAILLE_CHAMPS,
                                MCS_CONNEXION_PSEUDO_MIN,
                                MCS_CONNEXION_PSEUDO_MAX,
                                TRUE, FALSE);

    // Tant qu'on a pas reussi a se connecter
    while (!ready)
    {
        // On affiche les champs
        drawCDKEntry (hote_entry, FALSE);
        drawCDKEntry (port_entry, TRUE);
        drawCDKEntry (pseudo_entry, TRUE);
        // On active les champs et on récupére leur valeurs
        hote_input = copyChar (activateCDKEntry (hote_entry, FALSE) );
        port_input = copyChar (activateCDKEntry (port_entry, FALSE) );
        pseudo_input = copyChar (activateCDKEntry (pseudo_entry, FALSE) );
        // On efface les champs de saisies
        eraseCDKEntry (hote_entry);
        eraseCDKEntry (port_entry);
        eraseCDKEntry (pseudo_entry);

        // Si aucune valeur n'est invalide
        if (hote_input != NULL && port_input != NULL && pseudo_input != NULL)
        {
            // On affiche le message qu'on essaye de se connecter
            const char* mesg[2];
            mesg[0] = "<C></U/B>Connexion en cours";
            mesg[1] = "<C>Veuillez patienter";
            CDKLABEL* connexion_label;
            connexion_label = newCDKLabel (screen, CENTER, CENTER,
                                           (CDK_CSTRING2) mesg, 2,
                                           TRUE, FALSE);
            drawCDKLabel (connexion_label, TRUE);
            // On copie les parametres
            strcpy (hote, hote_input);
            port = strtol (port_input, NULL, 10);
            strcpy (pseudo, pseudo_input);
            // On met en place les valeurs
            addr_serveur = sockaddrinit (hote, port);

            // Si on arrive a utiliser les parametres
            if (addr_serveur != NULL)
            {
                // On essaye de se connecter
                int status = connect (client, (struct sockaddr*) addr_serveur, sizeof (struct sockaddr_in) );

                // Si tout va bien, on continue
                if (status == 0)
                {
                    // On essaye de se connecter avec une requete
                    T_Requete requete_connexion;
                    requete_connexion = creareq_connexion_serveur_central (pseudo);
                    writereq (client, requete_connexion);
                    // On va voir si on a reçu une erreur ou pas
                    T_Reponse reponse;
                    reponse = readrep (client);

                    if (reponse.identifiant != REP_CODE_ACQUITTEMENT)
                    {
                        // Tout est bon, on va pouvoir avancer
                        ready = !ready;
                    }
                }
            }

            // On efface le message
            eraseCDKLabel (connexion_label);
        }

        // On nettoie
        freeChar (hote_input);
        freeChar (port_input);
        freeChar (pseudo_input);
    }

    // On redessine tous les elements dessines
    refreshCDKScreen (screen);
    // On poursuit le fonctionnement de l'application
    lister_clients (client);
    // On ferme le tout
    close (client);
    sockaddrfree (addr_serveur);
}


/**
 * Main Client
 * \param argc Le nombre d'arguments
 * \param argv Les arguments
 * \retval int La valeur de sortie du programme
 */
int main (int argc, char** argv)
{
    CDK_PARAMS params;
    handle_signal (SIGINT, deroute, 0);
    initscr();
    screen = initCDKScreen (stdscr);
    CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);
    initCDKColor();
    init_connexion_serveur();
    destroyCDKScreen (screen);
    endCDK();
    endwin();
    return EXIT_SUCCESS;
}
