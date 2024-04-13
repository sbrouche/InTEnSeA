#ifndef MEMOIRE_H
#define MEMOIRE_H

#include "fenetre.h"
#include "memoireservice.h"

#include <QtWidgets>

class  MainWidget;

class Memoire : public QWidget
{
    Q_OBJECT
public:
    explicit Memoire( MemoireService *memoireService, Fenetre * ,QWidget *parent = nullptr);
    void init();
    void setPages();


//    void resizeEvent(QResizeEvent *event);

    QLabel *getPoint() const;

    void passageGrille();
    void passageCroixBlanc();
    void passageFinition();
    void enregistrer();

signals:

private slots:
    void movePoint();

private:
    void setPagePresentation();
    void setPageGrille();
    void setPageCroixBlanc();
    void setPageFinition();

    MemoireService *memoireService;

    QStackedWidget *stackedWidget;
    QLabel  *point;

    QWidget *pagePresentation;
    QWidget *pageGrille;
    QWidget *pageCroixBlanc;
    QWidget *pageFinition;

    Fenetre * fenetre;

    void decompte();


};

#endif // MEMOIRE_H
