#include "mainmenu.h"
#include "fenetre.h"



MainMenu::MainMenu (MemoireService* memoireService, AttentionService* attentionService, Fenetre *f, QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;
    this->memoireService = memoireService;
    this->attentionService = attentionService;

    QPixmap img("assets/images/femme.png");
    QLabel *femme = new QLabel(this);
    int largeur_femme = 200 , hauteur_femme = 400;
    img = img.scaled(largeur_femme, hauteur_femme, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    femme->setPixmap(img);
    femme->resize(largeur_femme, hauteur_femme);
    femme->move(fenetre->width() - largeur_femme - 100, fenetre->height() - hauteur_femme);


    setStyleSheet("background-color: rgb(14,14,14);");

    init();
    listen_bt();
}

void MainMenu::onClickMemoire()
{
    fenetre->versFormulaireUtilisateur("memoire");
}

void MainMenu::onClickAttention()
{
    fenetre->versFormulaireUtilisateur("attention");
}

void MainMenu::onClickSensoriel()
{
    fenetre->versMenuSensorielPage();
}

void MainMenu::onClickQuestionnaire()
{
    fenetre->versQuestionnairePage();
}

void MainMenu::init()
{
    QGridLayout *grid= new QGridLayout;

    bt_memoire = new QPushButton("Mémoire");
    bt_memoire->setStyleSheet("background-color : rgb(157,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_memoire->setMaximumWidth(300);
    bt_memoire->setFont(QFont("Times", 27));

    bt_attention = new QPushButton("Attention");
    bt_attention->setStyleSheet("background-color : rgb(125, 155, 183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_attention->setMaximumWidth(300);
    bt_attention->setFont(QFont("Times", 27));

    bt_sensoriel = new QPushButton("Sensoriel");
    bt_sensoriel->setStyleSheet("background-color : rgb(81, 113, 180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_sensoriel->setMaximumWidth(300);
    bt_sensoriel->setFont(QFont("Times", 27));

    bt_questionnaire = new QPushButton("Questionnaire");
    bt_questionnaire->setStyleSheet("background-color : rgb(32, 56, 100); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_questionnaire->setMaximumWidth(300);
    bt_questionnaire->setFont(QFont("Times", 27));

    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addStretch();
    vboxLayout->addLayout(grid);

    QPushButton *bt_quitter = new QPushButton("Quitter");
    bt_quitter->setStyleSheet("background-color : white; color: black; width: 250px; height: 50px; border-radius: 13px; margin: 10px;");
    bt_quitter->setMaximumWidth(300);
    bt_quitter->setFont(QFont("Times", 22));
    vboxLayout->addStretch();
    vboxLayout->addWidget(bt_quitter);

    grid->addWidget(bt_memoire, 0, 0);
    grid->addWidget(bt_attention, 1, 0);
    grid->addWidget(bt_sensoriel, 2, 0);
    grid->addWidget(bt_questionnaire, 3, 0);

    connect(bt_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainMenu::listen_bt()
{
    connect(bt_memoire, SIGNAL(clicked()), this, SLOT(onClickMemoire()));
    connect(bt_attention, SIGNAL(clicked()), this, SLOT(onClickAttention()));
    connect(bt_questionnaire, SIGNAL(clicked()), this, SLOT(onClickQuestionnaire()));
    connect(bt_sensoriel, SIGNAL(clicked()), this, SLOT(onClickSensoriel()));
}
