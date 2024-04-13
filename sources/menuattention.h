#ifndef MENUATTENTION_H
#define MENUATTENTION_H

#include <QtWidgets>
#include "attentionservice.h"

class Fenetre;

class MenuAttention : public QWidget
{
    Q_OBJECT
public:
    explicit MenuAttention(AttentionService *attentionService, Fenetre *fenetre, QWidget *parent = nullptr);

    void redirection();
    void diaporama();


signals:

private slots:
    void onClickPractice();
    void onClickTest1();
    void onClickTest2();
    void onClickTest3();
    void onClickTest4();

private :
    void init();
    void bt_listen();
    void setPageMenu();
    void setPageChargement();

    void pageChargement();

    QStackedWidget *stackedWidget;

    QWidget *page_menu;
    QWidget *page_chargement;

    QPushButton *bt_Practice;
    QPushButton *bt_test1;
    QPushButton *bt_test2;
    QPushButton *bt_test3;
    QPushButton *bt_test4;

    Fenetre *fenetre;

    AttentionService *attentionService;

};


#endif // MENUATTENTION_H
