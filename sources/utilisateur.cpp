#include "utilisateur.h"

Utilisateur::Utilisateur()
{

}

int Utilisateur::getLieu() const
{
    return lieu;
}

void Utilisateur::setLieu(int newLieu)
{
    lieu = newLieu;
}

char Utilisateur::getGenre() const
{
    return genre;
}

void Utilisateur::setGenre(char newGenre)
{
    genre = newGenre;
}

const QString &Utilisateur::getId() const
{
    return id;
}

void Utilisateur::setId(const QString newId)
{
    id = newId;
}

const QString &Utilisateur::getDate_naissance() const
{
    return date_naissance;
}

void Utilisateur::setDate_naissance(const QString newDate_naissance)
{
    date_naissance = newDate_naissance;
}
