#include "formulaireutilisateur.h"
#include "fenetre.h"

FormulaireUtilisateur::FormulaireUtilisateur(MemoireService *memoireService,AttentionService *attentionService, Fenetre *fenetre,QString destination ,QWidget *parent)
    : QWidget{parent}
{
    this->memoireService =memoireService;
    this->attentionService = attentionService;
    this->destination = destination;
    this->fenetre = fenetre;
    init();
}

FormulaireUtilisateur::~FormulaireUtilisateur()
{
   delete utilisateur;
}

void FormulaireUtilisateur::onClickHopital()
{
    utilisateur->setLieu(1);
    stackedWidget->setCurrentWidget(page_genre);
}

void FormulaireUtilisateur::onClickEcole()
{
    utilisateur->setLieu(2);
    stackedWidget->setCurrentWidget(page_genre);
}

void FormulaireUtilisateur::onClickFille()
{
    utilisateur->setGenre('f');
    stackedWidget->setCurrentIndex(2);
}

void FormulaireUtilisateur::onClickGarcon()
{
    utilisateur->setGenre('m');
    stackedWidget->setCurrentIndex(2);
}

void FormulaireUtilisateur::onValiderId()
{
    QString str = input_id->text();
    qDebug() << str;
    utilisateur->setId(str);
    stackedWidget->setCurrentIndex(3);
}

void FormulaireUtilisateur::onValiderDtn()
{
    QString dtn = input_annee->currentText() + "/" + QString::number(input_mois->currentIndex()) + "/" + input_jour->currentText();
    utilisateur->setDate_naissance(dtn);
    memoireService->setUtilisateur(*utilisateur);
    attentionService->setUtilisateur(*utilisateur);

    if(destination == "memoire") {
        fenetre->versInstruction("memoire");
    } else if (destination == "attention") {
        fenetre->versInstruction("attention");
    }
    qDebug() << dtn;
}




void FormulaireUtilisateur::init()
{
    utilisateur = new Utilisateur;

    QVBoxLayout *vboxlayout = new QVBoxLayout(this);

    stackedWidget = new QStackedWidget;
    stackedWidget->resize(this->size());
    vboxlayout->addWidget(stackedWidget);

    page_lieu = new QWidget;
    setPageLieu();
    page_genre = new QWidget;
    setPageGenre();
    page_id = new QWidget;
    setPageId();
    page_dtn = new QWidget;
    setPageDtn();

    stackedWidget->addWidget(page_lieu);
    stackedWidget->addWidget(page_genre);
    stackedWidget->addWidget(page_id);
    stackedWidget->addWidget(page_dtn);

    stackedWidget->setCurrentIndex(0);
}

void FormulaireUtilisateur::setPageLieu()
{
    QPushButton *hopital = new QPushButton("Hôpital");
    hopital->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    hopital->setMaximumWidth(400);
    hopital->setMinimumHeight(85);
    QPushButton *ecole = new QPushButton("Ecole");
    ecole->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    ecole->setMaximumWidth(400);
    ecole->setMinimumHeight(85);

    QVBoxLayout *vboxlayout = new QVBoxLayout(page_lieu);
    QHBoxLayout *hboxlayout = new QHBoxLayout;

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(hopital, 0, 0);
    grid->addWidget(ecole, 0, 1);

    hboxlayout->addSpacing(1);
    hboxlayout->addLayout(grid);
    hboxlayout->addSpacing(1);

    vboxlayout->addSpacing(1);
    vboxlayout->addLayout(hboxlayout);
    vboxlayout->addSpacing(1);

    connect(hopital, SIGNAL(clicked()), this, SLOT(onClickHopital()));
    connect(ecole, SIGNAL(clicked()), this, SLOT(onClickEcole()));
}

void FormulaireUtilisateur::setPageGenre()
{
    QPushButton *fille = new QPushButton("Fille");
    fille->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    fille->setMaximumWidth(400);
    fille->setMinimumHeight(85);
    QPushButton *garcon = new QPushButton("Garçon");
    garcon->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    garcon->setMaximumWidth(400);
    garcon->setMinimumHeight(85);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(fille, 0, 0);
    grid->addWidget(garcon, 0, 1);

    QHBoxLayout *hboxlayout = new QHBoxLayout(page_genre);
    hboxlayout->addSpacing(1);
    hboxlayout->addLayout(grid);
    hboxlayout->addSpacing(1);

    connect(fille, SIGNAL(clicked()), this, SLOT(onClickFille()));
    connect(garcon, SIGNAL(clicked()), this, SLOT(onClickGarcon()));
}

void FormulaireUtilisateur::setPageId()
{
    input_id = new QLineEdit;
    input_id->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    input_id->setMaximumWidth(800);
    input_id->setMinimumHeight(85);

    QPushButton *valider = new QPushButton("Valider");
    valider->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    valider->setMaximumWidth(300);
    valider->setMinimumHeight(75);

    QLabel *label = new QLabel("ID participant");
    label->setStyleSheet("color: white; font-size: 25px;");

//    QGridLayout *grid = new QGridLayout;
//    grid->addWidget(label, 0,0);
//    grid->addWidget(id, 1,0);
//    grid->addWidget(valider, 2,0);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addStretch();
    vlayout->addWidget(label);
    vlayout->addWidget(input_id);
    vlayout->addWidget(valider);
    vlayout->addStretch();

    QHBoxLayout *hlayout = new QHBoxLayout(page_id);
    hlayout->addLayout(vlayout);

    connect(valider, SIGNAL(clicked()), this, SLOT(onValiderId()));
}

void FormulaireUtilisateur::setPageDtn()
{
    QLabel *label = new QLabel("Date de naissance");
    label->setStyleSheet("color: white; font-size: 25px;");
    label->setAlignment(Qt::AlignCenter);

    input_mois = new QComboBox;
    input_mois->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 10px; text-align: center;");
    input_mois->addItem("Mois");
    input_mois->setMaximumSize(250, 85);
    input_jour = new QComboBox;
    input_jour->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 10px; text-align: center;");
    input_jour->addItem("Jour");
    input_jour->setMaximumSize(250, 85);
    input_annee = new QComboBox;
    input_annee->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 10px; text-align: center;");
    input_annee->addItem("Année");
    input_annee->setMaximumSize(250, 85);

    QPushButton *valider = new QPushButton("valider");
    valider->setStyleSheet("color : white; font-size: 25px; border-style: outset; border-width: 1px; border-color: white; margin: 20px;");
    valider->setMaximumWidth(300);
    valider->setMinimumHeight(75);

    QStringList listeMois = Utilitaire::getListeMois();
    foreach (QString mois, listeMois) {
        input_mois->addItem(mois);
    }
    for(int i=1;i<=31; i++) {
        input_jour->addItem(QString::number(i));
    }
    for(int i=2022; i>=1900; i--) {
        input_annee->addItem(QString::number(i));
    }

    QHBoxLayout *layoutTitre = new QHBoxLayout;
    layoutTitre->addStretch();
    layoutTitre->addWidget(label, Qt::AlignCenter);
    layoutTitre->addStretch();

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(input_mois);
    hlayout->addWidget(input_jour);
    hlayout->addWidget(input_annee);
    hlayout->addStretch();

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(valider);

    QVBoxLayout *vlayout = new QVBoxLayout(page_dtn);
    vlayout->addStretch();
    vlayout->addLayout(layoutTitre);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout2);
    vlayout->addStretch();

    connect(valider, SIGNAL(clicked()), this, SLOT(onValiderDtn()));
}

QStackedWidget *FormulaireUtilisateur::getStackedWidget() const
{
    return stackedWidget;
}
