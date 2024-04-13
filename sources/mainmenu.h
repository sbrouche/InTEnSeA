#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "memoireservice.h"
#include "attentionservice.h"

class Fenetre;

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(MemoireService * memoireService, AttentionService * attentionService, Fenetre *fenetre,QWidget *parent = nullptr);

signals:

private slots :
    void onClickMemoire();
    void onClickAttention();
    void onClickSensoriel();
    void onClickQuestionnaire();
private :
    MemoireService * memoireService;
    AttentionService * attentionService;

    void init();
    void listen_bt();

    QPushButton  *bt_memoire;
    QPushButton *bt_attention;
    QPushButton *bt_sensoriel;
    QPushButton  *bt_questionnaire;

    Fenetre *fenetre;

};

#endif // MAINMENU_H
