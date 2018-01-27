/**
 * \file serveur_central.c
 */
#include "serveur_central.h"

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
            fprintf(stderr,"SIGINT : Fermeture du serveur\n");
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
        case SIGINT:
            exit(1);
            break;
    }
}

/**
 * Représente la logique du dialogue pour le serveur central
 * \param socket_dialogue La socket de dialogue
 */
void dialogue_serveur (T_Socket socket_dialogue)
{
    // Le flag, pour couper la connexion
    char flag = 0;

    // Tant qu'on a pas eu la requete de coupure
    while (!flag)
    {
        // Une requete sous forme de structure
        T_Requete requete;
        // On va lire la requete envoyé par le client
        requete = readreq (socket_dialogue);

        // On parcours la liste des requetes qu'on connait
        switch (requete.identifiant)
        {
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
            // On affiche l'adresse du client
            printf ("Par %s\n", inet_ntoa (addr_client.sin_addr) );
            // On va creer cloner le processus afin que notre fils s'occupe du client et
            // Que le père va pouvoir continuer a ecouter d'autre clients
            CHECK (pid = fork(), "ERREUR FORK")
            // Je suis le fils, je m'occupe de faire le dialogue avec le client

            if (pid == 0)
            {
                handle_signal (SIGINT, deroute_clients, 0);
                // Le fils n'a pas besoin de la socket d'écoute
                close (serveur);
                // On effectue le dialogue
                dialogue_serveur (socket_dialogue);
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
    sockaddrfree(addr_serveur);
    return 0;
}
