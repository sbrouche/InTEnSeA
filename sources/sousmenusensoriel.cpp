#include "sousmenusensoriel.h"
#include "fenetre.h"

SousMenuSensoriel::SousMenuSensoriel(QVector<sensoriel_bouton> *bts,Fenetre *f ,QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;
    this->bts = bts;

    init();
}

void SousMenuSensoriel::init()
{
    if (bts != nullptr) {
        QVBoxLayout *vlayout = new QVBoxLayout(this);
        vlayout->addStretch();

        for (sensoriel_bouton bt : bts[0]) {
            vlayout->addWidget(bt.bt, 0, Qt::AlignCenter);

            connect(bt.bt, SIGNAL(clicked()), this, SLOT(versSensoriel()));
        }

        vlayout->addStretch();
    }
}

int SousMenuSensoriel::indiceDeBouton(QPushButton *bouton)
{
        for (int i=0; i<bts->length(); i++) {
            if(bouton == bts[0][i].bt) {
                return i;
            }
        }
        return -1;
}



void SousMenuSensoriel::versSensoriel()
{
    QPushButton *button = (QPushButton*) QObject::sender();
    int i= indiceDeBouton(button);
    if (i>=0) {
        QString media = bts[0][i].media;
        fenetre->versAudioVisuelPage(media);
    }
}
