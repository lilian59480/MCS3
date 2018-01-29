/**
 * \file fichiers_infos.c
 */
#include "fichiers_infos.h"

volatile sig_atomic_t stop_serveur;

/**
 * Traitement des signaux par déroutage
 * \param signal Le signal qu'on va traiter
 */
void deroute_serveur (int signal)
{
    int status;
    pid_t pidchld;

    switch (signal)
    {
        case SIGCHLD:
            // On va récupérer le status renvoyé par wait, ainsi que le PID du fils
            pidchld = wait (&status);
            fprintf (stderr, "Le processus de service [PID:%d] vient de se terminer sur le signal SIGCHLD(%d) avec le status : %d\n", pidchld, signal, status);
            break;

        case SIGINT:
            fprintf (stderr, "SIGINT : Fermeture du serveur\n");
            CHECK (kill (0, SIGUSR1), "ERREUR KILL");
            sleep (5);
            stop_serveur = !stop_serveur;
            break;
    }
}

/**
 * Traitement des signaux par déroutage
 * \param signal Le signal qu'on va traiter
 */
void deroute_clients (int signal)
{
    switch (signal)
    {
        case SIGUSR1:
            exit (1);
            break;
    }
}

void traiter_requete_ping (T_Socket socket)
{
    T_Reponse reponse;
    reponse = crearep_pong();
    writerep (socket, reponse);
    return;
}

void envoyer_requete_invalide (T_Socket socket)
{
    T_Reponse reponse;
    reponse = crearep_requete_invalide();
    writerep (socket, reponse);
    return;
}

void lire_fichier_infos_joueurs (T_Infos_Joueurs infos)
{
    FILE* fichier;
    memset (infos, 0, sizeof (T_Infos_Joueurs) );
    CHECK_NULL (fichier = fopen ("joueurs.dat", "r"), "ERREUR FOPEN");
    fread (infos, sizeof (T_Infos_Joueurs), 1, fichier);

    if (ferror (fichier) )
    {
        exit (-1);
    }

    fclose (fichier);
}

void ecrire_fichier_infos_joueurs (T_Infos_Joueurs infos)
{
    FILE* fichier;
    sem_t* mutex;
    // On a besoin de tester la sémaphore
    CHECK_SEMFAILED (mutex = sem_open (MUTEX_ECRITURE_FICHIER, 0), "ERREUR SEM_OPEN");
    CHECK (sem_wait (mutex), "ERREUR SEM_WAIT");
    {
        CHECK_NULL (fichier = fopen ("joueurs.dat", "w"), "ERREUR FOPEN");
        int l = fwrite (infos, sizeof (T_Infos_Joueurs), 1, fichier);
        printf ("%d\n", l);

        if (ferror (fichier) )
        {
            exit (-1);
        }
    }
    CHECK (sem_post (mutex), "ERREUR SEM_POST");
    fclose (fichier);
}

void modifier_info_joueur (T_Infos_Joueurs infos, T_Info_Joueur data, int position)
{
    lire_fichier_infos_joueurs (infos);
    infos[position] = data;
    ecrire_fichier_infos_joueurs (infos);
}

int position_libre_fichier_infos_joueurs (T_Infos_Joueurs infos)
{
    int pos;

    for (pos = 0; pos < NBR_CLIENTS_MAX; pos++)
    {
        T_Info_Joueur elt = infos[pos];

        if (strcmp (elt.pseudo, "") == 0)
        {
            return pos;
        }
    }

    return -1;
}
/**
 * Représente la logique du dialogue pour le serveur central
 * \param socket_dialogue La socket de dialogue
 */
void dialogue_serveur (T_Socket socket_dialogue, struct sockaddr_in addr_client)
{
    // Le flag, pour couper la connexion
    char flag = 0;
    // Les informations sur les clients
    T_Infos_Joueurs informations;
    // La position du client dans le tableau d'informations
    int position_client = -1;
    // Première lecture du fichier afin de voir les etats
    lire_fichier_infos_joueurs (informations);
    ecrire_fichier_infos_joueurs (informations);

    // Tant qu'on a pas eu la requete de coupure
    while (!flag)
    {
        // Une requete sous forme de structure
        T_Requete requete;
        // On va lire la requete envoyé par le client
        requete = readreq (socket_dialogue);
        printf ("[%s] Nouvelle requete\n", inet_ntoa (addr_client.sin_addr) );

        // On parcours la liste des requetes qu'on connait
        switch (requete.identifiant)
        {
            case REQ_CODE_PING:
                traiter_requete_ping (socket_dialogue);
                break;

            case REQ_CODE_CONNEXION_SERVEUR_CENTRAL:
                if (position_client == -1)
                {
                }
                else
                {
                    // Deja connecté, on envoie une erreur
                    envoyer_requete_invalide (socket_dialogue);
                }

                break;

            case REQ_CODE_NOMBRE_CLIENTS_CONNECTES:
                break;

            case REQ_CODE_INFORMATION_CLIENT:
                break;

            case REQ_CODE_PASSER_MODE_PARTIE:
                if (position_client != -1)
                {
                    // Ok
                }
                else
                {
                    // Pas connecté, on envoie une erreur
                    envoyer_requete_invalide (socket_dialogue);
                }

                break;

            case REQ_CODE_PORT_CHAT:
                if (position_client != -1)
                {
                    // Ok
                }
                else
                {
                    // Pas connecté, on envoie une erreur
                    envoyer_requete_invalide (socket_dialogue);
                }

                break;

            case REQ_CODE_CHOIX_JOUEUR:
                if (position_client != -1)
                {
                    // Ok
                }
                else
                {
                    // Pas connecté, on envoie une erreur
                    envoyer_requete_invalide (socket_dialogue);
                }

                break;

            case REQ_CODE_DEMANDE_PARTIE:
            case REQ_CODE_QUESTION:
            case REQ_CODE_VALIDER_REPONSE:
            case REQ_CODE_MESSAGE_CHAT:
                envoyer_requete_invalide (socket_dialogue);
                break;

            case REQ_CODE_DECONNEXION:
            default:
                flag = !flag;
                break;
        }
    }
}

/**
 * Main Serveur
 * \retval int La valeur de sortie du programme
 */
int main()
{
    // La socket utilisé par le serveur
    T_Socket serveur;
    // La structure de l'adresse de notre serveur
    struct sockaddr_in* addr_serveur;
    // On prépare notre adresse
    addr_serveur = sockaddrinit_serv (5000);
    // On initialise une socket
    serveur = soinit();
    // On va demander a la machine de nous assigner ce qu'on a demandé
    CHECK (bind (serveur, (struct sockaddr*) addr_serveur, sizeof (struct sockaddr) ), "ERREUR BIND");
    // On va dérouter les signaux SIG_CHLD afin d'éviter la création de processus zombies
    handle_signal (SIGCHLD, deroute_serveur, SA_RESTART);
    handle_signal (SIGINT, deroute_serveur, 0);
    handle_signal (SIGUSR1, SIG_IGN, 0);
    // On ouvre nos sémaphores
    sem_t* mutex;
    CHECK_SEMFAILED (mutex = sem_open (MUTEX_ECRITURE_FICHIER, O_CREAT | O_EXCL, 0644, 1), "ERREUR SEM_OPEN");
    // On va se mettre en mode écoute, afin d'etre pret a recevoir les demandes de connect
    CHECK (listen (serveur, NBR_CLIENTS_MAX), "ERREUR LISTEN")
    stop_serveur = FALSE;

    // On écoute a présent
    while (!stop_serveur)
    {
        // On va creer une socket afin de creer un canal de communication entre ce client et le serveur
        T_Socket socket_dialogue;
        // Les informations sur le client
        struct sockaddr_in addr_client;
        // Le pid du père/fils
        pid_t pid;
        // Utilisé plus tard
        socklen_t taille = sizeof (struct sockaddr_in);
        // On attends d'accepter un client, et on récupére qui il est
        CHECK_NOEINTR ( (socket_dialogue = accept (serveur, (struct sockaddr*) &addr_client, &taille) ), "ERREUR ACCEPT");

        if (!stop_serveur)
        {
            // On va creer cloner le processus afin que notre fils s'occupe du client et
            // Que le père va pouvoir continuer a ecouter d'autre clients
            CHECK (pid = fork(), "ERREUR FORK")
            // Je suis le fils, je m'occupe de faire le dialogue avec le client

            if (pid == 0)
            {
                handle_signal (SIGUSR1, deroute_clients, 0);
                handle_signal (SIGINT, SIG_IGN, 0);
                // Le fils n'a pas besoin de la socket d'écoute
                close (serveur);
                // On effectue le dialogue
                dialogue_serveur (socket_dialogue, addr_client);
                // On ferme la socket de dialogue
                close (socket_dialogue);
                // OBLIGATOIRE, SINON IL RISQUE D'AVOIR DES PROBLEMES
                // TOURJOURS EXIT
                exit (0);
            }
        }

        // Je suis le père, je n'ai rien d'autre a faire, je vais continuer d'attendre d'autre clients
    }

    // Il faut fermer les sockets avec close dès qu'on en a plus besoin
    close (serveur);
    sockaddrfree (addr_serveur);
    return 0;
}

