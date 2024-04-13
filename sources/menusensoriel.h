#ifndef MENUSENSORIEL_H
#define MENUSENSORIEL_H

#include <QtWidgets>


class Fenetre;

class MenuSensoriel : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSensoriel(Fenetre *fenetre, QWidget *parent = nullptr);


signals:

private slots :
    void onClickBtVision();
    void onClickBtAudition();
    void onClickBtAudioVisuel();

private :
    void init();
    void bt_listen();

    Fenetre *fenetre;

    QPushButton *bt_vision;
    QPushButton *bt_audition;
    QPushButton *bt_audio_visuel;

};

#endif // MENUSENSORIEL_H
