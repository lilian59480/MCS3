/**
 * \file reseau.c
 */

#include "reseau.h"

T_Socket soinit()
{
    return socket ( AF_INET, SOCK_STREAM, 0 );
}

struct sockaddr_in* sockaddrinit (const char* adresse, const int port)
{
    struct sockaddr_in* as;
    struct hostent* hote;
    as = (struct sockaddr_in*) malloc (sizeof (struct sockaddr_in) );

    if (as == NULL)
    {
        return NULL;
    }

    hote = gethostbyname (adresse);

    if (hote == NULL)
    {
        herror ("ERREUR GETHOSTBYNAME");
        sockaddrfree (as);
        return NULL;
    }

    memset (as, 0, sizeof (struct sockaddr_in) );
    as->sin_family = AF_INET;
    as->sin_port = htons (port);
    as->sin_addr = * ( (struct in_addr*) hote->h_addr);
    memset ( as->sin_zero, 0, 8 );
    return as;
}

void sockaddrfree (struct sockaddr_in* socketaddr)
{
    free (socketaddr);
}

long int writereq (const T_Socket socket, const T_Requete requete)
{
    T_Buffer buffer;
    long int length;
    reqtostr (buffer, requete);
    // On va envoyer une réponse
    CHECK ( length = write (socket, buffer, strlen (buffer) + 1), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

long int writerep (const T_Socket socket, const T_Reponse reponse)
{
    T_Buffer buffer;
    long int length;
    reptostr (buffer, reponse);
    // On va envoyer une réponse
    CHECK ( length = write (socket, buffer, strlen (buffer) + 1), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

T_Requete readreq (const T_Socket socket)
{
    T_Buffer buffer;
    T_Requete requete;
    long int length;
    CHECK (length = read (socket, buffer, BUFF_MAX), "ERREUR READ");
    // On va transformer notre buffer en une structure de type T_Requete
    strtoreq (&requete, buffer);
    return requete;
}

T_Reponse readrep (const T_Socket socket)
{
    T_Buffer buffer;
    T_Reponse reponse;
    long int length;
    CHECK (length = read (socket, buffer, BUFF_MAX), "ERREUR READ");
    // On va transformer notre buffer en une structure de type T_Requete
    strtorep (&reponse, buffer);
    return reponse;
}


