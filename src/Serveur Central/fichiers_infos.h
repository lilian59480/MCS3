/**
 * \file fichiers_infos.h
 */
#ifndef H_SERVEUR_CENTRAL_FICHIER_INFOS
#define H_SERVEUR_CENTRAL_FICHIER_INFOS

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

// Includes locaux
#include "../Utilitaires/utils.h"
#include "common.h"

void lire_fichier_infos_joueurs (T_Infos_Joueurs infos);
void ecrire_fichier_infos_joueurs (T_Infos_Joueurs infos);
void modifier_info_joueur (T_Infos_Joueurs infos, T_Info_Joueur data, int position);
T_Info_Joueur get_info_joueur (T_Infos_Joueurs infos, int position);
int position_libre_fichier_infos_joueurs (T_Infos_Joueurs infos);



#endif

