/**
 * \file main.h
 */
#ifndef H_MAIN
#define H_MAIN

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
#include <signal.h>
#include <sys/wait.h>

#include <ncurses.h>
#include <cdk/cdk.h>

// Includes locaux
#include "Protocole/Requetes/requetes.h"
#include "Protocole/Reponses/reponses.h"

// Macros
/** Permet d'utiliser la valeur FALSE au lieu de 0 */
#define FALSE 0
/** Permet d'utiliser la valeur TRUE au lieu de 1 */
#define TRUE 1

/** Ce test permet d'afficher les erreurs pour les appels systèmes qui aurai échoué
 * \param statement Le statement a tester
 * \param mess Le message d'erreur a afficher
 */
#define CHECK(statement,mess) if ((statement)<0) { perror(mess); exit(errno); }

/** \mainpage Compte rendu et description du protocole
 *
 * \section compterendu_sec Compte Rendu
 *
 * L'objectif est de faire communiquer un client et un serveur a travers les sockets
 * connectées en mode STREAM (TCP).\n
 * Le serveur est chargé de répondre a plusieurs types de requetes pouvant etre
 * demandée par un client.\n
 * Le protocole mis en place est expliqué en détail en dessous.
 *
 * \section protocole_sec Protocole
 *
 * Le protocole pour cet application se forme de la manière suivante : \n
 *
 * |Code d'identification de la requete|Separateur|   Parametres  |Terminal|
 * |-----------------------------------| ---------|---------------|--------|
 * | Ne peut contenir que des chiffres |    :     |Non obligatoire|   \\0  |
 *
 * \subsection requete_sec Requetes
 *
 * Voici le tableau representant les requetes possibles :
 *
 * |Numero de la requete|Parametres|Description|
 * |--------------------|----------|-----------|
 * | 0 |      |Termine la connexion|
 * |100|      |Demande le nombre d'elements du tableau|
 * |200|Indice|Recupere s'il existe l'element du tableau à l'index spécifié en parametre|
 *
 * \subsection reponse_sec Reponses
 *
 * Voici le tableau representant les reponses possibles :
 *
 * |Numero de la reponse|Parametres|Description|
 * |--------------------|----------|-----------|
 * |100|Indice|Retourne le nombre d'elements contenu dans le tableau serveur|
 * |200|Phrase|Retourne la phrase dans les parametres|
 * |250|      |Out of Range, l'element demandé n'existe pas|
 */

#endif
