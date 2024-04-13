#ifndef FENETRE_H
#define FENETRE_H

#include <QtWidgets>
#include "attentionservice.h"
#include "diaporama.h"
#include "memoireservice.h"
#include "sousmenusensoriel.h"


class Fenetre : public QMainWindow
{
    Q_OBJECT
public:
    explicit Fenetre(MemoireService *, AttentionService*, QWidget *parent = nullptr);

public slots:
    void setPageDiaporama(QString);
    void versPageMainMenu();
    void versAttentionPage();
    void versMemoirePage();
    void versMenuMemoirePage();
    void versMenuAttentionPage();
    void versFormulaireUtilisateur(QString);
    void versSousMenuSensorielPage(QVector<sensoriel_bouton> *bts);
    void versMenuSensorielPage();
    void versAudioVisuelPage(QString media);
    void versInstruction(QString destination);
    void versQuestionnairePage();

signals:

private :
    MemoireService *memoireService;
    AttentionService *attentionService;
};

#endif // FENETRE_H
