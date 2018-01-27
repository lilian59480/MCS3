/**
 * \file client.c
 */
#include "client.h"

/**
 * Main Client
 * \param argc Le nombre d'arguments
 * \param argv Les arguments
 * \retval int La valeur de sortie du programme
 */
int main (int argc, char** argv)
{
    // Les informations sur le serveur, afin de le contacter
    struct sockaddr_in* addr_serveur;
    // Si je n'ai pas les bons arguments, j'arrete en donnant une information sur comment utiliser le programme
    if (argc != 3)
    {
        fprintf (stderr, "Utilisation :\n\t%s @IP PORT\n", argv[0]);
        exit (2);
    }
    else
    {
        int port;
        CHECK(port = strtol(argv[2],NULL,10),"ERREUR STRTOL");
        CHECK_NULL(addr_serveur = sockaddrinit(argv[1],port),"ERREUR SOADDRINIT");
    }

    // La socket utilisé par le client
    T_Socket client;
    // On dit que notre socket est une socket INET (Internet) et qui fonctionne en mode STREAM
    client = soinit();
    // Vu qu'on est en STREAM, il faut qu'on se connecte au serveur avec les infos mises au dessus
    CHECK (connect (client, (struct sockaddr*) addr_serveur, sizeof (struct sockaddr_in) ), "ERREUR CONNECT");
    // On fait notre dialogue avec le client
    
    // On ferme le socket comme on en a plus besoin
    close (client);
    sockaddrfree(addr_serveur);
    return 0;
}
