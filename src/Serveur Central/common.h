/**
 * \file common.h
 */
#ifndef H_SERVEUR_CENTRAL_COMMON
#define H_SERVEUR_CENTRAL_COMMON

// Includes systèmes

// Includes locaux
#include "../Protocole/protocole.h"

/** Nombre maximum de clients autorisé par le serveur */
#define NBR_CLIENTS_MAX 60

#define MUTEX_ECRITURE_FICHIER "/mutex-fichier-info"

typedef enum
{
    DISPONIBLE,
    EN_PARTIE,
} T_Etat_Joueur;

typedef struct
{
    char pseudo[TAILLE_PARAM_MAX - 1];
    unsigned int port;
    T_Etat_Joueur etat_joueur;
} T_Info_Joueur;

typedef T_Info_Joueur T_Infos_Joueurs[NBR_CLIENTS_MAX];

#endif

