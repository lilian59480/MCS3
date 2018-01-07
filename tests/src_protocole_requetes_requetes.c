#include "test_utils.h"

void test_reqtostr ()
{
    // La valeur
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = 250;
    requete.nbr_parametres = 2;
    T_Requete_parametre param1;
    strcpy (param1.nom, "Param1");
    strcpy (param1.valeur, "Valeur1");
    T_Requete_parametre param2;
    strcpy (param2.nom, "Param2");
    strcpy (param2.valeur, "Valeur2\nSur plusieurs lignes");
    requete.parametres[0] = param1;
    requete.parametres[1] = param2;
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_strtoreq ()
{
    // La valeur que l'on doit obtenir
    T_Requete expected;
    memset (&expected, 0, sizeof (T_Requete) );
    expected.identifiant = 250;
    expected.nbr_parametres = 2;
    T_Requete_parametre param1;
    strcpy (param1.nom, "Param1");
    strcpy (param1.valeur, "Valeur1");
    T_Requete_parametre param2;
    strcpy (param2.nom, "Param2");
    strcpy (param2.valeur, "Valeur2\nSur plusieurs lignes");
    expected.parametres[0] = param1;
    expected.parametres[1] = param2;
    // La valeur
    char valeur[BUFF_MAX] = "REQUETE 250\nParam1:Valeur1\nParam2:Valeur2\rSur plusieurs lignes\n\n";
    // Le résultat
    T_Requete resultat;
    strtoreq (&resultat, valeur);
    EXIT_IF_NOT_EQUAL (resultat.identifiant, expected.identifiant);
    EXIT_IF_NOT_EQUAL (resultat.nbr_parametres, expected.nbr_parametres);
    int i;

    for (i = 0; i < resultat.nbr_parametres; i += 1)
    {
        EXIT_IF_STRING_NOT_EQUAL (resultat.parametres[i].nom, expected.parametres[i].nom);
        EXIT_IF_STRING_NOT_EQUAL (resultat.parametres[i].valeur, expected.parametres[i].valeur);
    }
}

void test_creareq_ping()
{
    // La valeur
    T_Requete requete;
    requete = creareq_ping();
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 1\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_deconnexion()
{
    // La valeur
    T_Requete requete;
    requete = creareq_deconnexion();
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 2\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_connexion_serveur_central()
{
    // La valeur
    T_Requete requete;
    requete = creareq_connexion_serveur_central ("PSEUDO");
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 100\nPseudo:PSEUDO\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_nombre_clients_connectes()
{
    // La valeur
    T_Requete requete;
    requete = creareq_nombre_clients_connectes ();
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 101\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_information_client()
{
    // La valeur
    T_Requete requete;
    requete = creareq_information_client (5);
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 102\nIndex:5\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_passer_mode_partie()
{
    // La valeur
    T_Requete requete;
    requete = creareq_passer_mode_partie ("CLIENT1", "CLIENT2", "CLIENT3", 2);
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 103\nClient_1:CLIENT1\nClient_2:CLIENT2\nClient_3:CLIENT3\nPartenaire:2\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_port_chat()
{
    // La valeur
    T_Requete requete;
    requete = creareq_port_chat (1);
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 104\nType:1\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_choix_joueur()
{
    // La valeur
    T_Requete requete;
    requete = creareq_choix_joueur();
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 105\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_demande_partie()
{
    // La valeur
    T_Requete requete;
    requete = creareq_demande_partie (-1);
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 200\nEquipe:-1\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_question()
{
    // La valeur
    T_Requete requete;
    requete = creareq_question ("Ce test va t'il fonctionner?");
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 201\nQuestion:Ce test va t'il fonctionner?\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_valider_reponse()
{
    // La valeur
    T_Requete requete;
    requete = creareq_valider_reponse (FALSE, "Oui, mais c'est pas bon\nLa reponse D");
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 202\nValide:0\nMessage:Oui, mais c'est pas bon\rLa reponse D\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

void test_creareq_message_chat()
{
    // La valeur
    T_Requete requete;
    requete = creareq_message_chat ("Message chat");
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "REQUETE 203\nMessage:Message chat\n\n";
    // Le résultat
    char resultat[BUFF_MAX];
    reqtostr (resultat, requete);
    EXIT_IF_STRING_NOT_EQUAL (resultat, expected);
}

int main()
{
    test_reqtostr();
    test_strtoreq();
    test_creareq_ping();
    test_creareq_deconnexion();
    test_creareq_connexion_serveur_central();
    test_creareq_nombre_clients_connectes();
    test_creareq_information_client();
    test_creareq_passer_mode_partie();
    test_creareq_port_chat();
    test_creareq_choix_joueur();
    test_creareq_demande_partie();
    test_creareq_question();
    test_creareq_valider_reponse();
    test_creareq_message_chat();
    return 0;
}

