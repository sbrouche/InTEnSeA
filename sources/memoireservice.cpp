#include "memoireservice.h"

using namespace std;

MemoireService::MemoireService()
{
    chargerCSV();
    chargerFichier();
    construireNiveaux();
}

MemoireService::~MemoireService()
{
//    delete utilisateur;
    delete niveauxJeu;
}

void MemoireService::init(QString type_jeu)
{
    this->typeJeu = type_jeu;
    this->listeItem = niveauxJeuImage[0][typeJeu];
    this->listeNbErreur = new QVector<int>;

    initBloc(0);
}

void MemoireService::initBloc(int niveau)
{
    nbErreur = 0;
    this->niveau = niveau;
    QMap<QString ,QStringList*> item = listeItem[0][niveau][0];
    QStringList cibles = item["cibles"][0];
    QStringList distractors = item["distractors"][0];

    imagesGrille =  new QVector<TuileMemoire*>;
    imagesRetenir = new QVector<TuileMemoire*>;
    imagesDistraction = new QVector<TuileMemoire*>;

    for(QString image : cibles) {
        TuileMemoire *tuileMemoire = new TuileMemoire("assets/images/" + typeJeu + "/" + image, this);
        imagesGrille ->push_back(tuileMemoire);
        imagesRetenir->push_back(tuileMemoire);
    }

    for(QString image : distractors) {
        TuileMemoire *tuileMemoire = new TuileMemoire("assets/images/" + typeJeu + "/" + image, this);
        imagesGrille ->push_back(tuileMemoire);
        imagesDistraction->push_back(tuileMemoire);
    }

    *imagesGrille =  trierGrilleAleatoirement(*imagesGrille);

    imagesGrilleAff = new QVector<QVector<TuileMemoire*>*>;
    int nbSurUneLigne = imagesGrille->length() < 6 ? imagesGrille->length() : 3;

    for(int i=0; i<imagesGrille->length(); ) {
        QVector<TuileMemoire*> *tab = new QVector<TuileMemoire*>;
        for(int e = 0; e < nbSurUneLigne && i<imagesGrille->length(); e++ ) {
            tab->push_back(imagesGrille[0][i]);
            i++;
        }
        imagesGrilleAff->push_back(tab);
    }
    imagesChoisies = new QVector<TuileMemoire*>;

//    DEBUG
    for (TuileMemoire *tuile : imagesGrille[0]) {
        qDebug() << tuile->getFilenamePath();
    }
}

void MemoireService::reinitBloc(int niveau)
{
    delete  imagesGrille;
    delete imagesRetenir;
    delete imagesDistraction;
    delete imagesChoisies;
    delete  imagesGrilleAff;

    initBloc(niveau);
}



Utilisateur *MemoireService::getUtilisateur() const
{
    return utilisateur;
}

void MemoireService::setUtilisateur(Utilisateur newUtilisateur)
{
    utilisateur = new Utilisateur(newUtilisateur);
}

void MemoireService::chargerFichier()
{
    // PRACTICE
    practice_files = new QStringList;
    QDir directory("assets/images/practice");
    *practice_files = directory.entryList(QStringList() << "*.png", QDir::Files);

    // TEST 1
    test1_files = new QStringList;
    directory = QDir("assets/images/test1");
    *test1_files = directory.entryList(QStringList() << "*.png", QDir::Files);

    // TEST 2
    test2_files = new QStringList;
    directory = QDir("assets/images/test2");
    *test2_files = directory.entryList(QStringList() << "*.png", QDir::Files);

//    TEST 3
    test3_files = new QStringList;
    directory = QDir("assets/images/test3");
    *test3_files = directory.entryList(QStringList() << "*.png", QDir::Files);

//    TEST 4
    test4_files = new QStringList;
    directory = QDir("assets/images/test4");
    *test4_files = directory.entryList(QStringList() << "*.png", QDir::Files);
}

void MemoireService::construireNiveaux()
{
    niveauxJeu = new QMap<QString, int**>;
    // PRACTICE
    int** niveau_practice = (int**) malloc(5*sizeof(int*));
    niveau_practice[0] = (int*) malloc(2*sizeof(int));
    niveau_practice[0][0] = 3;
    niveau_practice[0][1] = 3;

    niveau_practice[1] = (int*) malloc(2*sizeof(int));
    niveau_practice[1][0] = 1;
    niveau_practice[1][1] = 2;

    niveau_practice[2] = (int*) malloc(2*sizeof(int));
    niveau_practice[2][0] = 2;
    niveau_practice[2][1] = 2;

    niveau_practice[3] = (int*) malloc(2*sizeof(int));
    niveau_practice[3][0] = 2;
    niveau_practice[3][1] = 3;

    niveau_practice[4] = (int*) malloc(2*sizeof(int));
    niveau_practice[4][0] = 3;
    niveau_practice[4][1] = 3;

    niveauxJeu->insert("practice", niveau_practice);

    // TEST 1
    int** niveau_test1 = (int**) malloc(5*sizeof(int*));
    niveau_test1[0] = (int*) malloc(2*sizeof(int));
    niveau_test1[0][0] = 1;
    niveau_test1[0][1] = 1;

    niveau_test1[1] = (int*) malloc(2*sizeof(int));
    niveau_test1[1][0] = 1;
    niveau_test1[1][1] = 2;

    niveau_test1[2] = (int*) malloc(2*sizeof(int));
    niveau_test1[2][0] = 2;
    niveau_test1[2][1] = 2;

    niveau_test1[3] = (int*) malloc(2*sizeof(int));
    niveau_test1[3][0] = 2;
    niveau_test1[3][1] = 3;

    niveau_test1[4] = (int*) malloc(2*sizeof(int));
    niveau_test1[4][0] = 3;
    niveau_test1[4][1] = 3;

    niveauxJeu->insert("test1", niveau_test1);

    // TEST 2
    int** niveau_test2 = (int**) malloc(5*sizeof(int*));
        niveau_test2[0] = (int*) malloc(2*sizeof(int));
        niveau_test2[0][0] = 1;
        niveau_test2[0][1] = 1;

        niveau_test2[1] = (int*) malloc(2*sizeof(int));
        niveau_test2[1][0] = 1;
        niveau_test2[1][1] = 2;

        niveau_test2[2] = (int*) malloc(2*sizeof(int));
        niveau_test2[2][0] = 2;
        niveau_test2[2][1] = 2;

        niveau_test2[3] = (int*) malloc(2*sizeof(int));
        niveau_test2[3][0] = 2;
        niveau_test2[3][1] = 3;

        niveau_test2[4] = (int*) malloc(2*sizeof(int));
        niveau_test2[4][0] = 3;
        niveau_test2[4][1] = 3;

        niveauxJeu->insert("test2", niveau_test2);

//        TEST 3
    int** niveau_test3 = (int**) malloc(5*sizeof(int*));
        niveau_test3[0] = (int*) malloc(2*sizeof(int));
        niveau_test3[0][0] = 1;
        niveau_test3[0][1] = 1;

        niveau_test3[1] = (int*) malloc(2*sizeof(int));
        niveau_test3[1][0] = 1;
        niveau_test3[1][1] = 2;

        niveau_test3[2] = (int*) malloc(2*sizeof(int));
        niveau_test3[2][0] = 2;
        niveau_test3[2][1] = 2;

        niveau_test3[3] = (int*) malloc(2*sizeof(int));
        niveau_test3[3][0] = 2;
        niveau_test3[3][1] = 3;

        niveau_test3[4] = (int*) malloc(2*sizeof(int));
        niveau_test3[4][0] = 3;
        niveau_test3[4][1] = 3;

        niveauxJeu->insert("test3", niveau_test3);

//        TEST 4
    int** niveau_test4 = (int**) malloc(5*sizeof(int*));
        niveau_test4[0] = (int*) malloc(2*sizeof(int));
        niveau_test4[0][0] = 1;
        niveau_test4[0][1] = 1;

        niveau_test4[1] = (int*) malloc(2*sizeof(int));
        niveau_test4[1][0] = 1;
        niveau_test4[1][1] = 2;

        niveau_test4[2] = (int*) malloc(2*sizeof(int));
        niveau_test4[2][0] = 2;
        niveau_test4[2][1] = 2;

        niveau_test4[3] = (int*) malloc(2*sizeof(int));
        niveau_test4[3][0] = 2;
        niveau_test4[3][1] = 3;

        niveau_test4[4] = (int*) malloc(2*sizeof(int));
        niveau_test4[4][0] = 3;
        niveau_test4[4][1] = 3;

        niveauxJeu->insert("test4", niveau_test4);
}

void MemoireService::construireNiveauxImage()
{
    niveauxJeuImage = new QMap<QString ,QVector<QMap<QString ,QStringList*>*>*>;

    // test 1
    QVector<QMap<QString ,QStringList*>*> *niveauTest1 = new QVector<QMap<QString ,QStringList*>*>;
//        item 1
        QMap<QString ,QStringList*> *map_test1_item1 = new QMap<QString ,QStringList*>;

        QStringList *test1_item1_cible = new QStringList;
        test1_item1_cible->push_back("008-popcorn.png");

        QStringList *test1_item1_distraction = new QStringList;
        test1_item1_distraction->push_back("012-triumph.png");

        map_test1_item1->insert("cible", test1_item1_cible);
        map_test1_item1->insert("distraction", test1_item1_distraction);
//        fin item 1

//        item 2
        QMap<QString ,QStringList*> *map_test1_item2 = new QMap<QString ,QStringList*>;

        QStringList *test1_item2_cible = new QStringList;
        test1_item1_cible->push_back("008-popcorn.png");

        QStringList *test1_item2_distraction = new QStringList;
        test1_item1_distraction->push_back("012-triumph.png");

        map_test1_item2->insert("cible", test1_item2_cible);
        map_test1_item2->insert("distraction", test1_item2_distraction);
//        fin item 2

//        item 3
        QMap<QString ,QStringList*> *map_test1_item3 = new QMap<QString ,QStringList*>;

        QStringList *test1_item3_cible = new QStringList;
        test1_item1_cible->push_back("008-popcorn.png");

        QStringList *test1_item3_distraction = new QStringList;
        test1_item1_distraction->push_back("012-triumph.png");

        map_test1_item3->insert("cible", test1_item3_cible);
        map_test1_item3->insert("distraction", test1_item3_distraction);
//        fin item 3

    niveauTest1->push_back(map_test1_item1);
    niveauTest1->push_back(map_test1_item2);
    niveauTest1->push_back(map_test1_item3);

    niveauxJeuImage->insert("test1", niveauTest1);
//    fin test 1

}

QString arrondir(QString str) {
    return str.sliced(str.indexOf('?') + 1);
}

QVector<QMap<QString ,QStringList*>*>* parseCSV (QString path) {
    QVector<QMap<QString ,QStringList*>*> *retour = new QVector<QMap<QString ,QStringList*>*>;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ouverture du fichier impossible : " << path;
    }
//    Regrouper toutes les lignes dans un tableau
    QStringList lines;
    QTextStream in(&file);
    in.readLine();
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.push_back(line);
    }

//    Spliter les lignes 2 par 2
    QVector<QMap<QString, QString>> lineline;
    for(int i=0; i<lines.length(); i += 2) {
        QMap<QString, QString> item;
        item.insert("titre", lines[i]);
        item.insert("contenu", lines[i+1]);
        lineline.push_back(item);
    }

//    Récuperer les données des lignes
    for(int i=0; i<lineline.length(); i++) {
        QString titre = lineline[i]["titre"];
        QString contenu = lineline[i]["contenu"];
        QStringList splitTitre = titre.split(";");
        QStringList splitContenu = contenu.split(";");

        QStringList cibles;
        QStringList distractors;

        for(int e=0; e<splitTitre.length() && e<splitContenu.length(); e++) {
            QString el_titre = splitTitre[e], el_contenu = splitContenu[e];
            if(!el_contenu.isEmpty()) {
                if(el_titre.contains("cible", Qt::CaseInsensitive)) {
                    cibles.push_back(arrondir(el_contenu));
                } else if(el_titre.contains("distractor", Qt::CaseInsensitive)) {
                    distractors.push_back(arrondir(el_contenu));
                }
            }
        }

        // temp
//        qDebug() << "///////////////////////\nCibles : ";
//        for(QString str : cibles)
//            qDebug() << "\t" << str;
//        qDebug() << "Distractors : ";
//        for(QString str : distractors)
//            qDebug() << "\t" << str;
//        qDebug() << "///////////////////////\n\n";

        QMap<QString, QStringList*> *item = new QMap<QString, QStringList*>;
        item->insert("cibles", new QStringList(cibles));
        item->insert("distractors", new QStringList(distractors));
        retour->push_back(item);
    }
    return retour;
}

void MemoireService::chargerCSV()
{
    niveauxJeuImage = new QMap<QString ,QVector<QMap<QString ,QStringList*>*>*>;
//    Test 1
    QVector<QMap<QString ,QStringList*>*> *test1 = parseCSV("assets/csv/Items_memory_test1.csv");
    niveauxJeuImage->insert("test1", test1);

//    Test 2
    QVector<QMap<QString ,QStringList*>*> *test2 = parseCSV("assets/csv/Items_memory_test2.csv");
    niveauxJeuImage->insert("test2", test2);

//    Test 3
    QVector<QMap<QString ,QStringList*>*> *test3 = parseCSV("assets/csv/Items_memory_test3.csv");
    niveauxJeuImage->insert("test3", test3);

//    Test 4
    QVector<QMap<QString ,QStringList*>*> *test4 = parseCSV("assets/csv/Items_memory_test4.csv");
    niveauxJeuImage->insert("test4", test4);

//    PRACTICE
    QVector<QMap<QString ,QStringList*>*> *practice = parseCSV("assets/csv/Items_memory_practice.csv");
    niveauxJeuImage->insert("practice", practice);

}

const QString &MemoireService::getTypeJeu() const
{
    return typeJeu;
}

void MemoireService::setTypeJeu(const QString &newTypeJeu)
{
    typeJeu = newTypeJeu;
}

QVector<int> *MemoireService::getListeNbErreur() const
{
    return listeNbErreur;
}

QVector<QMap<QString, QStringList *> *> *MemoireService::getListeItem() const
{
    return listeItem;
}

int **MemoireService::getListeNiveau() const
{
    return listeNiveau;
}

void MemoireService::setListeNiveau(int **newListeNiveau)
{
    listeNiveau = newListeNiveau;
}

int MemoireService::getNiveau() const
{
    return niveau;
}

void MemoireService::setNiveau(int newNiveau)
{
    niveau = newNiveau;
}

QVector<TuileMemoire *> MemoireService::trierGrilleAleatoirement(QVector<TuileMemoire *> liste)
{
    int  taille = liste.size();
    for(int i=0; i<taille; i++) {
        int indice = QRandomGenerator::global()->generate()%taille;
        TuileMemoire *temp = liste[i];
        liste[i] =  liste[indice];
        liste[indice] =  temp;
    }
    return liste;
}

int MemoireService::choisirImage(TuileMemoire *tuileMemoire)
{
    //  Je  vérifie que ce n'est pas déjà plein
    if(imagesChoisies->length() >= imagesRetenir->length()) {
        return 2;
    }
    // Je verifie si je ne l'ai pas dejà
    for(int i=0; i<imagesChoisies->length(); i++) {
        if(tuileMemoire == imagesChoisies[0][i]) {
            return -1;
        }
    }

    imagesChoisies->push_back(tuileMemoire);
    bool correct = false;
    for(int i=0; i<imagesRetenir->length(); i++) {
        if (imagesRetenir[0][i] == tuileMemoire) {
            correct = true;
            break;
        }
    }
    if (!correct) {
        qDebug() << "faux";
        nbErreur++;
    }
    if (imagesChoisies->length() >= imagesRetenir->length()) {
        listeNbErreur->push_back(nbErreur);
        return 1;
    }
    return 0;
}

QVector<QVector<TuileMemoire *> *> *MemoireService::getImagesGrilleAff() const
{
    return imagesGrilleAff;
}

QVector<TuileMemoire *> *MemoireService::getImagesDistraction() const
{
    return imagesDistraction;
}

QVector<TuileMemoire *> *MemoireService::getImagesRetenir() const
{
    return imagesRetenir;
}

QVector<TuileMemoire *> *MemoireService::getImagesGrille() const
{
    return imagesGrille;
}
