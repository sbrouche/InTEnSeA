#ifndef FORMULAIREUTILISATEUR_H
#define FORMULAIREUTILISATEUR_H

#include <QtWidgets>
#include "utilisateur.h"
#include "utilitaire.h"
#include "memoireservice.h"
#include "attentionservice.h"

class Fenetre;


class FormulaireUtilisateur : public QWidget
{
    Q_OBJECT
public:
    explicit FormulaireUtilisateur(MemoireService *memoireService,AttentionService *attentionService ,Fenetre *,QString destination = "" ,QWidget *parent = nullptr);
    ~FormulaireUtilisateur();




    QStackedWidget *getStackedWidget() const;

signals:

private slots:
    void onClickHopital();
    void onClickEcole();
    void onClickFille();
    void onClickGarcon();
    void onValiderId();
    void onValiderDtn();

private:
    QString destination;
    MemoireService *memoireService;
    AttentionService *attentionService;
    Fenetre *fenetre;

    void init();
    void setPageLieu();
    void setPageGenre();
    void setPageId();
    void setPageDtn();

    QStackedWidget *stackedWidget;

    QWidget *page_lieu;
    QWidget *page_genre;
    QWidget *page_id;
    QWidget *page_dtn;

    Utilisateur *utilisateur;

//    extra
    QLineEdit *input_id;
    QComboBox *input_annee;
    QComboBox *input_mois;
    QComboBox *input_jour;
};

#endif // FORMULAIREUTILISATEUR_H
