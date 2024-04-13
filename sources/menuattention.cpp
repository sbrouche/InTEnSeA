#include "menuattention.h"
#include "fenetre.h"


MenuAttention::MenuAttention( AttentionService *attentionService, Fenetre *f, QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;

    QLabel *titre = new QLabel("A  t  t  e  n  t  i  o  n", this);
    titre->setStyleSheet("color : white; background-color: rgba(0,0,0,0);");
    titre->setFont(QFont("Segoe UI", 40));
    titre->move(10, 20);
    titre->resize(1000,50);
    qDebug() << this->width();

    QPixmap img("assets/images/loupe.png");
    QLabel *tete = new QLabel(this);
    int largeur_tete = 600 , hauteur_tete = 200;
    img = img.scaled(largeur_tete, hauteur_tete, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    tete->setPixmap(img);
    tete->resize(largeur_tete, hauteur_tete);
    tete->move(fenetre->width() - largeur_tete, 300);

    this->attentionService = attentionService;
    init();
    bt_listen();

    this->setStyleSheet("background-color: rgba(0,0,0,0);");
}

void MenuAttention::redirection()
{
    this->fenetre->versAttentionPage();
    this->stackedWidget->setCurrentIndex(0);
}

void MenuAttention::diaporama()
{
    fenetre->setPageDiaporama("attention");
}

void MenuAttention::onClickPractice()
{
    qDebug() << "Practice";
    pageChargement();
    attentionService->init("practice");
    QTimer::singleShot(3300, this, &MenuAttention::diaporama);
}

void MenuAttention::onClickTest1()
{
    qDebug() << "Test 1";
    pageChargement();
    attentionService->init("test1");
    QTimer::singleShot(3300, this, &MenuAttention::redirection);
}

void MenuAttention::onClickTest2()
{
    qDebug() << "Test 2";
    pageChargement();
    attentionService->init("test2");
    QTimer::singleShot(3300, this, &MenuAttention::redirection);
}

void MenuAttention::onClickTest3()
{
    qDebug() << "Test 3";
    pageChargement();
    attentionService->init("test3");
    QTimer::singleShot(3300, this, &MenuAttention::redirection);
}

void MenuAttention::onClickTest4()
{
    qDebug() << "Test 4";
    pageChargement();
    attentionService->init("test4");
    QTimer::singleShot(3300, this, &MenuAttention::redirection);
}

void MenuAttention::init()
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget;
    vlayout->addWidget(stackedWidget);

    page_menu = new QWidget;
    setPageMenu();
    page_chargement = new QWidget;
    setPageChargement();

    stackedWidget->addWidget(page_menu);
    stackedWidget->addWidget(page_chargement);

    stackedWidget->setCurrentIndex(0);

}

void MenuAttention::bt_listen()
{
    this->connect(bt_Practice, SIGNAL(clicked()), this, SLOT(onClickPractice()));
    this->connect(bt_test1, SIGNAL(clicked()), this, SLOT(onClickTest1()));
    this->connect(bt_test2, SIGNAL(clicked()), this, SLOT(onClickTest2()));
    this->connect(bt_test3, SIGNAL(clicked()), this, SLOT(onClickTest3()));
    this->connect(bt_test4, SIGNAL(clicked()), this, SLOT(onClickTest4()));
}

void MenuAttention::setPageMenu()
{
    QGridLayout *grid= new QGridLayout;

    bt_Practice = new QPushButton("Practice");
    bt_Practice->setStyleSheet("background-color : rgb(155,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_Practice->setMaximumWidth(300);
    bt_Practice->setFont(QFont("Times", 27));

    bt_test1 = new QPushButton("Test 1");
    bt_test1->setStyleSheet("background-color : rgb(125,155,183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_test1->setMaximumWidth(300);
    bt_test1->setFont(QFont("Times", 27));

    bt_test2 = new QPushButton("Test 2");
    bt_test2->setStyleSheet("background-color : rgb(81,113,180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_test2->setMaximumWidth(300);
    bt_test2->setFont(QFont("Times", 27));

    bt_test3 = new QPushButton("Test 3");
    bt_test3->setStyleSheet("background-color : rgb(32,56,100); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_test3->setMaximumWidth(300);
    bt_test3->setFont(QFont("Times", 27));

    bt_test4 = new QPushButton("Test 4");
    bt_test4->setStyleSheet("background-color : rgb(70,65,150); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_test4->setMaximumWidth(300);
    bt_test4->setFont(QFont("Times", 27));

    QVBoxLayout *vboxLayout = new QVBoxLayout(page_menu);
    vboxLayout->addSpacing(1);
    vboxLayout->addLayout(grid);
//    vboxLayout->addWidget(bt_memoire);
//    vboxLayout->addLayout(hlayout_memoire);
//    vboxLayout->addWidget(bt_attention);
//    vboxLayout->addWidget(bt_sensoriel);
//    vboxLayout->addWidget(bt_questionnaire);


    grid->addWidget(bt_Practice, 0, 0);
    grid->addWidget(bt_test1, 1, 0);
    grid->addWidget(bt_test2, 2, 0);
    grid->addWidget(bt_test3, 3, 0);
    grid->addWidget(bt_test4, 4, 0);

    vboxLayout->addSpacing(1);
}

void MenuAttention::setPageChargement()
{
    QString imagePath = "assets/icon/intensea.png";
    QPixmap img(imagePath);
    QLabel *logo = new QLabel;
    logo->setAlignment(Qt::AlignCenter);
    logo->setPixmap(img);

    QLabel *titre = new QLabel("InTEnSeA");
    titre->setStyleSheet("font-size: 40px; color: white;");
    titre->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vlayout = new QVBoxLayout(page_chargement);
    vlayout->addStretch();
    vlayout->addWidget(logo);
    vlayout->addWidget(titre);
    vlayout->addStretch();
}

void MenuAttention::pageChargement()
{
    stackedWidget->setCurrentIndex(1);
}


//const MainWidget &MenuMemoire::getFenPrincipale() const
//{
//    return fenPrincipale;
//}

//void MenuMemoire::setFenPrincipale(const MainWidget &newFenPrincipale)
//{
//    fenPrincipale = newFenPrincipale;
//}
