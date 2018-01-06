/**
 * \file requetes.c
 */
#include "requetes.h"

/**
 * Transforme une requete en chaine de caractéres
 * \param[out] str La chaine de caractéres obtenu
 * \param[in] requete La requete a transformer
 */
void reqtostr (char* str, const T_Requete requete)
{
    int i;
    // On met l'indentifiant de requete
    sprintf (str, "REQUETE %d\n", requete.identifiant);

    // On ajoute les parametres
    for (i = 0; i < requete.nbr_parametres; i += 1)
    {
        char parametre[TAILLE_PARAM_MAX * 2];
        char valeur[TAILLE_PARAM_MAX];
        strncpy (valeur, requete.parametres[i].valeur, TAILLE_PARAM_MAX - 1);
        strnltocr (valeur);
        sprintf (parametre,"%s:%s\n", requete.parametres[i].nom, valeur);
        strcat(str,parametre);
    }
    strcat(str,"\n");
}

/**
 * Parse une chaine de caractéres en requete
 * \param[in] str La chaine de caractéres a parser
 * \param[out] requete La requete obtenu
 */
void strtoreq (T_Requete* requete, const char* str)
{
    char* copie_str;
    char* parametre;
    char identifiant[TAILLE_PARAM_MAX];
    char valeur[TAILLE_PARAM_MAX];
    T_Requete_parametre param;
    int i = 0;
    // On reset la structure
    memset (requete, 0, sizeof (T_Requete) );
    // On récupére le numéro de requete
    sscanf (str, "REQUETE %d\n", & (requete->identifiant) );
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
            memset (&param, 0, sizeof (T_Requete_parametre) );
            // On assigne les valeurs
            strcpy (param.nom, identifiant);
            strcpy (param.valeur, valeur);
            // Et on le met a notre structure
            requete->parametres[i] = param;
            // On incrémente
            i++;
        }

        // On continue notre découpe de parametres
        parametre = strtok (NULL, "\n");
    }

    requete->nbr_parametres = i;
}
