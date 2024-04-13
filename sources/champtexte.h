#ifndef CHAMPTEXTE_H
#define CHAMPTEXTE_H

#include <QtWidgets>

class ChampTexte : public QLineEdit
{
public:
    ChampTexte(QString *cible ,QWidget *parent = nullptr);

    QString *getCible() const;
    void setCible(QString *newCible);

private:
    QString *cible;
};

#endif // CHAMPTEXTE_H
