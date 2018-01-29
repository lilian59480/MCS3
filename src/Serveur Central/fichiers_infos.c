/**
 * \file fichiers_infos.c
 */
#include "fichiers_infos.h"

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

T_Info_Joueur get_info_joueur (T_Infos_Joueurs infos, int position)
{
    lire_fichier_infos_joueurs (infos);
    return infos[position];
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

