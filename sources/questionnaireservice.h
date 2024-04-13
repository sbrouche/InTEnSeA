#ifndef QUESTIONNAIRESERVICE_H
#define QUESTIONNAIRESERVICE_H

#include <QStringList>

struct trouble_spectre_autisme {
    char diagnostic_de_trouble = 'a';
    QString a_quel_age = "";
    QString pose_par = "";
    QString score_adi = "";
    QString score_ados = "";
    QString score_qi = "";
    QString score_autre_test = "";
};
typedef struct trouble_spectre_autisme trouble_spectre_autisme;

struct autre_diagnostic {
    char trouble_attention_avec_hyperactivite = 'a';
    char trouble_attention_sans_hyperactivite = 'a';
    char trouble_communication_sociale = 'a';
    char trouble_communication_non_specifie = 'a';
    char trouble_moteurs = 'a';
    char trouble_apprentissages = 'a';
    char trouble_phonation = 'a';
    QString autre = "";
};
typedef struct autre_diagnostic autre_diagnostic;

struct diagnostic_psychiatrique {
    char trouble_anxieux = 'a';
    QString  type = "";
    char trouble_obsessionnel = 'a';
    char  trouble_stress = 'a';
};
typedef struct diagnostic_psychiatrique  diagnostic_psychiatrique;

struct prise_en_charge {
    char ime = 'a';
    char cams = 'a';
    char hopital_de_jour = 'a';
    char uema = 'a';
    char sessad = 'a';
    char rased = 'a';
    char segpa = 'a';
    char ulis = 'a';
    char liberal = 'a';
    QString autre_structure = "";

    char orthophonie = 'a';
    char psychomotricite = 'a';
    char ergotherapie = 'a';
    char educatrice = 'a';
    char psychologie = 'a';
    char  neuropsychologie = 'a';
    QString autre_type = "";
};
typedef struct prise_en_charge prise_en_charge;

struct traitement_medicamentaux  {
    char prend_il_un_traitement = 'a';
    QString traitement = "";
};
typedef  traitement_medicamentaux  traitement_medicamentaux;

struct sommeil_enfant {
    char difficulte_de_sommeil = 'a';
    QString  type = "";
    char endormissement = 'a';
    char reveil_nocturne = 'a';
    char  reveil_precoce = 'a';
    char  apnee_du_sommeil = 'a';
    char terreur_nocturne = 'a';
    char frequent_terreur_nocturne = 'a';
    char diagnostic_trouble_de_sommeil = 'a';
};
typedef struct sommeil_enfant  sommeil_enfant;

struct alimentation_enfant {
    char presente_selectivite_alimentaire = 'a';
    QString intensite_selectivite = "";

    // si oui
    char selon_structure = 'a';
    char selon_couleur = 'a';
    char selon_temperature = 'a';
    char selon_odeur = 'a';
    char selon_gout = 'a';
    char pb_mastication = 'a';
    char pb_deglutir = 'a';
    char pb_digestion = 'a';

    char diag_trouble_comportement_alimentaire = 'a';
};
typedef struct alimentation_enfant alimentation_enfant;

struct langage_enfant {
    QString  niveau_langage = "";
    QString age_premiers_mots = ""; //mois
};
typedef struct langage_enfant langage_enfant;

struct moteur_enfant  {
    char  retard_moteur = 'a';
    QString age_premiere_marche = "";
    char diagnostice_de_dyspraxie = 'a';
    char probleme_de_coordination = 'a';
    char  difficulte_de_lateralisation = 'a';
    char  difficulte_de_reperer_dans_lespace = 'a';
    char difficulte_de_motricite_fine = 'a';
};
typedef struct moteur moteur;

struct apprentissages_enfant {
    char presente_dyslexie = 'a';
    char difficulte_lecture = 'a';
    char difficulte_ecriture = 'a';
    char difficulte_calcul = 'a';
    QString autre = "";
};
typedef struct apprentissages_enfant apprentissages_enfant;

class QuestionnaireService
{
public:
    QuestionnaireService();
    QString toString();

    QString num_inclusion = "";
    QString nom = "";
    QString prenom = "";
    QString date_naissance = "";
    QString sexe  =  "";
    QString date_inclusion = "";
    QString date_test = "";
    QString nom_codateur = "";
    QString centre = "";

    trouble_spectre_autisme troubleSpectreAutisme;
    autre_diagnostic autreDiagnostic;
    diagnostic_psychiatrique diagnosticPsychiatrique;
    prise_en_charge  priseEnCharge;
    traitement_medicamentaux traitementMedicamentaux;
    sommeil_enfant sommeilEnfant;
    alimentation_enfant alimentationEnfant;
    langage_enfant langageEnfant;
    moteur_enfant  moteurEnfant;
    apprentissages_enfant apprentissageEnfant;

};

#endif // QUESTIONNAIRESERVICE_H
