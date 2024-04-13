#include "menusensoriel.h"
#include "sousmenusensoriel.h"
#include "fenetre.h"

MenuSensoriel::MenuSensoriel(Fenetre *f,QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;

    QPixmap img("assets/images/oreille1.png");
    QLabel *oreille1 = new QLabel(this);
    int largeur_oreille1 = 150 , hauteur_oreille1 = 150;
    img = img.scaled(largeur_oreille1, hauteur_oreille1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    oreille1->setPixmap(img);
    oreille1->resize(largeur_oreille1, hauteur_oreille1);
    oreille1->move(300, 300);


    QPixmap img2("assets/images/oreille2.png");
    QLabel *oreille2 = new QLabel(this);
    int largeur_oreille2 = 150 , hauteur_oreille2 = 150;
    img2 = img2.scaled(largeur_oreille2, hauteur_oreille2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    oreille2->setPixmap(img2);
    oreille2->resize(largeur_oreille2, hauteur_oreille2);
    oreille2->move(fenetre->width() - largeur_oreille2 - 300, 400);



    init();
    bt_listen();

    this->setStyleSheet("background-color: rgba(0,0,0,0);");
}


void MenuSensoriel::onClickBtVision()
{
    QVector<sensoriel_bouton> *bts = new QVector<sensoriel_bouton>;

    sensoriel_bouton bt1; bt1.bt = new QPushButton("Vision 1"); bt1.media=("visuel1.mp4");
    bt1.bt->setStyleSheet("background-color : rgb(155,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt1.bt->setFont(QFont("Times", 27));
    bts->push_back(bt1);


    sensoriel_bouton bt2; bt2.bt = new QPushButton("Vision 2"); bt2.media=("visuel2.mp4");
    bt2.bt->setStyleSheet("background-color : rgb(155,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt2.bt->setFont(QFont("Times", 27));
    bts->push_back(bt2);


    sensoriel_bouton bt3; bt3.bt = new QPushButton("Vision 3"); bt3.media=("visuel3.mp4");
    bt3.bt->setStyleSheet("background-color : rgb(155,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt3.bt->setFont(QFont("Times", 27));
    bts->push_back(bt3);

    fenetre->versSousMenuSensorielPage(bts);
}

void MenuSensoriel::onClickBtAudition()
{
    QVector<sensoriel_bouton> *bts = new QVector<sensoriel_bouton>;

    sensoriel_bouton bt1; bt1.bt = new QPushButton("Audition 1"); bt1.media=("audio1.mp4");
    bt1.bt->setStyleSheet("background-color : rgb(125,155,183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt1.bt->setFont(QFont("Times", 27));
    bts->push_back(bt1);


    sensoriel_bouton bt2; bt2.bt = new QPushButton("Audition 2"); bt2.media=("audio2.mp4");
    bt2.bt->setStyleSheet("background-color : rgb(125,155,183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt2.bt->setFont(QFont("Times", 27));
    bts->push_back(bt2);


    sensoriel_bouton bt3; bt3.bt = new QPushButton("Audition 3"); bt3.media=("audio3.mp4");
    bt3.bt->setStyleSheet("background-color : rgb(125,155,183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt3.bt->setFont(QFont("Times", 27));
    bts->push_back(bt3);

    fenetre->versSousMenuSensorielPage(bts);
}

void MenuSensoriel::onClickBtAudioVisuel()
{
    QVector<sensoriel_bouton> *bts = new QVector<sensoriel_bouton>;

    sensoriel_bouton bt1; bt1.bt = new QPushButton("Audiovisuel 1"); bt1.media=("audio-visuel1.mp4");
    bt1.bt->setStyleSheet("background-color : rgb(81,113,180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt1.bt->setFont(QFont("Times", 27));
    bts->push_back(bt1);


    sensoriel_bouton bt2; bt2.bt = new QPushButton("Audiovisuel 2"); bt2.media=("audio-visuel2.mp4");
    bt2.bt->setStyleSheet("background-color : rgb(81,113,180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt2.bt->setFont(QFont("Times", 27));
    bts->push_back(bt2);


    sensoriel_bouton bt3; bt3.bt = new QPushButton("Audiovisuel 3"); bt3.media=("audio-visuel3.mp4");
    bt3.bt->setStyleSheet("background-color : rgb(81,113,180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt3.bt->setFont(QFont("Times", 27));
    bts->push_back(bt3);

    fenetre->versSousMenuSensorielPage(bts);
}

void MenuSensoriel::init()
{
    bt_vision = new QPushButton("Vision");
    bt_vision->setStyleSheet("background-color : rgb(155,195,230); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_vision->setMaximumWidth(300);
    bt_vision->setFont(QFont("Times", 27));


    bt_audition = new QPushButton("Audition");
    bt_audition->setStyleSheet("background-color : rgb(125,155,183); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_audition->setMaximumWidth(300);
    bt_audition->setFont(QFont("Times", 27));


    bt_audio_visuel = new QPushButton("Audio-Visuel");
    bt_audio_visuel->setStyleSheet("background-color : rgb(81,113,180); color: white; width: 300px; height: 85px; border-radius: 13px; margin: 10px;");
    bt_audio_visuel->setMaximumWidth(300);
    bt_audio_visuel->setFont(QFont("Times", 27));

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addStretch(0);
    vlayout->addWidget(bt_vision, 0, Qt::AlignCenter);
    vlayout->addWidget(bt_audition, 0, Qt::AlignCenter);
    vlayout->addWidget(bt_audio_visuel, 0, Qt::AlignCenter);
    vlayout->addStretch(0);
}

void MenuSensoriel::bt_listen()
{
    connect(bt_vision, SIGNAL(clicked()), this, SLOT(onClickBtVision()));
    connect(bt_audition, SIGNAL(clicked()), this, SLOT(onClickBtAudition()));
    connect(bt_audio_visuel, SIGNAL(clicked()), this, SLOT(onClickBtAudioVisuel()));
}
