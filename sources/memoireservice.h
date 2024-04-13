#ifndef MEMOIRESERVICE_H
#define MEMOIRESERVICE_H

#include "tuilememoire.h"
#include "utilisateur.h"
#include <cstdlib>
#include <QtWidgets>


class MemoireService
{
public:
    MemoireService();
    ~MemoireService();

    void init(QString type_jeu = "practice");
    void initBloc(int niveau=0);
    void reinitBloc(int niveau);
    int choisirImage(TuileMemoire *tuileMemoire);

    Utilisateur *getUtilisateur() const;
    void setUtilisateur(Utilisateur newUtilisateur);


    QVector<TuileMemoire *> *getImagesGrille() const;

    QVector<TuileMemoire *> *getImagesRetenir() const;

    QVector<TuileMemoire *> *getImagesDistraction() const;

    QVector<QVector<TuileMemoire *> *> *getImagesGrilleAff() const;

    int getNiveau() const;
    void setNiveau(int newNiveau);

    int **getListeNiveau() const;
    void setListeNiveau(int **newListeNiveau);

    QVector<QMap<QString, QStringList *> *> *getListeItem() const;

    QVector<int> *getListeNbErreur() const;

    const QString &getTypeJeu() const;
    void setTypeJeu(const QString &newTypeJeu);

private:
    void chargerFichier();
    void construireNiveaux();
    void construireNiveauxImage();
    void chargerCSV();



    Utilisateur *utilisateur;
    QString typeJeu;
    QStringList *filenames;
    int** listeNiveau;
    QVector<int> *listeNbErreur;
    QVector<QMap<QString ,QStringList*>*> *listeItem;
    int niveau;

    int nbErreur;
    QVector<TuileMemoire*> *imagesGrille;
    QVector<TuileMemoire*> *imagesRetenir;
    QVector<TuileMemoire*> *imagesDistraction;
    QVector<TuileMemoire*> *imagesChoisies;
    QVector<QVector<TuileMemoire*>*> *imagesGrilleAff;

//    RESERVE
    QStringList *practice_files;
    QStringList *test1_files;
    QStringList *test2_files;
    QStringList *test3_files;
    QStringList *test4_files;

    QMap<QString, int**> *niveauxJeu;
    QMap<QString ,QVector<QMap<QString ,QStringList*>*>*> *niveauxJeuImage;

//   Methode utile
    QVector<TuileMemoire *> trierGrilleAleatoirement(QVector<TuileMemoire *>);
};

#endif // MEMOIRESERVICE_H
