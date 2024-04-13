#include "utilitaire.h"

Utilitaire::Utilitaire()
{

}

int Utilitaire::getJourMois(int mois)
{
    switch(mois) {
        case 1:
            return 31;
        case 2:
            return 29;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }
    return 30;
}

QStringList Utilitaire::getListeMois()
{
    QStringList retour;
    retour.push_back("Janvier");
    retour.push_back("Février");
    retour.push_back("Mars");
    retour.push_back("Avril");
    retour.push_back("Mai");
    retour.push_back("Juin");
    retour.push_back("Juillet");
    retour.push_back("Août");
    retour.push_back("Septembre");
    retour.push_back("Octobre");
    retour.push_back("Novembre");
    retour.push_back("Décembre");

    return  retour;
}
