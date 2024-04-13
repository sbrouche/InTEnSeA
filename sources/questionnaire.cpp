#include "questionnaire.h"
#include "fenetre.h"

Questionnaire::Questionnaire(Fenetre *f,QWidget *parent)
    : QWidget{parent}
{
    fenetre = f;
    questionnaireService  =  new  QuestionnaireService;
    setFont(QFont("Times", 10));

    stackedWidget  =  new  QStackedWidget;

    QVBoxLayout *vlayout  =  new QVBoxLayout(this);

    page0 = new QWidget;
    pageA1 = new QWidget;
    pageA2 = new QWidget;
    pageC = new QWidget;
    pageC2 = new QWidget;
    pageD = new QWidget;
    pageE = new QWidget;
    pageF = new QWidget;
    pageG = new QWidget;
    pageh = new QWidget;
    pageI = new QWidget;
    setPages();

    stackedWidget->addWidget(page0);
    stackedWidget->addWidget(pageA1);
    stackedWidget->addWidget(pageA2);
    stackedWidget->addWidget(pageC);
    stackedWidget->addWidget(pageC2);
    stackedWidget->addWidget(pageD);
    stackedWidget->addWidget(pageE);
    stackedWidget->addWidget(pageF);
    stackedWidget->addWidget(pageG);
    stackedWidget->addWidget(pageh);
    stackedWidget->addWidget(pageI);

    stackedWidget->setCurrentIndex(0);

    vlayout->addWidget(stackedWidget);

    bt_suivant =  new QPushButton("Suivant");
    bt_suivant->setStyleSheet("width : 250; height : 25");
    bt_suivant->setFont(QFont("Times", 15));
    bt_precedent =  new QPushButton("Précédent");
    bt_precedent->setStyleSheet("width : 250; height : 25");
    bt_precedent->setFont(QFont("Times", 15));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(bt_precedent, 0, Qt::AlignLeft);
    hlayout->addWidget(bt_suivant, 0, Qt::AlignRight);
    vlayout->addLayout(hlayout);

    setStyleSheet("background-color: white;");

    connect(bt_suivant, SIGNAL(clicked()), this, SLOT(pageSuivante()));
    connect(bt_precedent, SIGNAL(clicked()), this, SLOT(pagePrecedente()));
}


void Questionnaire::enregistrer()
{
    QString ligne = questionnaireService->toString();

    QFile file("extraction.csv");
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf16);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "le fichier ne peut pas se créer";

    }

    if(file.size() == 0) {
        out << "Nom complet;Numéro de code du sujet ;Groupe (Contrôle ou TSA);Date de naissance de naissance de l'enfant  ;Genre ;Date inclusion;Date de test ;Nom investigateur ;Centre ;Diagnostic de trouble du spectre de l'autisme ;Si oui, à quel âge;Diagnostic posé par;Score ADI;Score ADOS;Score QI;Score autre;Trouble de l'attention avec hyperactivité ;Trouble de l'attention sans hyperactivité ;Trouble de la communication sociale ;Trouble de la communication non spécifié ;Trouble moteurs ;Trouble des apprentissages ;Trouble de la phonation ;Autre ;Trouble anxieux;Si oui, préciser le type;Trouble obsessionnel compulsif;Trouble de stress post-traumatique ;Dans quelle types de structure votre enfant est-il pris en charge ;De quels types de prise en charge bénéficie votre enfant ? ;Votre enfant prend-il un traitement(s) actuellement ? ;Si oui, préciser ;Votre enfant présente-t-il des difficultés de sommeil;Si oui, préciser le type ? ;Votre enfant présente-t-il de l'apnée du sommeil ? ;Votre enfant fait-il des terreurs nocturnes ? ;Si oui est-ce fréquent ;Un diagnostic de trouble du sommeil a-t-il été posé ? ;Votre enfant présente-t-il une sélectivité alimentaire ;Si oui, quelle est l'intensité de cette sélectivité alimentaire selon vous ? ;Si oui, préciser comment choisit-il ses aliments ;Si oui, préciser les difficultés ;Quel est le niveau de langage de votre enfant ;Quel est l'âge auquel votre enfant a eu ses premiers mots (mois);Votre enfant présente-t-il un retard sur le plan moteur ;Quel est son âge d'acquisition de la marche (mois);Est-ce que votre enfant a un diagnostic de dyspraxie  ? ;Est-ce que votre enfant présente de problème de coordination ?;Est-ce que votre enfant présente des difficultés de latéralisation ?;Est-ce que votre enfant présente des difficultés pour se repérer dans l'espace ? ;Est-ce que votre enfant présente des difficultés de motricité fine ? ;Votre enfant présente-t-il une dyslexie ;Votre enfant a-t-il eu des difficultés d'apprentissage de la lecture ;Votre enfant a-t-il eu des difficultés d'apprentissage de l'écriture ;Votre enfant a-t-il eu des difficultés d'apprentissage du calcul;Autre, préciser\n";
    }
    out << ligne + "\n";
    fenetre->versPageMainMenu();
}

void Questionnaire::pageSuivante()
{
    int index= stackedWidget->currentIndex();
    if (++index < stackedWidget->count()) {
        stackedWidget->setCurrentIndex(index);
    }
}

void Questionnaire::pagePrecedente()
{
    int index= stackedWidget->currentIndex();
    if (--index >= 0) {
        stackedWidget->setCurrentIndex(index);
    }
}

void Questionnaire::onClickRadioBouton(bool etat)
{
    RadioBouton *bouton = (RadioBouton*) QObject::sender();
    if (etat == true) {
        QString text = bouton->text();
        if (text == "oui") {
            bouton->getCible()[0] = 'o';
        } else if (text == "non") {
            bouton->getCible()[0] = 'n';
        } else {
            bouton->getCible()[0] = 'a';
        }
    }
    qDebug() << questionnaireService->toString();
}

void Questionnaire::onEditChampTexte()
{
    ChampTexte *champ = (ChampTexte *) QObject::sender();
    champ->getCible()[0] = champ->text();
    qDebug() << questionnaireService->toString();
}

void Questionnaire::onClickRadioTexteBouton(bool etat)
{
    RadioTexteBouton *bouton = (RadioTexteBouton*) QObject::sender();
    if (etat == true) {
        QString text = bouton->text();
        bouton->getCible()[0] = text;
    }
    qDebug() << questionnaireService->toString();
}

void Questionnaire::setDiagTsaOui(bool actif)
{
    questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble = actif ? 'o' : 'a';
}

void Questionnaire::setDiagTsaNon(bool actif)
{
    questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble = actif ? 'n' : 'a';
}

void Questionnaire::setDiagTsaNa(bool actif)
{
    questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble = actif ? 'a' : 'a';
}



void Questionnaire::setTsaAge(QString str)
{
    questionnaireService->troubleSpectreAutisme.a_quel_age = str;
}

void Questionnaire::setPosePar(QString str)
{
    questionnaireService->troubleSpectreAutisme.pose_par = str;
}

void Questionnaire::setAdi(QString str)
{
    questionnaireService->troubleSpectreAutisme.score_adi = str;
}

void Questionnaire::setAdos(QString str)
{
    questionnaireService->troubleSpectreAutisme.score_ados = str;
}

void Questionnaire::setQi(QString str)
{
    questionnaireService->troubleSpectreAutisme.score_qi = str;
}

void Questionnaire::setScoreAutre(QString str)
{
    questionnaireService->troubleSpectreAutisme.score_autre_test = str;
}

void Questionnaire::setPages()
{
    setPage0();
    setPageA1();
    setPageA2();
    setPageC();
    setPageD();
    setPageE();
    setPageF();
    setPageG();
    setPageH();
    setPageI();
}

void Questionnaire::setPage0()
{
    num_inclusion = new ChampTexte(&questionnaireService->num_inclusion);
    prenom = new ChampTexte(&questionnaireService->prenom);
    nom = new ChampTexte(&questionnaireService->nom);

    radio_homme = new RadioTexteBouton("H", &questionnaireService->sexe);
    radio_femme = new RadioTexteBouton("F", &questionnaireService->sexe);
    date_inclusion = new ChampTexte(&questionnaireService->date_inclusion);
    date_test = new ChampTexte(&questionnaireService->date_test);
    nom_codateur = new ChampTexte(&questionnaireService->nom_codateur);
    centre = new ChampTexte(&questionnaireService->centre);
    date_naissance = new ChampTexte(&questionnaireService->date_naissance);

    QVBoxLayout *vlayout = new QVBoxLayout(page0);

    QGroupBox *box = new QGroupBox;

    QFormLayout *layout  =  new QFormLayout;
    layout->addRow("Numéro de code du sujet : ", num_inclusion);
    layout->addRow("Nom : ", nom);
    layout->addRow("Prénom : ", prenom);
    layout->addRow("Date de naissance : ", date_naissance);

    QHBoxLayout *layout_genre = new QHBoxLayout;
    layout_genre->addWidget(radio_homme);
    layout_genre->addWidget(radio_femme);
    layout_genre->setAlignment(Qt::AlignLeft);
    layout->addRow("Genre : ", layout_genre);
    layout->addRow("Date d'inclusion : ", date_inclusion);
    layout->addRow("Date de test : ", date_test);
    layout->addRow("Nom du codateur/investigateur : ", nom_codateur);
    layout->addRow("Centre : ", centre);

    box->setLayout(layout);
    vlayout->addWidget(box);


    connect(date_naissance, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(centre, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(nom_codateur, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(date_test, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(date_inclusion, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(nom, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(prenom, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    connect(num_inclusion, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));

    connect(radio_femme, SIGNAL(toggled(bool)), this, SLOT(onClickRadioTexteBouton(bool)));
    connect(radio_homme, SIGNAL(toggled(bool)), this, SLOT(onClickRadioTexteBouton(bool)));
}

void Questionnaire::setPageA1()
{
    QVBoxLayout *layout = new QVBoxLayout(pageA1);
    QGroupBox *group = new QGroupBox;
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    aff_trouble_du_spectre aff = AffTroubleDuSpectre;

    QHBoxLayout *tsaL = new QHBoxLayout();
    tsaL->setAlignment(Qt::AlignLeft);
     aff.diag_tsa_oui = new RadioBouton("oui", &questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble);
     aff.diag_tsa_non = new RadioBouton("non", &questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble);
     aff.diag_tsa_nonconnu = new RadioBouton("non connu", &questionnaireService->troubleSpectreAutisme.diagnostic_de_trouble);
     tsaL->addWidget(aff.diag_tsa_oui);
     tsaL->addWidget(aff.diag_tsa_non);
     tsaL->addWidget(aff.diag_tsa_nonconnu);
     fl->addRow("Diagnostic de trouble du spectre de l'autisme : ", tsaL);
     connect(aff.diag_tsa_oui, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));

     QGroupBox *group1 = new QGroupBox ("(Si oui)");
     QFormLayout *flGroup1 = new QFormLayout;
     group1->setLayout(flGroup1);
     aff.aQuelAge = new ChampTexte(&questionnaireService->troubleSpectreAutisme.a_quel_age);
     flGroup1->addRow("A quel âge : ", aff.aQuelAge);
     aff.poser_par = new ChampTexte(&questionnaireService->troubleSpectreAutisme.pose_par);
     flGroup1->addRow("Diagnostic posé par (quel professionnel de santé, quel type de structure) : ", aff.poser_par);
     aff.adi = new ChampTexte(&questionnaireService->troubleSpectreAutisme.score_adi);
     flGroup1->addRow("Score ADI : ", aff.adi);
     aff.ados = new ChampTexte(&questionnaireService->troubleSpectreAutisme.score_ados);
     flGroup1->addRow("Score ADOS : ", aff.ados);
     aff.qui = new ChampTexte(&questionnaireService->troubleSpectreAutisme.score_qi);
     flGroup1->addRow("Score QI : ", aff.qui);
     aff.autre_test = new ChampTexte(&questionnaireService->troubleSpectreAutisme.score_autre_test);
     flGroup1->addRow("Score autre test : ", aff.autre_test);

     fl->addWidget(group1);

    // autre
     QGroupBox *autreBox = new QGroupBox("Autre diagnostic");
     QFormLayout *flAutre = new QFormLayout;
     autreBox->setLayout(flAutre);
     layout->addWidget(autreBox);

     QGroupBox *groupTaah = new QGroupBox;
     QHBoxLayout *taahL = new QHBoxLayout();
     groupTaah->setLayout(taahL);
     taahL->setAlignment(Qt::AlignLeft);
     aff.taah_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_attention_avec_hyperactivite);
     aff.taah_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_attention_avec_hyperactivite);
     aff.taah_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_attention_avec_hyperactivite);
     taahL->addWidget(aff.taah_oui);
     taahL->addWidget(aff.taah_non);
     taahL->addWidget(aff.taah_nonconnu);
     flAutre->addRow("Trouble de l'attention avec hyperactivité : ", groupTaah);

     QGroupBox *groupTash = new QGroupBox;
     QHBoxLayout *tashL = new QHBoxLayout();
     groupTash->setLayout(tashL);
     tashL->setAlignment(Qt::AlignLeft);
     aff.tash_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_attention_sans_hyperactivite);
     aff.tash_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_attention_sans_hyperactivite);
     aff.tash_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_attention_sans_hyperactivite);
     tashL->addWidget(aff.tash_oui);
     tashL->addWidget(aff.tash_non);
     tashL->addWidget(aff.tash_nonconnu);
     flAutre->addRow("Trouble de l'attention sans hyperactivité : ", groupTash);

     QGroupBox *groupTcs = new QGroupBox;
     QHBoxLayout *tcsL = new QHBoxLayout();
     groupTcs->setLayout(tcsL);
     tcsL->setAlignment(Qt::AlignLeft);
     aff.tcs_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_communication_sociale);
     aff.tcs_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_communication_sociale);
     aff.tcs_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_communication_sociale);
     tcsL->addWidget(aff.tcs_oui);
     tcsL->addWidget(aff.tcs_non);
     tcsL->addWidget(aff.tcs_nonconnu);
     flAutre->addRow("Trouble de la communication sociale : ", groupTcs);

     QGroupBox *groupTcns = new QGroupBox;
     QHBoxLayout *tcnsL = new QHBoxLayout();
     groupTcns->setLayout(tcnsL);
     tcnsL->setAlignment(Qt::AlignLeft);
     aff.tcns_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_communication_non_specifie);
     aff.tcns_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_communication_non_specifie);
     aff.tcns_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_communication_non_specifie);
     tcnsL->addWidget(aff.tcns_oui);
     tcnsL->addWidget(aff.tcns_non);
     tcnsL->addWidget(aff.tcns_nonconnu);
     flAutre->addRow("Trouble de la communication non spécifiée : ", groupTcns);

     QGroupBox *groupTm = new QGroupBox;
     QHBoxLayout *tm = new QHBoxLayout();
     groupTm->setLayout(tm);
     tm->setAlignment(Qt::AlignLeft);
     aff.tm_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_moteurs);
     aff.tm_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_moteurs);
     aff.tm_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_moteurs);
     tm->addWidget(aff.tm_oui);
     tm->addWidget(aff.tm_non);
     tm->addWidget(aff.tm_nonconnu);
     flAutre->addRow("Trouble moteurs", groupTm);

     QGroupBox *groupTda = new QGroupBox;
     QHBoxLayout *tdaL = new QHBoxLayout();
     groupTda->setLayout(tdaL);
     tdaL->setAlignment(Qt::AlignLeft);
     aff.tda_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_apprentissages);
     aff.tda_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_apprentissages);
     aff.tda_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_apprentissages);
     tdaL->addWidget(aff.tda_oui);
     tdaL->addWidget(aff.tda_non);
     tdaL->addWidget(aff.tda_nonconnu);
     flAutre->addRow("Trouble des apprentissages", groupTda);

     QGroupBox *groupTdp = new QGroupBox;
     QHBoxLayout *tdp = new QHBoxLayout();
     groupTdp->setLayout(tdp);
     tdp->setAlignment(Qt::AlignLeft);
     aff.tdp_oui = new RadioBouton("oui", &questionnaireService->autreDiagnostic.trouble_phonation);
     aff.tdp_non = new RadioBouton("non", &questionnaireService->autreDiagnostic.trouble_phonation);
     aff.tdp_nonconnu = new RadioBouton("non connu", &questionnaireService->autreDiagnostic.trouble_phonation);
     tdp->addWidget(aff.tdp_oui);
     tdp->addWidget(aff.tdp_non);
     tdp->addWidget(aff.tdp_nonconnu);
     flAutre->addRow("trouble de la phonation", groupTdp);

    aff.autre_trouble = new ChampTexte(&questionnaireService->autreDiagnostic.autre);
    flAutre->addRow("Autre", aff.autre_trouble);

    for(RadioBouton *radio : aff.getListeRadioBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
    }
    for(ChampTexte *champ : aff.getListeChampTexte()) {
        connect(champ, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
    }

}

void Questionnaire::setPageA2()
{
    aff_autre_diagnostic aff = affAutreDiagnostic;

    QVBoxLayout *layout = new QVBoxLayout(pageA2);
    QGroupBox *group = new QGroupBox;
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupeTa = new QGroupBox;
    QHBoxLayout *ta = new QHBoxLayout();
    groupeTa->setLayout(ta);
    ta->setAlignment(Qt::AlignLeft);
    aff.ta_oui = new RadioBouton("oui", &questionnaireService->diagnosticPsychiatrique.trouble_anxieux) ;;
    aff.ta_non = new RadioBouton("non", &questionnaireService->diagnosticPsychiatrique.trouble_anxieux) ;;
    aff.ta_nonconnu = new RadioBouton("non connu", &questionnaireService->diagnosticPsychiatrique.trouble_anxieux) ;;
    ta->addWidget(aff.ta_oui);
    ta->addWidget(aff.ta_non);
    ta->addWidget(aff.ta_nonconnu);
    fl->addRow("Trouble anxieux", groupeTa);

    //type
    QGroupBox *groupType = new QGroupBox("(Si oui)");
    QVBoxLayout *typeL = new QVBoxLayout();
    groupType->setLayout(typeL);
    typeL->setAlignment(Qt::AlignLeft);
    aff.specifique = new RadioTexteBouton("Phobie spécifique", &questionnaireService->diagnosticPsychiatrique.type) ;
    aff.sociale = new RadioTexteBouton("Anxiété sociale", &questionnaireService->diagnosticPsychiatrique.type) ;
    aff.panique = new RadioTexteBouton("Trouble panique", &questionnaireService->diagnosticPsychiatrique.type) ;
    aff.angoraphobie = new RadioTexteBouton("Angoraphobie", &questionnaireService->diagnosticPsychiatrique.type) ;
    aff.general = new RadioTexteBouton("Anxiété général", &questionnaireService->diagnosticPsychiatrique.type) ;
    typeL->addWidget(aff.specifique);
    typeL->addWidget(aff.sociale);
    typeL->addWidget(aff.panique);
    typeL->addWidget(aff.angoraphobie);
    typeL->addWidget(aff.general);
    fl->addRow("Trouble de l'attention sans hyperactivité : ", groupType);

    QGroupBox *groupeToc = new QGroupBox;
    QHBoxLayout *tocL = new QHBoxLayout();
    groupeToc->setLayout(tocL);
    tocL->setAlignment(Qt::AlignLeft);
    aff.toc_oui = new RadioBouton("oui", &questionnaireService->diagnosticPsychiatrique.trouble_obsessionnel) ;
    aff.toc_non = new RadioBouton("non", &questionnaireService->diagnosticPsychiatrique.trouble_obsessionnel) ;;
    aff.toc_nonconnu = new RadioBouton("non connu", &questionnaireService->diagnosticPsychiatrique.trouble_obsessionnel) ;;
    tocL->addWidget(aff.toc_oui);
    tocL->addWidget(aff.toc_non);
    tocL->addWidget(aff.toc_nonconnu);
    fl->addRow("Trouble obsessionnel compulsif", groupeToc);

    QGroupBox *groupeTspt = new QGroupBox;
    QHBoxLayout *tspt = new QHBoxLayout();
    groupeTspt->setLayout(tspt);
    tspt->setAlignment(Qt::AlignLeft);
    aff.tspt_oui = new RadioBouton("oui", &questionnaireService->diagnosticPsychiatrique.trouble_stress) ;;
    aff.tspt_non = new RadioBouton("non", &questionnaireService->diagnosticPsychiatrique.trouble_stress) ;;
    aff.tspt_nonconnu = new RadioBouton("non connu", &questionnaireService->diagnosticPsychiatrique.trouble_stress) ;;
    tspt->addWidget(aff.tspt_oui);
    tspt->addWidget(aff.tspt_non);
    tspt->addWidget(aff.tspt_nonconnu);
    fl->addRow("Trouble de stress post-traumatique", groupeTspt);

    for(RadioBouton *radio : aff.getListeRadioBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
    }
    for (RadioTexteBouton *radio : aff.getListeRadioTexteBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioTexteBouton(bool)));
    }

}

void Questionnaire::setPageC()
{
    aff_prise_encharge aff = affPriseEnCharge;

    QVBoxLayout *layout = new QVBoxLayout(pageC);
    layout->addWidget(new QLabel("Dans quels types de structure votre enfant est-il pris en charge ?"));
    QGroupBox *group = new QGroupBox;
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);


    QGroupBox *groupeIme = new QGroupBox;
    QHBoxLayout *ime = new QHBoxLayout();
    groupeIme->setLayout(ime);
    ime->setAlignment(Qt::AlignLeft);
     aff.ime_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.ime);
     aff.ime_non = new RadioBouton("non", &questionnaireService->priseEnCharge.ime);
     aff.ime_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.ime);
     ime->addWidget(aff.ime_oui);
     ime->addWidget(aff.ime_non);
     ime->addWidget(aff.ime_nonconnu);
     fl->addRow("IME", groupeIme);

     QGroupBox *groupeCams = new QGroupBox;
     QHBoxLayout *cams = new QHBoxLayout();
     groupeCams->setLayout(cams);
     cams->setAlignment(Qt::AlignLeft);
     aff.cams_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.cams);
     aff.cams_non = new RadioBouton("non", &questionnaireService->priseEnCharge.cams);
     aff.cams_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.cams);
     cams->addWidget(aff.cams_oui);
     cams->addWidget(aff.cams_non);
     cams->addWidget(aff.cams_nonconnu);
     fl->addRow("CAMS", groupeCams);

     QGroupBox *groupeHdj = new QGroupBox;
     QHBoxLayout *hdj = new QHBoxLayout();
     groupeHdj->setLayout(hdj);
     hdj->setAlignment(Qt::AlignLeft);
     aff.hopital_de_jour_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.hopital_de_jour);
     aff.hopital_de_jour_non = new RadioBouton("non", &questionnaireService->priseEnCharge.hopital_de_jour);
     aff.hopital_de_jour_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.hopital_de_jour);
     hdj->addWidget(aff.hopital_de_jour_oui);
     hdj->addWidget(aff.hopital_de_jour_non);
     hdj->addWidget(aff.hopital_de_jour_nonconnu);
     fl->addRow("Hôpital de jour", groupeHdj);

     QGroupBox *groupeUema = new QGroupBox;
     QHBoxLayout *uema = new QHBoxLayout();
     groupeUema->setLayout(uema);
     uema->setAlignment(Qt::AlignLeft);
     aff.uema_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.uema);
     aff.uema_non = new RadioBouton("non", &questionnaireService->priseEnCharge.uema);
     aff.uema_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.uema);
     uema->addWidget(aff.uema_oui);
     uema->addWidget(aff.uema_non);
     uema->addWidget(aff.uema_nonconnu);
     fl->addRow("UEMA", groupeUema);

     QGroupBox *groupeSessad = new QGroupBox;
     QHBoxLayout *sessad = new QHBoxLayout();
     groupeSessad->setLayout(sessad);
     sessad->setAlignment(Qt::AlignLeft);
     aff.sessad_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.sessad);
     aff.sessad_non = new RadioBouton("non", &questionnaireService->priseEnCharge.sessad);
     aff.sessad_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.sessad);
     sessad->addWidget(aff.sessad_oui);
     sessad->addWidget(aff.sessad_non);
     sessad->addWidget(aff.sessad_nonconnu);
     fl->addRow("SESSAD", groupeSessad);


     QGroupBox *groupeRased = new QGroupBox;
     QHBoxLayout *rased = new QHBoxLayout();
     groupeRased->setLayout(rased);
     rased->setAlignment(Qt::AlignLeft);
     aff.rased_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.rased);
     aff.rased_non = new RadioBouton("non", &questionnaireService->priseEnCharge.rased);
     aff.rased_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.rased);
     rased->addWidget(aff.rased_oui);
     rased->addWidget(aff.rased_non);
     rased->addWidget(aff.rased_nonconnu);
     fl->addRow("RASED", groupeRased);

     QGroupBox *groupeSegpa = new QGroupBox;
     QHBoxLayout *segpa = new QHBoxLayout();
     groupeSegpa->setLayout(segpa);
     segpa->setAlignment(Qt::AlignLeft);
     aff.segpa_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.segpa);
     aff.segpa_non = new RadioBouton("non", &questionnaireService->priseEnCharge.segpa);
     aff.segpa_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.segpa);
     segpa->addWidget(aff.segpa_oui);
     segpa->addWidget(aff.segpa_non);
     segpa->addWidget(aff.segpa_nonconnu);
     fl->addRow("SEGPA", groupeSegpa);

     QGroupBox *groupeUlis = new QGroupBox;
     QHBoxLayout *ulis = new QHBoxLayout();
     groupeUlis->setLayout(ulis);
     ulis->setAlignment(Qt::AlignLeft);
     aff.ulis_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.ulis);
     aff.ulis_non = new RadioBouton("non", &questionnaireService->priseEnCharge.ulis);
     aff.ulis_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.ulis);
     ulis->addWidget(aff.ulis_oui);
     ulis->addWidget(aff.ulis_non);
     ulis->addWidget(aff.ulis_nonconnu);
     fl->addRow("ULIS", groupeUlis);

     QGroupBox *groupeLiberal = new QGroupBox;
     QHBoxLayout *liberal = new QHBoxLayout();
     groupeLiberal->setLayout(liberal);
     liberal->setAlignment(Qt::AlignLeft);
     aff.liberal_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.liberal);
     aff.liberal_non = new RadioBouton("non", &questionnaireService->priseEnCharge.liberal);
     aff.liberal_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.liberal);
     liberal->addWidget(aff.liberal_oui);
     liberal->addWidget(aff.liberal_non);
     liberal->addWidget(aff.liberal_nonconnu);
     fl->addRow("Libéral", groupeLiberal);

     aff.autre_structure = new ChampTexte(&questionnaireService->priseEnCharge.autre_structure);
     fl->addRow("Autre, préciser : ", aff.autre_structure);

     QVBoxLayout *layout2 = new QVBoxLayout(pageC2);

     layout2->addWidget(new QLabel("De quels types de prise en charge bénéficie votre enfant ?"));

     QGroupBox *group2 = new QGroupBox;
        QFormLayout *fl2 = new QFormLayout;
        group2->setLayout(fl2);
        layout2->addWidget(group2);

        QGroupBox *groupeOrtho = new QGroupBox;
             QHBoxLayout *ortho = new QHBoxLayout();
             groupeOrtho->setLayout(ortho);
             ortho->setAlignment(Qt::AlignLeft);
             aff.orthophonie_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.orthophonie);
             aff.orthophonie_non = new RadioBouton("non", &questionnaireService->priseEnCharge.orthophonie);
             aff.orthophonie_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.orthophonie);
             ortho->addWidget(aff.orthophonie_oui);
             ortho->addWidget(aff.orthophonie_non);
             ortho->addWidget(aff.orthophonie_nonconnu);
             fl2->addRow("Orthophonie", groupeOrtho);

             QGroupBox *groupePsy = new QGroupBox;
             QHBoxLayout *psy = new QHBoxLayout();
             groupePsy->setLayout(psy);
             psy->setAlignment(Qt::AlignLeft);
             aff.psychomotricite_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.psychomotricite);
             aff.psychomotricite_non = new RadioBouton("non", &questionnaireService->priseEnCharge.psychomotricite);
             aff.psychomotricite_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.psychomotricite);
             psy->addWidget(aff.psychomotricite_oui);
             psy->addWidget(aff.psychomotricite_non);
             psy->addWidget(aff.psychomotricite_nonconnu);
             fl2->addRow("Psychomotricité", groupePsy);

             QGroupBox *groupeErgo = new QGroupBox;
             QHBoxLayout *ergo = new QHBoxLayout();
             groupeErgo->setLayout(ergo);
             ergo->setAlignment(Qt::AlignLeft);
             aff.ergotherapie_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.ergotherapie);
             aff.ergotherapie_non = new RadioBouton("non", &questionnaireService->priseEnCharge.ergotherapie);
             aff.ergotherapie_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.ergotherapie);
             ergo->addWidget(aff.ergotherapie_oui);
             ergo->addWidget(aff.ergotherapie_non);
             ergo->addWidget(aff.ergotherapie_nonconnu);
             fl2->addRow("Ergothérapie", groupeErgo);

             QGroupBox *groupeEdu = new QGroupBox;
             QHBoxLayout *edu = new QHBoxLayout();
             groupeEdu->setLayout(edu);
             edu->setAlignment(Qt::AlignLeft);
             aff.educatrice_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.educatrice);
             aff.educatrice_non = new RadioBouton("non", &questionnaireService->priseEnCharge.educatrice);
             aff.educatrice_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.educatrice);
             edu->addWidget(aff.educatrice_oui);
             edu->addWidget(aff.educatrice_non);
             edu->addWidget(aff.educatrice_nonconnu);
             fl2->addRow("Educatrice", groupeEdu);

             QGroupBox *groupePsycho = new QGroupBox;
             QHBoxLayout *psycho = new QHBoxLayout();
             groupePsycho->setLayout(psycho);
             psycho->setAlignment(Qt::AlignLeft);
             aff.psychologique_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.psychologie);
             aff.psychologique_non = new RadioBouton("non", &questionnaireService->priseEnCharge.psychologie);
             aff.psychologique_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.psychologie);
             psycho->addWidget(aff.psychologique_oui);
             psycho->addWidget(aff.psychologique_non);
             psycho->addWidget(aff.psychologique_nonconnu);
             fl2->addRow("Psychologie", groupePsycho);

             QGroupBox *groupeNeuro = new QGroupBox;
             QHBoxLayout *neuro = new QHBoxLayout();
             groupeNeuro->setLayout(neuro);
             neuro->setAlignment(Qt::AlignLeft);
             aff.neuropsychologique_oui = new RadioBouton("oui", &questionnaireService->priseEnCharge.neuropsychologie);
             aff.neuropsychologique_non = new RadioBouton("non", &questionnaireService->priseEnCharge.neuropsychologie);
             aff.neuropsychologique_nonconnu = new RadioBouton("non connu", &questionnaireService->priseEnCharge.neuropsychologie);
             neuro->addWidget(aff.neuropsychologique_oui);
             neuro->addWidget(aff.neuropsychologique_non);
             neuro->addWidget(aff.neuropsychologique_nonconnu);
             fl2->addRow("Neuropsychologie", groupeNeuro);

             aff.autre_prise_en_charge = new ChampTexte(&questionnaireService->priseEnCharge.autre_type);
             fl2->addRow("Autre, préciser : ", aff.autre_prise_en_charge);

     layout->addStretch();
     layout2->addStretch();

     for(RadioBouton *radio : aff.getListeRadioBouton()) {
         connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
     }
     for(ChampTexte *champ : aff.getListeChampTexte()) {
         connect(champ, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
     }
}

void Questionnaire::setPageD()
{

    aff_traitement_medicamentaux aff = affTraitementMedicamentaux;

    QVBoxLayout *layout = new QVBoxLayout(pageD);
    QGroupBox *group = new QGroupBox("Traitements médicamentaux actuels (y compris somatiques)");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupePr = new QGroupBox;
    QHBoxLayout *prend = new QHBoxLayout();
    groupePr->setLayout(prend);
    prend->setAlignment(Qt::AlignLeft);
     aff.prend_il_oui = new RadioBouton("oui", &questionnaireService->traitementMedicamentaux.prend_il_un_traitement);
     aff.prend_il_non = new RadioBouton("non", &questionnaireService->traitementMedicamentaux.prend_il_un_traitement);
     aff.prend_il_nonconnu = new RadioBouton("non connu", &questionnaireService->traitementMedicamentaux.prend_il_un_traitement);
     prend->addWidget(aff.prend_il_oui);
     prend->addWidget(aff.prend_il_non);
     prend->addWidget(aff.prend_il_nonconnu);
     fl->addRow("Votre enfant prend-il un traitement actuellement ?", groupePr);

     aff.preciser = new ChampTexte(&questionnaireService->traitementMedicamentaux.traitement);
     fl->addRow("Si oui, préciser : ", aff.preciser);

     for(RadioBouton *radio : aff.getListeRadioBouton()) {
         connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
     }
     connect(aff.preciser, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
}

void Questionnaire::setPageE()
{
    aff_sommeil_enfant aff = affSommeilEnfant;

    QVBoxLayout *layout = new QVBoxLayout(pageE);
    QGroupBox *group = new QGroupBox("Sommeil");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);


    QGroupBox *groupeDiffSom = new QGroupBox;
    QHBoxLayout *diffsom = new QHBoxLayout();
    groupeDiffSom->setLayout(diffsom);
    diffsom->setAlignment(Qt::AlignLeft);
     aff.diffsom_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.difficulte_de_sommeil);
     aff.diffsom_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.difficulte_de_sommeil);
     aff.diffsom_nonconnu = new RadioBouton("non connu", &questionnaireService->sommeilEnfant.difficulte_de_sommeil);
     diffsom->addWidget(aff.diffsom_oui);
     diffsom->addWidget(aff.diffsom_non);
     diffsom->addWidget(aff.diffsom_nonconnu);
     fl->addRow("Votre enfant présente-t-il des difficultés de sommeil ?", groupeDiffSom);

        QGroupBox *group2 = new QGroupBox("Si oui, précisez le type");
        QFormLayout *fl2 = new QFormLayout;
        group2->setLayout(fl2);

             QGroupBox *groupeEndorm = new QGroupBox;
             QHBoxLayout *endorm = new QHBoxLayout();
             groupeEndorm->setLayout(endorm);
             endorm->setAlignment(Qt::AlignLeft);
             aff.endorm_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.endormissement);
             aff.endorm_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.endormissement);
             endorm->addWidget(aff.endorm_oui);
             endorm->addWidget(aff.endorm_non);
             fl2->addRow("Endormissement", groupeEndorm);

             QGroupBox *groupeNocturne = new QGroupBox;
             QHBoxLayout *nocturne = new QHBoxLayout();
             groupeNocturne->setLayout(nocturne);
             nocturne->setAlignment(Qt::AlignLeft);
             aff.nocturne_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.reveil_nocturne);
             aff.nocturne_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.reveil_nocturne);
             nocturne->addWidget(aff.nocturne_oui);
             nocturne->addWidget(aff.nocturne_non);
             fl2->addRow("Réveil nocturne", groupeNocturne);

             QGroupBox *groupePrecoce = new QGroupBox;
             QHBoxLayout *precoce = new QHBoxLayout();
             groupePrecoce->setLayout(precoce);
             precoce->setAlignment(Qt::AlignLeft);
             aff.precoce_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.reveil_precoce);
             aff.precoce_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.reveil_precoce);
             precoce->addWidget(aff.precoce_oui);
             precoce->addWidget(aff.precoce_non);
             fl2->addRow("Réveil précoce", groupePrecoce);

        fl->addWidget(group2);

        QGroupBox *groupeApnee = new QGroupBox;
        QHBoxLayout *apnee = new QHBoxLayout();
        groupeApnee->setLayout(apnee);
        apnee->setAlignment(Qt::AlignLeft);
     aff.apnee_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.apnee_du_sommeil);
     aff.apnee_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.apnee_du_sommeil);
     aff.apnee_nonconnu = new RadioBouton("non connu", &questionnaireService->sommeilEnfant.apnee_du_sommeil);
     apnee->addWidget(aff.apnee_oui);
     apnee->addWidget(aff.apnee_non);
     apnee->addWidget(aff.apnee_nonconnu);
     fl->addRow("Votre enfant présente-t-il de l'apnée du sommeil ?", groupeApnee);

     QGroupBox *groupeTerreur = new QGroupBox;
     QHBoxLayout *terreur = new QHBoxLayout();
     groupeTerreur->setLayout(terreur);
     terreur->setAlignment(Qt::AlignLeft);
     aff.terreur_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.terreur_nocturne);
     aff.terreur_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.terreur_nocturne);
     aff.terreur_nonconnu = new RadioBouton("non connu", &questionnaireService->sommeilEnfant.terreur_nocturne);
     terreur->addWidget(aff.terreur_oui);
     terreur->addWidget(aff.terreur_non);
     terreur->addWidget(aff.terreur_nonconnu);
     fl->addRow("Votre enfant fait-il des terreurs nocturnes ?", groupeTerreur);

     QGroupBox *groupeFrequent = new QGroupBox;
     QHBoxLayout *frequent = new QHBoxLayout();
     groupeFrequent->setLayout(frequent);
     frequent->setAlignment(Qt::AlignLeft);
     aff.frequent_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.frequent_terreur_nocturne);
     aff.frequent_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.frequent_terreur_nocturne);
     aff.frequent_nonconnu = new RadioBouton("non connu", &questionnaireService->sommeilEnfant.frequent_terreur_nocturne);
     frequent->addWidget(aff.frequent_oui);
     frequent->addWidget(aff.frequent_non);
     frequent->addWidget(aff.frequent_nonconnu);
     fl->addRow("Si oui, est-ce fréquent ?", groupeFrequent);

     QGroupBox *groupeDiag = new QGroupBox;
     QHBoxLayout *diag = new QHBoxLayout();
     groupeDiag->setLayout(diag);
     diag->setAlignment(Qt::AlignLeft);
     aff.diag_trouble_oui = new RadioBouton("oui", &questionnaireService->sommeilEnfant.diagnostic_trouble_de_sommeil);
     aff.diag_trouble_non = new RadioBouton("non", &questionnaireService->sommeilEnfant.diagnostic_trouble_de_sommeil);
     aff.diag_trouble_nonconnu = new RadioBouton("non connu", &questionnaireService->sommeilEnfant.diagnostic_trouble_de_sommeil);
     diag->addWidget(aff.diag_trouble_oui);
     diag->addWidget(aff.diag_trouble_non);
     diag->addWidget(aff.diag_trouble_nonconnu);
     fl->addRow("Un diagnostic de trouble du sommeil a-t-il été posé ?", groupeDiag);

     for(RadioBouton *radio : aff.getListeRadioBouton()) {
         connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
     }
}

void Questionnaire::setPageF()
{
    aff_alimentation_enfant aff = affAlimentationEnfant;

    QVBoxLayout *layout = new QVBoxLayout(pageF);
    QGroupBox *group = new QGroupBox("Alimentation");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupeSelective = new QGroupBox;
    QHBoxLayout *selective = new QHBoxLayout();
    groupeSelective->setLayout(selective);
    selective->setAlignment(Qt::AlignLeft);
    aff.selective_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.presente_selectivite_alimentaire);
    aff.selective_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.presente_selectivite_alimentaire);
    aff.selective_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.presente_selectivite_alimentaire);
    selective->addWidget(aff.selective_oui);
    selective->addWidget(aff.selective_non);
    selective->addWidget(aff.selective_nonconnu);
    fl->addRow("Votre enfant présente-t-il une sélectivité alimentaire ?", groupeSelective);

    QGroupBox *groupeIntensite = new QGroupBox;
    QHBoxLayout *intensite = new QHBoxLayout();
    groupeIntensite->setLayout(intensite);
    intensite->setAlignment(Qt::AlignLeft);
    aff.du_tout = new RadioTexteBouton("Pas du tout", &questionnaireService->alimentationEnfant.intensite_selectivite);
    aff.un_peu = new RadioTexteBouton("Un peu", &questionnaireService->alimentationEnfant.intensite_selectivite);
    aff.souvent = new RadioTexteBouton("Souvent", &questionnaireService->alimentationEnfant.intensite_selectivite);
    aff.tout_le_temps = new RadioTexteBouton("Tout le temps", &questionnaireService->alimentationEnfant.intensite_selectivite);
    intensite->addWidget(aff.du_tout);
    intensite->addWidget(aff.un_peu);
    intensite->addWidget(aff.souvent);
    intensite->addWidget(aff.tout_le_temps);
    fl->addRow("Si oui, quelle st l'intensité de cette sélectivité alimentaire selon vous : ", groupeIntensite);

    QGroupBox *group2 = new QGroupBox("Si oui, préciser comment choisit-t-il ses aliments");
    QFormLayout *fl2 = new QFormLayout;
    group2->setLayout(fl2);
    fl->addWidget(group2);

        QGroupBox *groupeTexture = new QGroupBox;
        QHBoxLayout *texture = new QHBoxLayout();
        groupeTexture->setLayout(texture);
        texture->setAlignment(Qt::AlignLeft);
        aff.selon_texture_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.selon_structure);
        aff.selon_texture_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.selon_structure);
        aff.selon_texture_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.selon_structure);
        texture->addWidget(aff.selon_texture_oui);
        texture->addWidget(aff.selon_texture_non);
        texture->addWidget(aff.selon_texture_nonconnu);
        fl2->addRow("Selon leur texture", groupeTexture);

        QGroupBox *groupeCouleur = new QGroupBox;
        QHBoxLayout *couleur = new QHBoxLayout();
        groupeCouleur->setLayout(couleur);
        couleur->setAlignment(Qt::AlignLeft);
        aff.selon_couleur_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.selon_couleur);
        aff.selon_couleur_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.selon_couleur);
        aff.selon_couleur_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.selon_couleur);
        couleur->addWidget(aff.selon_couleur_oui);
        couleur->addWidget(aff.selon_couleur_non);
        couleur->addWidget(aff.selon_couleur_nonconnu);
        fl2->addRow("Selon leur couleur", groupeCouleur);

        QGroupBox *groupeTemp = new QGroupBox;
        QHBoxLayout *temp = new QHBoxLayout();
        groupeTemp->setLayout(temp);
        temp->setAlignment(Qt::AlignLeft);
        aff.selon_temp_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.selon_temperature);
        aff.selon_temp_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.selon_temperature);
        aff.selon_temp_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.selon_temperature);
        temp->addWidget(aff.selon_temp_oui);
        temp->addWidget(aff.selon_temp_non);
        temp->addWidget(aff.selon_temp_nonconnu);
        fl2->addRow("Selon leur température", groupeTemp);

        QGroupBox *groupeOdeur = new QGroupBox;
        QHBoxLayout *odeur = new QHBoxLayout();
        groupeOdeur->setLayout(odeur);
        odeur->setAlignment(Qt::AlignLeft);
        aff.selon_odeur_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.selon_odeur);
        aff.selon_odeur_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.selon_odeur);
        aff.selon_odeur_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.selon_odeur);
        odeur->addWidget(aff.selon_odeur_oui);
        odeur->addWidget(aff.selon_odeur_non);
        odeur->addWidget(aff.selon_odeur_nonconnu);
        fl2->addRow("Selon leur odeur", groupeOdeur);

        QGroupBox *groupeGout = new QGroupBox;
        QHBoxLayout *gout = new QHBoxLayout();
        groupeGout->setLayout(gout);
        gout->setAlignment(Qt::AlignLeft);
        aff.selon_gout_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.selon_gout);
        aff.selon_gout_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.selon_gout);
        aff.selon_gout_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.selon_gout);
        gout->addWidget(aff.selon_gout_oui);
        gout->addWidget(aff.selon_gout_non);
        gout->addWidget(aff.selon_gout_nonconnu);
        fl2->addRow("Selon leur goût", groupeGout);

    fl->addWidget(new QLabel("Si oui, préciser : "));

    QGroupBox *groupeMastication = new QGroupBox;
    QHBoxLayout *mastication = new QHBoxLayout();
    groupeMastication->setLayout(mastication);
    mastication->setAlignment(Qt::AlignLeft);
    aff.pd_mastication_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.pb_mastication);
    aff.pd_mastication_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.pb_mastication);
    aff.pd_mastication_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.pb_mastication);
    mastication->addWidget(aff.pd_mastication_oui);
    mastication->addWidget(aff.pd_mastication_non);
    mastication->addWidget(aff.pd_mastication_nonconnu);
    fl->addRow("Votre enfant présente-t-il des problèmes de mastication ?", groupeMastication);

    QGroupBox *grouptDeglutir = new QGroupBox;
    QHBoxLayout *deglutir = new QHBoxLayout();
    grouptDeglutir->setLayout(deglutir);
    deglutir->setAlignment(Qt::AlignLeft);
    aff.pb_deglutir_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.pb_deglutir);
    aff.pb_deglutir_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.pb_deglutir);
    aff.pb_deglutir_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.pb_deglutir);
    deglutir->addWidget(aff.pb_deglutir_oui);
    deglutir->addWidget(aff.pb_deglutir_non);
    deglutir->addWidget(aff.pb_deglutir_nonconnu);
    fl->addRow("Votre enfant a-t-il des difficultés pour déglutir ?", grouptDeglutir);

    QGroupBox *groupeDigestion = new QGroupBox;
    QHBoxLayout *digestion = new QHBoxLayout();
    groupeDigestion->setLayout(digestion);
    digestion->setAlignment(Qt::AlignLeft);
    aff.pb_digestion_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.pb_digestion);
    aff.pb_digestion_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.pb_digestion);
    aff.pb_digestion_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.pb_digestion);
    digestion->addWidget(aff.pb_digestion_oui);
    digestion->addWidget(aff.pb_digestion_non);
    digestion->addWidget(aff.pb_digestion_nonconnu);
    fl->addRow("Votre enfant a-t-il des problèmes de digestion ?", groupeDigestion);

    fl->addWidget(new QLabel("Si oui, préciser : "));

    QGroupBox *groupeDiag = new QGroupBox;
    QHBoxLayout *diag = new QHBoxLayout();
    groupeDiag->setLayout(diag);
    diag->setAlignment(Qt::AlignLeft);
    aff.diag_trouble_comp_oui = new RadioBouton("oui", &questionnaireService->alimentationEnfant.diag_trouble_comportement_alimentaire);
    aff.diag_trouble_comp_non = new RadioBouton("non", &questionnaireService->alimentationEnfant.diag_trouble_comportement_alimentaire);
    aff.diag_trouble_comp_nonconnu = new RadioBouton("non connu", &questionnaireService->alimentationEnfant.diag_trouble_comportement_alimentaire);
    diag->addWidget(aff.diag_trouble_comp_oui);
    diag->addWidget(aff.diag_trouble_comp_non);
    diag->addWidget(aff.diag_trouble_comp_nonconnu);
    fl->addRow("Un diagnostic du trouble du comportement alimentaire a-t-il été posé ?", groupeDiag);

    for(RadioBouton *radio : aff.getListeRadioBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
    }
    for (RadioTexteBouton *radio : aff.getListeRadioTexteBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioTexteBouton(bool)));
    }
}

void Questionnaire::setPageG()
{
    aff_langage_enfant aff = affLangageEnfant;

    QVBoxLayout *layout = new QVBoxLayout(pageG);
    QGroupBox *group = new QGroupBox("Langage");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupeNiveau = new QGroupBox;
    QHBoxLayout *niveau = new QHBoxLayout();
    groupeNiveau->setLayout(niveau);
    niveau->setAlignment(Qt::AlignLeft);
     aff.verbal = new RadioTexteBouton("Verbal", &questionnaireService->langageEnfant.niveau_langage);
     aff.phrases = new RadioTexteBouton("Quelques phrases", &questionnaireService->langageEnfant.niveau_langage);
     aff.mots = new RadioTexteBouton("Quelques mots", &questionnaireService->langageEnfant.niveau_langage);
     aff.nonverbal = new RadioTexteBouton("Non verbal", &questionnaireService->langageEnfant.niveau_langage);
     niveau->addWidget(aff.verbal);
     niveau->addWidget(aff.phrases);
     niveau->addWidget(aff.mots);
     niveau->addWidget(aff.nonverbal);
     fl->addRow("Quel est le niveau de langage de votre enfant ?", groupeNiveau);

     aff.age_premiers_mots = new ChampTexte(&questionnaireService->langageEnfant.age_premiers_mots);
     fl->addRow("Quel est l'âge auquel votre enfant a eu ses premiers mots (mois) ?", aff.age_premiers_mots);

     connect(aff.age_premiers_mots, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
     for (RadioTexteBouton *radio : aff.getListeRadioTexteBouton()) {
         connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioTexteBouton(bool)));
     }
}

void Questionnaire::setPageH()
{
    aff_moteur_enfant aff = affMoteurEnfant;

    QVBoxLayout *layout = new QVBoxLayout(pageh);
    QGroupBox *group = new QGroupBox("Moteur");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupeRetard = new QGroupBox;
    QHBoxLayout *retard = new QHBoxLayout();
    groupeRetard->setLayout(retard);
    retard->setAlignment(Qt::AlignLeft);
    aff.retard_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.retard_moteur);
    aff.retard_non = new RadioBouton("non", &questionnaireService->moteurEnfant.retard_moteur);
    aff.retard_nonconnu = new RadioBouton("non connu", &questionnaireService->moteurEnfant.retard_moteur);
    retard->addWidget(aff.retard_oui);
    retard->addWidget(aff.retard_non);
    retard->addWidget(aff.retard_nonconnu);
    fl->addRow("Votre enfant présente-t-il un retard sur le plan moteur ?", groupeRetard);

    aff.age_marche = new ChampTexte(&questionnaireService->moteurEnfant.age_premiere_marche);
    fl->addRow("Quel est son âge d'acquisition de la marche(mois) ?", aff.age_marche);

    QGroupBox *groupeDyspraxie = new QGroupBox;
    QHBoxLayout *dyspraxie = new QHBoxLayout();
    groupeDyspraxie->setLayout(dyspraxie);
    dyspraxie->setAlignment(Qt::AlignLeft);
    aff.dyspraxie_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.diagnostice_de_dyspraxie);
    aff.dyspraxie_non = new RadioBouton("non", &questionnaireService->moteurEnfant.diagnostice_de_dyspraxie);
    aff.dyspraxie_nonconnu = new RadioBouton("oui", &questionnaireService->moteurEnfant.diagnostice_de_dyspraxie);
    dyspraxie->addWidget(aff.dyspraxie_oui);
    dyspraxie->addWidget(aff.dyspraxie_non);
    dyspraxie->addWidget(aff.dyspraxie_nonconnu);
    fl->addRow("Est-ce que votre enfant a un diagnostic de dyspraxie ?", groupeDyspraxie);

    //    Si non
    fl->addWidget(new QLabel("Si non,"));

    QGroupBox *groupeCoord = new QGroupBox;
    QHBoxLayout *coord = new QHBoxLayout();
    groupeCoord->setLayout(coord);
    coord->setAlignment(Qt::AlignLeft);
    aff.coordination_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.probleme_de_coordination);
    aff.coordination_non = new RadioBouton("non", &questionnaireService->moteurEnfant.probleme_de_coordination);
    aff.coordination_nonconnu = new RadioBouton("non connu", &questionnaireService->moteurEnfant.probleme_de_coordination);;
    coord->addWidget(aff.coordination_oui);
    coord->addWidget(aff.coordination_non);
    coord->addWidget(aff.coordination_nonconnu);
    fl->addRow("Est-ce que votre enfant présente des problèmes de coordination ?", groupeCoord);

    QGroupBox *groupeLater = new QGroupBox;
    QHBoxLayout *later = new QHBoxLayout();
    groupeLater->setLayout(later);
    later->setAlignment(Qt::AlignLeft);
    aff.lateralisation_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.difficulte_de_lateralisation);
    aff.lateralisation_non = new RadioBouton("non", &questionnaireService->moteurEnfant.difficulte_de_lateralisation);
    aff.lateralisation_nonconnu = new RadioBouton("non connu", &questionnaireService->moteurEnfant.difficulte_de_lateralisation);;
    later->addWidget(aff.lateralisation_oui);
    later->addWidget(aff.lateralisation_non);
    later->addWidget(aff.lateralisation_nonconnu);
    fl->addRow("Est-ce que votre enfant présente des difficultés de latéralisation ?", groupeLater);

    QGroupBox *groupeReper = new QGroupBox;
    QHBoxLayout *reper = new QHBoxLayout();
    groupeReper->setLayout(reper);
    reper->setAlignment(Qt::AlignLeft);
    aff.reperer_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.difficulte_de_reperer_dans_lespace);
    aff.reperer_non = new RadioBouton("non", &questionnaireService->moteurEnfant.difficulte_de_reperer_dans_lespace);
    aff.reperer_nonconnu = new RadioBouton("non connu", &questionnaireService->moteurEnfant.difficulte_de_reperer_dans_lespace);;
    reper->addWidget(aff.reperer_oui);
    reper->addWidget(aff.reperer_non);
    reper->addWidget(aff.reperer_nonconnu);
    fl->addRow("Est-ce que votre enfant présente des difficultés pour se repérer dans l'espace ?", groupeReper);

    QGroupBox *groupeMotri = new QGroupBox;
    QHBoxLayout *motri = new QHBoxLayout();
    groupeMotri->setLayout(motri);
    motri->setAlignment(Qt::AlignLeft);
    aff.motricite_oui = new RadioBouton("oui", &questionnaireService->moteurEnfant.difficulte_de_motricite_fine);
    aff.motricite_non = new RadioBouton("non", &questionnaireService->moteurEnfant.difficulte_de_motricite_fine);
    aff.motricite_nonconnu = new RadioBouton("non connu", &questionnaireService->moteurEnfant.difficulte_de_motricite_fine);;
    motri->addWidget(aff.motricite_oui);
    motri->addWidget(aff.motricite_non);
    motri->addWidget(aff.motricite_nonconnu);
    fl->addRow("Est-ce que votre enfant présente des difficultés de motricité fine ?", groupeMotri);

    for(RadioBouton *radio : aff.getListeRadioBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
    }
    connect(aff.age_marche, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));
}

void Questionnaire::setPageI()
{
    aff_apprentissages_enfant aff = affApprentissagesEnfant;

    QVBoxLayout *layout = new QVBoxLayout(pageI);
    QGroupBox *group = new QGroupBox("Apprentissages");
    QFormLayout *fl = new QFormLayout;
    layout->addWidget(group);
    group->setLayout(fl);

    QGroupBox *groupeDyslexie = new QGroupBox;
    QHBoxLayout *dyslexie = new QHBoxLayout();
    groupeDyslexie->setLayout(dyslexie);
    dyslexie->setAlignment(Qt::AlignLeft);
    aff.dyslexie_oui = new RadioBouton("oui", &questionnaireService->apprentissageEnfant.presente_dyslexie);
    aff.dyslexie_non = new RadioBouton("non", &questionnaireService->apprentissageEnfant.presente_dyslexie);
    aff.dyslexie_nonconnu = new RadioBouton("non connu", &questionnaireService->apprentissageEnfant.presente_dyslexie);
    dyslexie->addWidget(aff.dyslexie_oui);
    dyslexie->addWidget(aff.dyslexie_non);
    dyslexie->addWidget(aff.dyslexie_nonconnu);
    fl->addRow("Votre enfant présente-t-il une dyslexie ?", groupeDyslexie);

    QGroupBox *groupeLecture = new QGroupBox;
    QHBoxLayout *lecture = new QHBoxLayout();
    groupeLecture->setLayout(lecture);
    lecture->setAlignment(Qt::AlignLeft);
    aff.lecture_oui = new RadioBouton("oui", &questionnaireService->apprentissageEnfant.difficulte_lecture);
    aff.lecture_non = new RadioBouton("non", &questionnaireService->apprentissageEnfant.difficulte_lecture);
    aff.lecture_nonconnu = new RadioBouton("non connu", &questionnaireService->apprentissageEnfant.difficulte_lecture);
    lecture->addWidget(aff.lecture_oui);
    lecture->addWidget(aff.lecture_non);
    lecture->addWidget(aff.lecture_nonconnu);
    fl->addRow("Votre enfant a-t-il des difficultés d'apprentissage de la lecture ?", groupeLecture);

    QGroupBox *groupeEcriture = new QGroupBox;
    QHBoxLayout *ecriture = new QHBoxLayout();
    groupeEcriture->setLayout(ecriture);
    ecriture->setAlignment(Qt::AlignLeft);
    aff.ecriture_oui = new RadioBouton("oui", &questionnaireService->apprentissageEnfant.difficulte_ecriture);
    aff.ecriture_non = new RadioBouton("non", &questionnaireService->apprentissageEnfant.difficulte_ecriture);
    aff.ecriture_nonconnu = new RadioBouton("non connu", &questionnaireService->apprentissageEnfant.difficulte_ecriture);
    ecriture->addWidget(aff.ecriture_oui);
    ecriture->addWidget(aff.ecriture_non);
    ecriture->addWidget(aff.ecriture_nonconnu);
    fl->addRow("Votre enfant a-t-il des difficultés d'apprentissage de l'écriture ?", groupeEcriture);

    QGroupBox *groupeCalcul = new QGroupBox;
    QHBoxLayout *calcul = new QHBoxLayout();
    groupeCalcul->setLayout(calcul);
    calcul->setAlignment(Qt::AlignLeft);
    aff.calcul_oui = new RadioBouton("oui", &questionnaireService->apprentissageEnfant.difficulte_calcul);
    aff.calcul_non = new RadioBouton("non", &questionnaireService->apprentissageEnfant.difficulte_calcul);
    aff.calcul_nonconnu = new RadioBouton("non connu", &questionnaireService->apprentissageEnfant.difficulte_calcul);
    calcul->addWidget(aff.calcul_oui);
    calcul->addWidget(aff.calcul_non);
    calcul->addWidget(aff.calcul_nonconnu);
    fl->addRow("Votre enfant a-t-il des difficultés d'apprentissage du calcul ?", groupeCalcul);

    aff.Autre = new ChampTexte(&questionnaireService->apprentissageEnfant.autre);
    fl->addRow("Autre, préciser : ", aff.Autre);

    for(RadioBouton *radio : aff.getListeRadioBouton()) {
        connect(radio, SIGNAL(toggled(bool)), this, SLOT(onClickRadioBouton(bool)));
    }
    connect(aff.Autre, SIGNAL(editingFinished()), this, SLOT(onEditChampTexte()));

    QPushButton *bt_enregistrer = new QPushButton("Enregistrer");
    bt_enregistrer->setStyleSheet("color : white; background-color: rgb(0,168,243);");
    bt_enregistrer->setFont(QFont("Times", 20));

    layout->addStretch();
    layout->addWidget(bt_enregistrer);

    connect(bt_enregistrer, SIGNAL(clicked()), this, SLOT(enregistrer()));
}


QVector<RadioBouton *> aff_trouble_du_spectre::getListeRadioBouton()
{
    QVector <RadioBouton*> retour;
    retour.push_back(diag_tsa_oui);
    retour.push_back(diag_tsa_non);
    retour.push_back(diag_tsa_nonconnu);
    retour.push_back(taah_oui);
    retour.push_back(taah_non);
    retour.push_back(taah_nonconnu);
    retour.push_back(tash_oui);
    retour.push_back(tash_non);
    retour.push_back(tash_nonconnu);
    retour.push_back(tcs_oui);
    retour.push_back(tcs_non);
    retour.push_back(tcs_nonconnu);
    retour.push_back(tcns_oui);
    retour.push_back(tcns_non);
    retour.push_back(tcns_nonconnu);
    retour.push_back(tm_oui);
    retour.push_back(tm_non);
    retour.push_back(tm_nonconnu);
    retour.push_back(tda_oui);
    retour.push_back(tda_non);
    retour.push_back(tda_nonconnu);
    retour.push_back(tdp_oui);
    retour.push_back(tdp_non);
    retour.push_back(tdp_nonconnu);
    return retour;
}

QVector<ChampTexte *> aff_trouble_du_spectre::getListeChampTexte()
{
    QVector<ChampTexte *> retour;
    retour.push_back(aQuelAge);
    retour.push_back(poser_par);
    retour.push_back(adi);
    retour.push_back(ados);
    retour.push_back(qui);
    retour.push_back(autre_test);
    retour.push_back(autre_trouble);
    return retour;
}

QVector<RadioBouton *> aff_autre_diagnostic::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(ta_oui);
    retour.push_back(ta_non);
    retour.push_back(ta_nonconnu);
    retour.push_back(toc_oui);
    retour.push_back(toc_non);
    retour.push_back(toc_nonconnu);
    retour.push_back(tspt_oui);
    retour.push_back(tspt_non);
    retour.push_back(tspt_nonconnu);
    return retour;
}

QVector<RadioTexteBouton *> aff_autre_diagnostic::getListeRadioTexteBouton()
{
    QVector<RadioTexteBouton *> retour;
    retour.push_back(specifique);
    retour.push_back(sociale);
    retour.push_back(panique);
    retour.push_back(angoraphobie);
    retour.push_back(general);
    return retour;
}

QVector<RadioBouton *> aff_prise_encharge::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(ime_oui);
    retour.push_back(ime_non);
    retour.push_back(ime_nonconnu);
    retour.push_back(cams_oui);
    retour.push_back(cams_non);
    retour.push_back(cams_nonconnu);
    retour.push_back(hopital_de_jour_oui);
    retour.push_back(hopital_de_jour_non);
    retour.push_back(hopital_de_jour_nonconnu);
    retour.push_back(uema_oui);
    retour.push_back(uema_non);
    retour.push_back(uema_nonconnu);
    retour.push_back(sessad_oui);
    retour.push_back(sessad_non);
    retour.push_back(sessad_nonconnu);
    retour.push_back(rased_oui);
    retour.push_back(rased_non);
    retour.push_back(rased_nonconnu);
    retour.push_back(segpa_oui);
    retour.push_back(segpa_non);
    retour.push_back(segpa_nonconnu);
    retour.push_back(ulis_oui);
    retour.push_back(ulis_non);
    retour.push_back(ulis_nonconnu);
    retour.push_back(liberal_oui);
    retour.push_back(liberal_non);
    retour.push_back(liberal_nonconnu);
    retour.push_back(orthophonie_oui);
    retour.push_back(orthophonie_non);
    retour.push_back(orthophonie_nonconnu);
    retour.push_back(psychomotricite_oui);
    retour.push_back(psychomotricite_non);
    retour.push_back(psychomotricite_nonconnu);
    retour.push_back(ergotherapie_oui);
    retour.push_back(ergotherapie_non);
    retour.push_back(ergotherapie_nonconnu);
    retour.push_back(educatrice_oui);
    retour.push_back(educatrice_non);
    retour.push_back(educatrice_nonconnu);
    retour.push_back(psychologique_oui);
    retour.push_back(psychologique_non);
    retour.push_back(psychologique_nonconnu);
    retour.push_back(neuropsychologique_oui);
    retour.push_back(neuropsychologique_non);
    retour.push_back(neuropsychologique_nonconnu);
    return retour;
}

QVector<ChampTexte *> aff_prise_encharge::getListeChampTexte()
{
    QVector<ChampTexte *> retour;
    retour.push_back(autre_structure);
    retour.push_back(autre_prise_en_charge);
    return retour;
}

QVector<RadioBouton *> aff_traitement_medicamentaux::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(prend_il_oui);
    retour.push_back(prend_il_non);
    retour.push_back(prend_il_nonconnu);

    return retour;
}

QVector<RadioBouton *> aff_sommeil_enfant::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(diffsom_oui);
    retour.push_back(diffsom_non);
    retour.push_back(diffsom_nonconnu);
    retour.push_back(endorm_oui);
    retour.push_back(endorm_non);
    retour.push_back(nocturne_oui);
    retour.push_back(nocturne_non);
    retour.push_back(precoce_oui);
    retour.push_back(precoce_non);
    retour.push_back(apnee_oui);
    retour.push_back(apnee_non);
    retour.push_back(apnee_nonconnu);
    retour.push_back(terreur_oui);
    retour.push_back(terreur_non);
    retour.push_back(terreur_nonconnu);
    retour.push_back(frequent_oui);
    retour.push_back(frequent_non);
    retour.push_back(frequent_nonconnu);
    retour.push_back(diag_trouble_oui);
    retour.push_back(diag_trouble_non);
    retour.push_back(diag_trouble_nonconnu);
    return retour;
}

QVector<RadioBouton *> aff_alimentation_enfant::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(selective_oui);
    retour.push_back(selective_non);
    retour.push_back(selective_nonconnu);
    retour.push_back(selon_texture_oui);
    retour.push_back(selon_texture_non);
    retour.push_back(selon_texture_nonconnu);
    retour.push_back(selon_couleur_oui);
    retour.push_back(selon_couleur_non);
    retour.push_back(selon_couleur_nonconnu);
    retour.push_back(selon_temp_oui);
    retour.push_back(selon_temp_non);
    retour.push_back(selon_temp_nonconnu);
    retour.push_back(selon_odeur_oui);
    retour.push_back(selon_odeur_non);
    retour.push_back(selon_odeur_nonconnu);
    retour.push_back(selon_gout_oui);
    retour.push_back(selon_gout_non);
    retour.push_back(selon_gout_nonconnu);
    retour.push_back(pd_mastication_oui);
    retour.push_back(pd_mastication_non);
    retour.push_back(pd_mastication_nonconnu);
    retour.push_back(pb_deglutir_oui);
    retour.push_back(pb_deglutir_non);
    retour.push_back(pb_deglutir_nonconnu);
    retour.push_back(pb_digestion_oui);
    retour.push_back(pb_digestion_non);
    retour.push_back(pb_digestion_nonconnu);
    retour.push_back(diag_trouble_comp_oui);
    retour.push_back(diag_trouble_comp_non);
    retour.push_back(diag_trouble_comp_nonconnu);
    return retour;
}

QVector<RadioTexteBouton *> aff_alimentation_enfant::getListeRadioTexteBouton()
{
    QVector<RadioTexteBouton *> retour;
    retour.push_back(du_tout);
    retour.push_back(un_peu);
    retour.push_back(souvent);
    retour.push_back(tout_le_temps);
    return retour;
}

QVector<RadioBouton *> aff_moteur_enfant::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(retard_oui);
    retour.push_back(retard_non);
    retour.push_back(retard_nonconnu);
    retour.push_back(dyspraxie_oui);
    retour.push_back(dyspraxie_non);
    retour.push_back(dyspraxie_nonconnu);
    retour.push_back(coordination_oui);
    retour.push_back(coordination_non);
    retour.push_back(coordination_nonconnu);
    retour.push_back(lateralisation_oui);
    retour.push_back(lateralisation_non);
    retour.push_back(lateralisation_nonconnu);
    retour.push_back(reperer_oui);
    retour.push_back(reperer_non);
    retour.push_back(reperer_nonconnu);
    retour.push_back(motricite_oui);
    retour.push_back(motricite_non);
    retour.push_back(motricite_nonconnu);
    return retour;
}

QVector<RadioBouton *> aff_apprentissages_enfant::getListeRadioBouton()
{
    QVector<RadioBouton *> retour;
    retour.push_back(dyslexie_oui);
    retour.push_back(dyslexie_non);
    retour.push_back(dyslexie_nonconnu);
    retour.push_back(lecture_oui);
    retour.push_back(lecture_non);
    retour.push_back(lecture_nonconnu);
    retour.push_back(ecriture_oui);
    retour.push_back(ecriture_non);
    retour.push_back(ecriture_nonconnu);
    retour.push_back(calcul_oui);
    retour.push_back(calcul_non);
    retour.push_back(calcul_nonconnu);
    return retour;
}

QVector<RadioTexteBouton *> aff_langage_enfant::getListeRadioTexteBouton()
{
    QVector<RadioTexteBouton *> retour;
    retour.push_back(verbal);
    retour.push_back(phrases);
    retour.push_back(mots);
    retour.push_back(nonverbal);
    return retour;
}
