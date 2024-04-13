#ifndef RADIOBOUTON_H
#define RADIOBOUTON_H

#include <QtWidgets>

class RadioBouton : public QRadioButton
{
public:
//    RadioBouton(QWidget *parent = nullptr);
//    RadioBouton(QString text, QWidget *parent = nullptr);
    RadioBouton(QString text, char* cible, QWidget *parent = nullptr);

    char *getCible() const;
    void setCible(char *newCible);

private :
    char* cible;
};

#endif // RADIOBOUTON_H
