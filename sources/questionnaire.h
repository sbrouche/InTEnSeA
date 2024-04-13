#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include <QtWidgets>
#include "questionnaireservice.h"
#include "radiobouton.h"
#include "champtexte.h"
#include "radiotextebouton.h"

class Fenetre;

struct aff_trouble_du_spectre{
    RadioBouton *diag_tsa_oui;
    RadioBouton *diag_tsa_non;
    RadioBouton *diag_tsa_nonconnu;

    ChampTexte *aQuelAge;
    ChampTexte *poser_par;
    ChampTexte *adi;
    ChampTexte *ados;
    ChampTexte *qui;
    ChampTexte *autre_test;

    // autre
    RadioBouton *taah_oui;
    RadioBouton *taah_non;
    RadioBouton *taah_nonconnu;

    RadioBouton *tash_oui;
    RadioBouton *tash_non;
    RadioBouton *tash_nonconnu;

    RadioBouton *tcs_oui;
    RadioBouton *tcs_non;
    RadioBouton *tcs_nonconnu;

    RadioBouton *tcns_oui;
    RadioBouton *tcns_non;
    RadioBouton *tcns_nonconnu;

    RadioBouton *tm_oui;
    RadioBouton *tm_non;
    RadioBouton *tm_nonconnu;

    RadioBouton *tda_oui;
    RadioBouton *tda_non;
    RadioBouton *tda_nonconnu;

    RadioBouton *tdp_oui;
    RadioBouton *tdp_non;
    RadioBouton *tdp_nonconnu;

    ChampTexte *autre_trouble;

    QVector<RadioBouton*> getListeRadioBouton();
    QVector<ChampTexte*> getListeChampTexte();
};
typedef struct aff_trouble_du_spectre aff_trouble_du_spectre;

struct aff_autre_diagnostic {
    RadioBouton *ta_oui;
    RadioBouton *ta_non;
    RadioBouton *ta_nonconnu;

    //type
    RadioTexteBouton *specifique;
    RadioTexteBouton *sociale;
    RadioTexteBouton *panique;
    RadioTexteBouton *angoraphobie;
    RadioTexteBouton *general;

    RadioBouton *toc_oui;
    RadioBouton *toc_non;
    RadioBouton *toc_nonconnu;

    RadioBouton *tspt_oui;
    RadioBouton *tspt_non;
    RadioBouton *tspt_nonconnu;

    QVector<RadioBouton*> getListeRadioBouton();
    QVector<RadioTexteBouton*> getListeRadioTexteBouton();
};
typedef struct aff_autre_diagnostic aff_autre_diagnostic;

struct aff_prise_encharge {
    RadioBouton *ime_oui;
    RadioBouton *ime_non;
    RadioBouton *ime_nonconnu;

    RadioBouton *cams_oui;
    RadioBouton *cams_non;
    RadioBouton *cams_nonconnu;

    RadioBouton *hopital_de_jour_oui;
    RadioBouton *hopital_de_jour_non;
    RadioBouton *hopital_de_jour_nonconnu;

    RadioBouton *uema_oui;
    RadioBouton *uema_non;
    RadioBouton *uema_nonconnu;

    RadioBouton *sessad_oui;
    RadioBouton *sessad_non;
    RadioBouton *sessad_nonconnu;

    RadioBouton *rased_oui;
    RadioBouton *rased_non;
    RadioBouton *rased_nonconnu;

    RadioBouton *segpa_oui;
    RadioBouton *segpa_non;
    RadioBouton *segpa_nonconnu;

    RadioBouton *ulis_oui;
    RadioBouton *ulis_non;
    RadioBouton *ulis_nonconnu;

    RadioBouton *liberal_oui;
    RadioBouton *liberal_non;
    RadioBouton *liberal_nonconnu;

    ChampTexte  *autre_structure;

    RadioBouton *orthophonie_oui;
    RadioBouton *orthophonie_non;
    RadioBouton *orthophonie_nonconnu;

    RadioBouton *psychomotricite_oui;
    RadioBouton *psychomotricite_non;
    RadioBouton *psychomotricite_nonconnu;

    RadioBouton *ergotherapie_oui;
    RadioBouton *ergotherapie_non;
    RadioBouton *ergotherapie_nonconnu;

    RadioBouton *educatrice_oui;
    RadioBouton *educatrice_non;
    RadioBouton *educatrice_nonconnu;

    RadioBouton *psychologique_oui;
    RadioBouton *psychologique_non;
    RadioBouton *psychologique_nonconnu;

    RadioBouton *neuropsychologique_oui;
    RadioBouton *neuropsychologique_non;
    RadioBouton *neuropsychologique_nonconnu;

    ChampTexte  *autre_prise_en_charge;

    QVector<RadioBouton*> getListeRadioBouton();
    QVector<ChampTexte*> getListeChampTexte();
};
typedef struct aff_prise_encharge aff_prise_encharge;

struct aff_traitement_medicamentaux {
    RadioBouton *prend_il_oui;
    RadioBouton *prend_il_non;
    RadioBouton *prend_il_nonconnu;

    ChampTexte *preciser;

    QVector<RadioBouton*> getListeRadioBouton();

public:
    ChampTexte *getPreciser() const;
    void setPreciser(ChampTexte *newPreciser);
};
typedef struct aff_traitement_medicamentaux aff_traitement_medicamentaux;

struct aff_sommeil_enfant {
    RadioBouton *diffsom_oui;
    RadioBouton *diffsom_non;
    RadioBouton *diffsom_nonconnu;

    RadioBouton *endorm_oui;
    RadioBouton *endorm_non;

    RadioBouton *nocturne_oui;
    RadioBouton *nocturne_non;

    RadioBouton *precoce_oui;
    RadioBouton *precoce_non;

    RadioBouton *apnee_oui;
    RadioBouton *apnee_non;
    RadioBouton *apnee_nonconnu;

    RadioBouton *terreur_oui;
    RadioBouton *terreur_non;
    RadioBouton *terreur_nonconnu;

    RadioBouton *frequent_oui;
    RadioBouton *frequent_non;
    RadioBouton *frequent_nonconnu;

    RadioBouton *diag_trouble_oui;
    RadioBouton *diag_trouble_non;
    RadioBouton *diag_trouble_nonconnu;
    QVector<RadioBouton*> getListeRadioBouton();
};
typedef struct aff_sommeil_enfant aff_sommeil_enfant;

struct aff_alimentation_enfant {
    RadioBouton *selective_oui;
    RadioBouton *selective_non;
    RadioBouton *selective_nonconnu;

    RadioTexteBouton *du_tout;
    RadioTexteBouton *un_peu;
    RadioTexteBouton *souvent;
    RadioTexteBouton *tout_le_temps;

    RadioBouton *selon_texture_oui;
    RadioBouton *selon_texture_non;
    RadioBouton *selon_texture_nonconnu;

    RadioBouton *selon_couleur_oui;
    RadioBouton *selon_couleur_non;
    RadioBouton *selon_couleur_nonconnu;

    RadioBouton *selon_temp_oui;
    RadioBouton *selon_temp_non;
    RadioBouton *selon_temp_nonconnu;

    RadioBouton *selon_odeur_oui;
    RadioBouton *selon_odeur_non;
    RadioBouton *selon_odeur_nonconnu;

    RadioBouton *selon_gout_oui;
    RadioBouton *selon_gout_non;
    RadioBouton *selon_gout_nonconnu;

    RadioBouton *pd_mastication_oui;
    RadioBouton *pd_mastication_non;
    RadioBouton *pd_mastication_nonconnu;

    RadioBouton *pb_deglutir_oui;
    RadioBouton *pb_deglutir_non;
    RadioBouton *pb_deglutir_nonconnu;

    RadioBouton *pb_digestion_oui;
    RadioBouton *pb_digestion_non;
    RadioBouton *pb_digestion_nonconnu;

    RadioBouton *diag_trouble_comp_oui;
    RadioBouton *diag_trouble_comp_non;
    RadioBouton *diag_trouble_comp_nonconnu;

    QVector<RadioBouton*> getListeRadioBouton();
    QVector<RadioTexteBouton*> getListeRadioTexteBouton();
};
typedef struct aff_alimentation_enfant aff_alimentation_enfant;

struct aff_langage_enfant {
    RadioTexteBouton *verbal;
    RadioTexteBouton *phrases;
    RadioTexteBouton *mots;
    RadioTexteBouton *nonverbal;

    ChampTexte *age_premiers_mots;
    QVector<RadioTexteBouton*> getListeRadioTexteBouton();
};
typedef struct aff_langage_enfant aff_langage_enfant;

struct aff_moteur_enfant {
    RadioBouton * retard_oui;
    RadioBouton * retard_non;
    RadioBouton * retard_nonconnu;

    ChampTexte * age_marche;

    RadioBouton * dyspraxie_oui;
    RadioBouton * dyspraxie_non;
    RadioBouton * dyspraxie_nonconnu;

    //    Si non

    RadioBouton * coordination_oui;
    RadioBouton * coordination_non;
    RadioBouton * coordination_nonconnu;

    RadioBouton * lateralisation_oui;
    RadioBouton * lateralisation_non;
    RadioBouton * lateralisation_nonconnu;

    RadioBouton * reperer_oui;
    RadioBouton * reperer_non;
    RadioBouton * reperer_nonconnu;

    RadioBouton * motricite_oui;
    RadioBouton * motricite_non;
    RadioBouton * motricite_nonconnu;

    QVector<RadioBouton*> getListeRadioBouton();
};
typedef struct aff_moteur_enfant aff_moteur_enfant;

struct aff_apprentissages_enfant {
    RadioBouton *dyslexie_oui;
    RadioBouton *dyslexie_non;
    RadioBouton *dyslexie_nonconnu;

    RadioBouton *lecture_oui;
    RadioBouton *lecture_non;
    RadioBouton *lecture_nonconnu;

    RadioBouton *ecriture_oui;
    RadioBouton *ecriture_non;
    RadioBouton *ecriture_nonconnu;

    RadioBouton *calcul_oui;
    RadioBouton *calcul_non;
    RadioBouton *calcul_nonconnu;

    ChampTexte *Autre;

    QVector<RadioBouton*> getListeRadioBouton();
};
typedef struct aff_apprentissages_enfant aff_apprentissages_enfant;

class Questionnaire : public QWidget
{
    Q_OBJECT
public:
    explicit Questionnaire(Fenetre *f, QWidget *parent = nullptr);


signals:

private slots:
    void enregistrer();

    void pageSuivante();
    void pagePrecedente();

    void onClickRadioBouton(bool); // pour radiobutton
    void onEditChampTexte();    // pour champ texte
    void onClickRadioTexteBouton(bool);

    void setDiagTsaOui(bool);
    void setDiagTsaNon(bool);
    void setDiagTsaNa(bool);

    void setTsaAge(QString str);
    void setPosePar(QString str);
    void setAdi(QString str);
    void setAdos(QString str);
    void setQi(QString str);
    void setScoreAutre(QString str);

private :
    QStackedWidget *stackedWidget;

    void setPages();

    void setPage0();
    void setPageA1();
    void setPageA2();
    void setPageC();
    void setPageD();
    void setPageE();
    void setPageF();
    void setPageG();
    void setPageH();
    void setPageI();

    QuestionnaireService *questionnaireService;
    Fenetre *fenetre;

    QWidget *page0;
    QWidget *pageA1;
    QWidget *pageA2;
    QWidget *pageC;
    QWidget *pageC2;
    QWidget *pageD;
    QWidget *pageE;
    QWidget *pageF;
    QWidget *pageG;
    QWidget *pageh;
    QWidget *pageI;

//    PAGE 0
    ChampTexte *num_inclusion;
    ChampTexte *prenom;
    ChampTexte *nom;
    ChampTexte *date_naissance;
    RadioTexteBouton *radio_homme;
    RadioTexteBouton  *radio_femme;
    ChampTexte *date_inclusion;
    ChampTexte *date_test;
    ChampTexte  *nom_codateur;
    ChampTexte *centre;

    QPushButton *bt_suivant;
    QPushButton *bt_precedent;

//    PAGE A1
    aff_trouble_du_spectre AffTroubleDuSpectre;

//    PAGE A2
    aff_autre_diagnostic affAutreDiagnostic;

//    PAGE C
    aff_prise_encharge affPriseEnCharge;

//    PAGE D
    aff_traitement_medicamentaux affTraitementMedicamentaux;

//    PAGE E
    aff_sommeil_enfant affSommeilEnfant;

//    PAGE F
    aff_alimentation_enfant affAlimentationEnfant;

//    PAGE G
    aff_langage_enfant affLangageEnfant;

//    PAGE H
    aff_moteur_enfant affMoteurEnfant;

//    PAGE I
    aff_apprentissages_enfant affApprentissagesEnfant;

};

#endif // QUESTIONNAIRE_H
