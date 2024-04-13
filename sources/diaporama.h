#ifndef DIAPORAMA_H
#define DIAPORAMA_H

#include "attentionservice.h"
#include "memoireservice.h"

#include <QtWidgets>


class Fenetre;

class Diaporama : public QWidget
{
    Q_OBJECT
public:
    explicit Diaporama(QString mode, MemoireService *memoireService, AttentionService *attentionService, Fenetre *fenetre, QWidget *parent = nullptr);

signals:

private slots :
    void onPageSuivant();
    void onPagePrecedent();

private :


    QStackedWidget *stackWidget;

    Fenetre *fenetre;
    QString mode;

    MemoireService *memoireService;
    AttentionService *attentionService;
};

#endif // DIAPORAMA_H
