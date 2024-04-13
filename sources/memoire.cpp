#include "memoire.h"

Memoire::Memoire(MemoireService *memoireService, Fenetre *f,QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;
    this->memoireService = memoireService;
}

void Memoire::init()
{
    foreach(TuileMemoire  *tuile, memoireService->getImagesGrille()[0])  {
        tuile->setMemoire(this);
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget;
    vlayout->addWidget(stackedWidget);

    //  set
    pagePresentation = new QWidget;
    setPagePresentation();
    pageGrille = new QWidget;
    setPageGrille();
    pageCroixBlanc = new QWidget;
    setPageCroixBlanc();
    pageFinition = new QWidget;
    setPageFinition();
    //

    stackedWidget->addWidget(pagePresentation);
    stackedWidget->addWidget(pageGrille);
    stackedWidget->addWidget(pageCroixBlanc);
    stackedWidget->addWidget(pageFinition);

    stackedWidget->setCurrentIndex(0);

    decompte();

    QPixmap img("assets/images/diapo_exemple/point.png");
    img = img.scaled(35, 35, Qt::KeepAspectRatio);
    point =  new QLabel;
    point->setPixmap(img);
    point->setParent(this);
    point->resize(35, 35);
    point->setStyleSheet("background-color: rgba(250,0,0,0);");
    point->hide();
    point->move((fenetre->width() - 35) /2, (fenetre->height() - 35)/2);
    connect(fenetre, SIGNAL(resized()), this,  SLOT(movePoint()));
}

void Memoire::setPages()
{
    setPagePresentation();
    setPageGrille();
    setPageCroixBlanc();

    stackedWidget->setCurrentIndex(0);
    decompte();
}





void Memoire::movePoint()
{
//    point->move(50, 50);
    point->move((fenetre->width() - 50) /2, (fenetre->height() - 50)/2);
}

void Memoire::setPagePresentation()
{
    QStringList filenames;
    for (int i=0; i<memoireService->getImagesRetenir()->length(); i++) {
        filenames.push_back(memoireService->getImagesRetenir()[0][i]->getFilenamePath());
    }

    QHBoxLayout *hlayout = new QHBoxLayout(pagePresentation);
    qDebug() << "filenames : " << filenames;
    foreach (QString str, filenames) {
        QPixmap img(str);
        img = img.scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel *label = new QLabel;
        label->setPixmap(img);
        hlayout->addWidget(label, 0, Qt::AlignCenter);
    }
}
void Memoire::setPageGrille()
{
    QVector<TuileMemoire*> imagesGrille = memoireService->getImagesGrille()[0];

    QVBoxLayout *vlayout = new QVBoxLayout(pageGrille);

    for (int i=0; i<imagesGrille.length(); ) {
        QHBoxLayout *hlayout = new QHBoxLayout;
        for (int e=0; e<5 && i<imagesGrille.length(); e++) {
            TuileMemoire *tuile = imagesGrille[i];
            tuile->setMemoire(this);
            hlayout->addWidget(tuile, 0, Qt::AlignCenter);
            i++;
        }
        vlayout->addLayout(hlayout);
    }
}




void Memoire::setPageCroixBlanc()
{
    QString image = "assets/images/diapo_exemple/plus.png";
    QPixmap img(image);
    img = img.scaled(60, 60, Qt::KeepAspectRatio);
    QLabel *logo = new QLabel;
    logo->setPixmap(img);
    logo->setAlignment(Qt::AlignCenter);

    QHBoxLayout *hlayout = new QHBoxLayout(pageCroixBlanc);
    hlayout->addWidget(logo);

}

void Memoire::setPageFinition()
{
        QString image= "good-feedback.png";
        QString texte = "FIN DE L'ENTRAINEMENT";
        if (memoireService->getTypeJeu() == "test1") {
            image = "happiness.png";
            texte = "FIN PREMIER TEST DE MEMOIRE";
        }
        else if (memoireService->getTypeJeu() == "test2") {
            image = "happy.png";
            texte = "FIN DEUXIEME TEST DE MEMOIRE";
        }
        else if (memoireService->getTypeJeu() == "test3") {
            image = "birthday.png";
            texte = "FIN TROISIEME TEST DE MEMOIRE";
        }
        else if (memoireService->getTypeJeu() == "test4") {
            image = "sun.png";
            texte = "FIN QUATRIEME TEST DE MEMOIRE";
        }


        QVBoxLayout *hlayout =  new QVBoxLayout(pageFinition);

        QPixmap img("assets/end_memoire/" + image);
        img = img.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel *label = new QLabel;
        label->setPixmap(img);
        label->setAlignment(Qt::AlignCenter);

        QLabel *header = new QLabel(texte);
        header->setFont(QFont("times", 25));
        header->setAlignment(Qt::AlignCenter);
        header->setStyleSheet("color : white");

        hlayout->addStretch();
        hlayout->addWidget(header);
        hlayout->addWidget(label);
        hlayout->addStretch();

}

QLabel *Memoire::getPoint() const
{
    return point;
}

void Memoire::passageGrille()
{
    stackedWidget->setCurrentIndex(1);

}

void Memoire::passageCroixBlanc()
{
    stackedWidget->setCurrentIndex(2);
    QTimer::singleShot(1200, this, &Memoire::passageGrille);
}

void Memoire::passageFinition()
{
    point->hide();
    stackedWidget->setCurrentIndex(3);
    // Je vérifie s'il y a d'autres niveaux
    int niveau = memoireService->getNiveau();
    memoireService->setNiveau(++niveau);
    if(niveau < memoireService->getListeItem()->length()) {
        memoireService->reinitBloc(niveau);
        fenetre->versMemoirePage();
    } else {
        enregistrer();
    }
}

void Memoire::enregistrer()
{
    Utilisateur utilisateur = memoireService->getUtilisateur()[0];
    QString lieu = utilisateur.getLieu() == 1 ? "Hôpital" : "Ecole";
    QString genre = utilisateur.getGenre() == 'f' ? "Fille" : "Garçon";
    QString ligne = utilisateur.getId() + ";" + lieu + ";" + utilisateur.getDate_naissance() + ";" + genre;
    QVector<int> listeNbErreur = this->memoireService->getListeNbErreur()[0];
    for (int nbErreur : listeNbErreur) {
        QString erreur_str = QString::number(nbErreur);
        ligne += ";" + erreur_str;
    }
    qDebug() << ligne;

    QFile file("memoire_"+memoireService->getTypeJeu()+".csv");
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf16);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "le fichier ne peut pas se créer";

    }

    if(file.size() == 0) {
        out << "Nom complet;ID participant;Lieu de test;Date de naissance;Genre;Nb erreurs Item 1;Nb erreurs Item 2;Nb erreurs Item 3;Nb erreurs Item 4;Nb erreurs Item 5;Nb erreurs Item 6;Nb erreurs Item 7;Nb erreurs Item 8;Nb erreurs Item 9;Nb erreurs Item 10\n";
    }
    out << ";" + ligne + "\n";

}

void Memoire::decompte()
{
    int delai = memoireService->getImagesRetenir()->length() < 3 ? 2000 : 3000;
    QTimer::singleShot(delai, this, &Memoire::passageCroixBlanc);
}

//void Memoire::resizeEvent(QResizeEvent *event)
//{
//    qDebug() << "resize";
//}
