#include "radiobouton.h"


//RadioBouton::RadioBouton(QWidget *parent) : QRadioButton(parent)
//{

//}

//RadioBouton::RadioBouton(QString text, QWidget *parent) : QRadioButton(text, parent)
//{

//}

RadioBouton::RadioBouton(QString text, char *cible, QWidget *parent) : QRadioButton(text, parent)
{
    this->cible = cible;
}

char *RadioBouton::getCible() const
{
    return cible;
}

void RadioBouton::setCible(char *newCible)
{
    cible = newCible;
}
