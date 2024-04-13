#ifndef SOUSMENUSENSORIEL_H
#define SOUSMENUSENSORIEL_H

#include <QtWidgets>

class Fenetre;

struct sensoriel_bouton {
    QPushButton *bt;
    QString text;
    QString media;

};
typedef struct sensoriel_bouton sensoriel_bouton;

class SousMenuSensoriel : public QWidget
{
    Q_OBJECT
public:
    explicit SousMenuSensoriel(QVector<sensoriel_bouton> *bts , Fenetre *,QWidget *parent = nullptr);




signals:

private slots:
    void versSensoriel();

private :
    void init();
    int indiceDeBouton (QPushButton *bouton);

    Fenetre * fenetre;

    QVector<sensoriel_bouton> *bts;
};

#endif // SOUSMENUSENSORIEL_H
