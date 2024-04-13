#ifndef ATTENTIONSERVICE_H
#define ATTENTIONSERVICE_H

#include "tuileattention.h"
#include "utilisateur.h"

#include <QString>
#include <QStringList>
#include <QMap>

class AttentionService
{
public:
    AttentionService();

    void init(QString type = "practice");
    void initBloc(int niveau);
    void chargerFichiers();
    void construireNiveaux();
    void chargerCSV();
    QVector<QMap<QString, QString>*>* parseCSV(QString path);
    QVector<TuileAttention *> trierGrilleAleatoirement(QVector<TuileAttention *> liste);


    Utilisateur *getUtilisateur() const;
    void setUtilisateur(Utilisateur newUtilisateur);

    int getNiveau() const;
    void setNiveau(int newNiveau);

    int choisirTuile(TuileAttention *tuile);

    QVector<TuileAttention *> *getImagesRetenir() const;

    QVector<TuileAttention *> *getImagesGrille() const;

    QVector<QVector<TuileAttention *> *> *getImagesGrilleAff() const;

    QVector<int> *getListeNiveau() const;
    void setListeNiveau(QVector<int> *newListeNiveau);

    QElapsedTimer *getChrono() const;

    QVector<int> *getListeTemps() const;

    const QString &getTypeJeu() const;
    void setTypeJeu(const QString &newTypeJeu);

    QVector<QMap<QString, QString> *> *getListeItem() const;

private :
    QStringList *filenames;
    QMap<QString, QVector<int>*> *niveauxJeux;
    QMap<QString, QVector<QMap<QString, QString>*>*> *niveauxJeuImages;

    Utilisateur *utilisateur;
    QString typeJeu;
    QVector<int> *listeNiveau;
    QVector<int> *listeNbErreur;
    QVector<int> *listeTemps;
    QElapsedTimer *chrono;
    QVector<QMap<QString, QString>*> *listeItem;

    int niveau;
    int nbErreur;
    QString imageRetenir;
    QVector<TuileAttention*> *imagesGrille;
    QVector<TuileAttention*> *imagesRetenir;
    QVector<TuileAttention*> *imagesDistraction;
    QVector<TuileAttention*> *imagesChoisis;
    QVector<QVector<TuileAttention*>*> *imagesGrilleAff;
};

#endif // ATTENTIONSERVICE_H
