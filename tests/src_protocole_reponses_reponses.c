#include "test_utils.h"

void test_reptostr ()
{
    // La valeur
    T_Reponse reponse;
    memset (&reponse, 0, sizeof (T_Reponse) );
    reponse.identifiant = 250;
    reponse.nbr_parametres = 2;
    T_Reponse_parametre param1;
    strcpy (param1.nom, "Param1");
    strcpy (param1.valeur, "Valeur1");
    T_Reponse_parametre param2;
    strcpy (param2.nom, "Param2");
    strcpy (param2.valeur, "Valeur2\nSur plusieurs lignes");
    reponse.parametres[0] = param1;
    reponse.parametres[1] = param2;
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REPONSE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reptostr (resultat, reponse);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_strtorep ()
{
    // La valeur que l'on doit obtenir
    T_Reponse expected;
    memset (&expected, 0, sizeof (T_Reponse) );
    expected.identifiant = 250;
    expected.nbr_parametres = 2;
    T_Reponse_parametre param1;
    strcpy (param1.nom, "Param1");
    strcpy (param1.valeur, "Valeur1");
    T_Reponse_parametre param2;
    strcpy (param2.nom, "Param2");
    strcpy (param2.valeur, "Valeur2\nSur plusieurs lignes");
    expected.parametres[0] = param1;
    expected.parametres[1] = param2;
    // La valeur
    char valeur[BUFF_MAX] = "REPONSE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    // Le résultat
    T_Reponse resultat;
    strtorep (&resultat, valeur);
    EXIT_IF_NOT_EQUAL (resultat.identifiant, expected.identifiant);
    EXIT_IF_NOT_EQUAL (resultat.nbr_parametres, expected.nbr_parametres);
    int i;

    for (i = 0; i < resultat.nbr_parametres; i += 1)
    {
        EXIT_IF_STRING_NOT_EQUAL (resultat.parametres[i].nom, expected.parametres[i].nom);
        EXIT_IF_STRING_NOT_EQUAL (resultat.parametres[i].valeur, expected.parametres[i].valeur);
    }
}

int main()
{
    test_reptostr();
    test_strtorep();
    return 0;
}

