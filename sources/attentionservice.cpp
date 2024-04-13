#include "attentionservice.h"

AttentionService::AttentionService()
{
    construireNiveaux();
    chargerFichiers();
    chargerCSV();
}

void AttentionService::init(QString type_jeu)
{
    this->typeJeu = type_jeu;
    this->listeNiveau = niveauxJeux[0][typeJeu];
    listeNbErreur = new QVector<int>;
    this->chrono = new QElapsedTimer;
    listeTemps = new QVector<int>;
    this->listeItem = niveauxJeuImages[0][typeJeu];
    initBloc(0);
}

void AttentionService::initBloc(int niveau)
{

    this->nbErreur=0;
    this->niveau=niveau;

    QMap<QString, QString> item = listeItem[0][niveau][0];
    int nbImageRetenir = item["nombre"].toInt();
    QString imageCible = item["cible"];
    this->imagesRetenir = new QVector<TuileAttention*>;
    this->imagesChoisis = new QVector<TuileAttention*>;
    this->imagesDistraction = new QVector<TuileAttention*>;
    this->imagesGrille = new QVector<TuileAttention*>;

    QStringList filenames_copie(*filenames);
    for(int i=0; i<filenames_copie.length(); i++) {
        if (filenames_copie[i] == imageCible) {
            filenames_copie.takeAt(i);
            break;
        }
    }

    // générer les tuiles d'images à retenir
    int i = 0;
    imageRetenir = imageCible;
    imageRetenir = "assets/images/stimuli_attention/" + imageRetenir;
    for (i=0; i<nbImageRetenir; i++) {
        TuileAttention *tuile = new TuileAttention(i+1, imageRetenir, this);
        this->imagesRetenir->push_back(tuile);
        this->imagesGrille->push_back(tuile);
    }

    // générer les tuiles d'images distraction
    for( ; i<168; i++) {
        int indice = QRandomGenerator::global()->generate()%filenames_copie.length();
        QString imageDistraction = filenames_copie[indice];
        TuileAttention *tuile = new TuileAttention(i+1, "assets/images/stimuli_attention/" + imageDistraction, this);
        this->imagesDistraction->push_back(tuile);
        this->imagesGrille->push_back(tuile);
    }

    // trier le tabelau imagesGrille aléatoirement
    *imagesGrille = trierGrilleAleatoirement(*imagesGrille);

    // images grille Aff
    this->imagesGrilleAff = new QVector<QVector<TuileAttention*>*>;
    for (i=0; i<this->imagesGrille->length(); ) {
        QVector<TuileAttention*> *tab = new QVector<TuileAttention*>;
        for(int e = 0; e<14 && i<this->imagesGrille->length(); e++) {
            tab->push_back(imagesGrille[0][i]);
            i++;
        }
        this->imagesGrilleAff->push_back(tab);
    }

}

void AttentionService::chargerFichiers()
{
    filenames = new QStringList;
    QDir directory("assets/images/stimuli_attention");
    *filenames = directory.entryList(QStringList() << "*.png", QDir::Files);
}

void AttentionService::construireNiveaux()
{
    niveauxJeux = new QMap<QString, QVector<int>*>;
    // Je clonerai ce niveau pour tous les types, mais ça peut varier selon les changements
    QVector<int> niveau;
    niveau.push_back(3);
    niveau.push_back(4);
    niveau.push_back(5);
    niveau.push_back(6);

    niveauxJeux->insert("practice",new QVector<int>(niveau));
    niveauxJeux->insert("test1",new QVector<int>(niveau));
    niveauxJeux->insert("test2",new QVector<int>(niveau));
    niveauxJeux->insert("test3",new QVector<int>(niveau));
    niveauxJeux->insert("test4",new QVector<int>(niveau));
}

QVector<TuileAttention *> AttentionService::trierGrilleAleatoirement(QVector<TuileAttention *> liste)
{
    int  taille = liste.size();
    for(int i=0; i<taille; i++) {
        int indice = QRandomGenerator::global()->generate()%taille;
        TuileAttention *temp = liste[i];
        liste[i] =  liste[indice];
        liste[indice] =  temp;
    }
    return liste;
}

QVector<QMap<QString, QString>*>* AttentionService::parseCSV(QString path) {
    QVector<QMap<QString, QString>*> *retour = new QVector<QMap<QString, QString>*>;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ouverture du fichier impossible : " << path;
    }

//    Regrouper toutes les lignes dans un tableau
    QStringList lines;
    QTextStream in(&file);
    in.readLine(); // sauter la première ligne
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.push_back(line);
    }

// Décomposer chaque ligne
    for(int i=0; i<lines.length(); i++) {
        QString line = lines[i];
        QStringList splitLine = line.split(";");

        QString image = splitLine[1];
        QString nombre = splitLine[2];


        QMap<QString, QString> *item = new QMap<QString, QString>;
        item->insert("cible", image);
        item->insert("nombre", nombre);
        retour->push_back(item);
    }

    return retour;
}

void AttentionService::chargerCSV()
{
    niveauxJeuImages = new QMap<QString, QVector<QMap<QString, QString>*>*>;
    // test 1
    QVector<QMap<QString, QString>*> *test1 = parseCSV("assets/csv/Items_attention_test1.csv");
    niveauxJeuImages->insert("test1", test1);

    // test 2
    QVector<QMap<QString, QString>*> *test2 = parseCSV("assets/csv/Items_attention_test2.csv");
    niveauxJeuImages->insert("test2", test2);

    // test 3
    QVector<QMap<QString, QString>*> *test3 = parseCSV("assets/csv/Items_attention_test3.csv");
    niveauxJeuImages->insert("test3", test3);

    // test 4
    QVector<QMap<QString, QString>*> *test4 = parseCSV("assets/csv/Items_attention_test4.csv");
    niveauxJeuImages->insert("test4", test4);

    // PRACTICE
    QVector<QMap<QString, QString>*> *practice = parseCSV("assets/csv/Items_attention_practice.csv");
    niveauxJeuImages->insert("practice", practice);


}

Utilisateur *AttentionService::getUtilisateur() const
{
    return utilisateur;
}

void AttentionService::setUtilisateur(Utilisateur newUtilisateur)
{
    utilisateur = new Utilisateur(newUtilisateur);
}

int AttentionService::getNiveau() const
{
    return niveau;
}

void AttentionService::setNiveau(int newNiveau)
{
    niveau = newNiveau;
}

int AttentionService::choisirTuile(TuileAttention *tuile)
{
    if(imagesRetenir->empty()) {
        listeTemps->push_back(this->chrono->elapsed());
        return 4;
    }
    int reponse = 1;
//    Les réponses possibles : 1 = vrai, 2 = faux, 3 = vrai et fin de jeu, 4= faux et fin de jeu
    if (tuile -> getFilepath() != imageRetenir) {
        reponse = 2;
        nbErreur ++;
        if(imagesRetenir->empty()) {
            reponse = 4;
            listeNbErreur->push_back(nbErreur);
            listeTemps->push_back(this->chrono->elapsed());
        }
    } else {
        reponse = 1;
        imagesRetenir->removeOne(tuile);
        if(imagesRetenir->empty()) {
            reponse = 3;
            listeNbErreur->push_back(nbErreur);
            listeTemps->push_back(this->chrono->elapsed());
        }
    }
    return reponse;
}

QVector<TuileAttention *> *AttentionService::getImagesRetenir() const
{
    return imagesRetenir;
}

QVector<TuileAttention *> *AttentionService::getImagesGrille() const
{
    return imagesGrille;
}

QVector<QVector<TuileAttention *> *> *AttentionService::getImagesGrilleAff() const
{
    return imagesGrilleAff;
}

QVector<int> *AttentionService::getListeNiveau() const
{
    return listeNiveau;
}

void AttentionService::setListeNiveau(QVector<int> *newListeNiveau)
{
    listeNiveau = newListeNiveau;
}

QElapsedTimer *AttentionService::getChrono() const
{
    return chrono;
}

QVector<int> *AttentionService::getListeTemps() const
{
    return listeTemps;
}

const QString &AttentionService::getTypeJeu() const
{
    return typeJeu;
}

void AttentionService::setTypeJeu(const QString &newTypeJeu)
{
    typeJeu = newTypeJeu;
}

QVector<QMap<QString, QString> *> *AttentionService::getListeItem() const
{
    return listeItem;
}
