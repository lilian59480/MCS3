/**
 * \file requetes.h
 */
#ifndef H_PROTOCOLE_REQUETES
#define H_PROTOCOLE_REQUETES

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Includes locaux
#include "../protocole.h"


/** Défini la structure d'un parametre */
typedef struct
{
    char nom[TAILLE_PARAM_MAX]; ///< L'identifiant du parametre
    char valeur[TAILLE_PARAM_MAX]; ///< La valeur possible
} T_Requete_parametre;

/** Defini une réponse émise par le serveur */
typedef struct
{
    int identifiant; ///< Le numéro de la reponse, qui l'identifie
    int nbr_parametres; ///< Le nombre de parametres dans notre tableau de parametres
    T_Requete_parametre parametres[NBR_PARAM_MAX]; ///< Représente les parametres afin de completer les reponses
} T_Requete;

void reqtostr (char* str, const T_Requete requete);
void strtoreq (T_Requete* requete, const char* str);

#endif
