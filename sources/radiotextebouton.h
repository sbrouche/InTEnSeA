#ifndef RADIOTEXTEBOUTON_H
#define RADIOTEXTEBOUTON_H

#include <QtWidgets>

class RadioTexteBouton : public QRadioButton
{
public:
    RadioTexteBouton(QString txt, QString *cible, QWidget *parent = nullptr);

    QString *getCible() const;
    void setCible(QString *newCible);

private :
    QString *cible;
};

#endif // RADIOTEXTEBOUTON_H
