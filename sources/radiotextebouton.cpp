#include "radiotextebouton.h"

RadioTexteBouton::RadioTexteBouton(QString texte ,QString *cible, QWidget *parent) : QRadioButton(texte, parent)
{
    this->cible = cible;
}

QString *RadioTexteBouton::getCible() const
{
    return cible;
}

void RadioTexteBouton::setCible(QString *newCible)
{
    cible = newCible;
}
