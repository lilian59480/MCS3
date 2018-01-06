#include "test_utils.h"

void test_reqtostr () {
    
    // La valeur 
    T_Requete requete;
    memset(&requete,0,sizeof(T_Requete));
    
    requete.identifiant = 250;
    requete.nbr_parametres = 2;
    
    T_Requete_parametre param1;
    strcpy(param1.nom,"Param1");
    strcpy(param1.valeur,"Valeur1");
    
    T_Requete_parametre param2;
    strcpy(param2.nom,"Param2");
    strcpy(param2.valeur,"Valeur2\nSur plusieurs lignes");
    
    requete.parametres[0] = param1;
    requete.parametres[1] = param2;
    
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    
    // Le résultat
    char resultat[BUFF_MAX];
    
    reqtostr (resultat, requete);
    
    EXIT_IF_STRING_NOT_EQUAL(resultat,expected);
}

void test_strtoreq () {
    
    // La valeur que l'on doit obtenir
    T_Requete expected;
    memset(&expected,0,sizeof(T_Requete));
    
    expected.identifiant = 250;
    expected.nbr_parametres = 2;
    
    T_Requete_parametre param1;
    strcpy(param1.nom,"Param1");
    strcpy(param1.valeur,"Valeur1");
    
    T_Requete_parametre param2;
    strcpy(param2.nom,"Param2");
    strcpy(param2.valeur,"Valeur2\nSur plusieurs lignes");
    
    expected.parametres[0] = param1;
    expected.parametres[1] = param2;
    
    // La valeur
    char valeur[BUFF_MAX] = "REQUETE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    
    // Le résultat
    T_Requete resultat;
    
    strtoreq (&resultat, valeur);
    
    EXIT_IF_NOT_EQUAL(resultat.identifiant,expected.identifiant);
    EXIT_IF_NOT_EQUAL(resultat.nbr_parametres,expected.nbr_parametres);
    
    int i;
    
    for (i = 0; i < resultat.nbr_parametres; i += 1)
    {
        EXIT_IF_STRING_NOT_EQUAL(resultat.parametres[i].nom,expected.parametres[i].nom);
        EXIT_IF_STRING_NOT_EQUAL(resultat.parametres[i].valeur,expected.parametres[i].valeur);
    }
}

int main() {
    test_reqtostr();
    
    test_strtoreq();
    
    return 0;
}

