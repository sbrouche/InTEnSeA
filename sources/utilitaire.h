#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <QString>
#include <QStringList>
#include <QVector>

class Utilitaire
{
public:
    Utilitaire();
    static int getJourMois(int mois);
    static QStringList getListeMois();
};

#endif // UTILITAIRE_H
