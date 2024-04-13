#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QtWidgets>

class Utilisateur
{
public:
    Utilisateur();

    int getLieu() const;
    void setLieu(int newLieu);

    char getGenre() const;
    void setGenre(char newGenre);

    const QString &getId() const;
    void setId(const QString newId);

    const QString &getDate_naissance() const;
    void setDate_naissance(const QString newDate_naissance);


private:
    int lieu;
    char genre;
    QString id;
    QString date_naissance;
};

#endif // UTILISATEUR_H
