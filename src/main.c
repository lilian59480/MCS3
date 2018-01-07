/**
 * \file main.c
 */
#include "main.h"

int main2()
{
    int i;
    char* requeteTest = "REQUETE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    T_Requete requete;
    strtoreq (&requete, requeteTest);
    printf ("%d\n", requete.identifiant);

    for (i = 0; i < requete.nbr_parametres - 1; i += 1)
    {
        printf ("*%s*\n", requete.parametres[i].nom);
        printf ("*%s*\n", requete.parametres[i].valeur);
    }

    char buffer[1000];
    reqtostr (buffer, requete);
    printf ("--%s--", buffer);

    if (strcmp (requeteTest, buffer) != 0)
    {
        printf ("Erreur potentielle\n");
    }

    return 0;
}

int main()
{
    int i;
    char* reponseTest = "REPONSE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    T_Reponse reponse;
    strtorep (&reponse, reponseTest);
    printf ("%d\n", reponse.identifiant);

    for (i = 0; i < reponse.nbr_parametres - 1; i += 1)
    {
        printf ("*%s*\n", reponse.parametres[i].nom);
        printf ("*%s*\n", reponse.parametres[i].valeur);
    }

    char buffer[1000];
    reptostr (buffer, reponse);
    printf ("--%s--", buffer);

    if (strcmp (reponseTest, buffer) != 0)
    {
        printf ("Erreur potentielle\n");
    }

    main2();
}


