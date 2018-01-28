/**
 * \file client.h
 */
#ifndef H_CLIENT_CLIENT
#define H_CLIENT_CLIENT

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <wait.h>
#include <pthread.h>
#include <ncurses.h>
#include <cdk/cdk.h>


// Includes locaux
#include "../Protocole/protocole.h"
#include "../Protocole/Reponses/reponses.h"
#include "../Protocole/Requetes/requetes.h"
#include "../Reseau/reseau.h"
#include "../Utilitaires/utils.h"
#include "../Utilitaires/signaux.h"
#include "../Utilitaires/clock.h"

#define MCS_CONNEXION_TAILLE_CHAMPS 30

#define MCS_CONNEXION_HOTE_MIN 2
#define MCS_CONNEXION_PORT_MIN 2
#define MCS_CONNEXION_PSEUDO_MIN 2

#define MCS_CONNEXION_HOTE_MAX 30
#define MCS_CONNEXION_PORT_MAX 5
#define MCS_CONNEXION_PSEUDO_MAX 30

extern CDKSCREEN* screen;

#endif

