#ifndef ATTENTION_H
#define ATTENTION_H

#include <QtWidgets>
#include "attentionservice.h"
#include "fenetre.h"

class MainWidget;

class Attention : public QWidget
{
    Q_OBJECT
public:
    explicit Attention(AttentionService *attentionService, Fenetre*, QWidget *parent = nullptr);
    void init();

    MainWidget *getMainWidget() const;
    void setMainWidget(MainWidget *newMainWidget);

    void passageCroixBlanc();
    void passageGrille();
    void passageFinition();
    void blocSuivant();
    void enregistrer();
    void timedOut();

    void decompte();

private:
    AttentionService *attentionService;
    QStackedWidget *stackedWidget;
    Fenetre *fenetre;

    void setPagePresentation();
    void setPageCroixBlanc();
    void setPageGrille();
    void setPageFinition();

    QWidget *pagePresentation;
    QWidget *pageCroixBlanc;
    QWidget *pageGrille;
    QWidget *pageFinition;

signals:

};

#endif // ATTENTION_H
