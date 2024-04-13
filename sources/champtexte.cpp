#include "champtexte.h"


ChampTexte::ChampTexte(QString *cible, QWidget *parent) : QLineEdit(parent)
{
    this->cible = cible;
}

QString *ChampTexte::getCible() const
{
    return cible;
}

void ChampTexte::setCible(QString *newCible)
{
    cible = newCible;
}
