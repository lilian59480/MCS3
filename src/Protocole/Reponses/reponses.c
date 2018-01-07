/**
 * \file reponses.h
 */

#include "reponses.h"

/**
 * Transforme une reponse en chaine de caractéres
 * \param[out] str La chaine de caractéres obtenu
 * \param[in] reponse La reponse a transformer
 */
void reptostr (char* str, const T_Reponse reponse)
{
    int i;
    // On met l'indentifiant de reponse
    sprintf (str, "REPONSE %d\n", reponse.identifiant);

    // On ajoute les parametres
    for (i = 0; i < reponse.nbr_parametres; i += 1)
    {
        char parametre[TAILLE_PARAM_MAX * 2];
        char valeur[TAILLE_PARAM_MAX];
        strncpy (valeur, reponse.parametres[i].valeur, TAILLE_PARAM_MAX - 1);
        strnltocr (valeur);
        sprintf (parametre, "%s:%s\n", reponse.parametres[i].nom, valeur);
        strcat (str, parametre);
    }

    strcat (str, "\n");
}

/**
 * Parse une chaine de caractéres en reponse
 * \param[in] str La chaine de caractéres a parser
 * \param[out] reponse La reponse obtenu
 */
void strtorep (T_Reponse* reponse, const char* str)
{
    char* copie_str;
    char* parametre;
    char identifiant[TAILLE_PARAM_MAX];
    char valeur[TAILLE_PARAM_MAX];
    T_Reponse_parametre param;
    int i = 0;
    // On reset la structure
    memset (reponse, 0, sizeof (T_Reponse) );
    // On récupére le numéro de requete
    sscanf (str, "REPONSE %d\n", & (reponse->identifiant) );

    if (reponse->identifiant == 0)
    {
        return;
    }

    // On fait une copie de la chiane de caractéres d'origine
    copie_str = (char*) malloc ( (strlen (str) + 1) * sizeof (char) );
    strcpy (copie_str, str);
    // Maintenant, on récupére toutes les lignes
    parametre = strtok (copie_str, "\n");

    while (parametre != NULL && i < NBR_PARAM_MAX)
    {
        // On récupére chaque morceaux
        sscanf (parametre, "%[^:]:%[^\n]", identifiant, valeur);

        if (strcmp (identifiant, parametre) != 0)
        {
            // On transforme nos \r en \n afin de retrouver des chaines normales
            strcrtonl (valeur);
            // On reset la structure
            memset (&param, 0, sizeof (T_Reponse_parametre) );
            // On assigne les valeurs
            strcpy (param.nom, identifiant);
            strcpy (param.valeur, valeur);
            // Et on le met a notre structure
            reponse->parametres[i] = param;
            // On incrémente
            i++;
        }

        // On continue notre découpe de parametres
        parametre = strtok (NULL, "\n");
    }

    reponse->nbr_parametres = i;
}


