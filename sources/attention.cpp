#include "attention.h"

Attention::Attention(AttentionService *attentionService, Fenetre *f ,QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = f;
    this->attentionService = attentionService;
}

void Attention::init()
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget (this) ;
    resize(1920, 1080);
    vlayout->addWidget(stackedWidget);
    vlayout->addStretch();

    // pages
    this->pagePresentation = new QWidget;
    this->pageCroixBlanc = new QWidget;
    this->pageGrille = new QWidget;
    this->pageFinition = new QWidget;

    this->stackedWidget->addWidget(pagePresentation);
    setPagePresentation();
    this->stackedWidget->addWidget(pageCroixBlanc);
    setPageCroixBlanc();
    this->stackedWidget->addWidget(pageGrille);
    setPageGrille();
    this->stackedWidget->addWidget(pageFinition);
    setPageFinition();

    this->stackedWidget->setCurrentIndex(0);

    decompte();

}


void Attention::passageCroixBlanc()
{
    this->stackedWidget->setCurrentIndex(1);
    QTimer::singleShot(1200, this, &Attention::passageGrille);
}

void Attention::passageGrille()
{
 this->stackedWidget->setCurrentIndex(2);
//Début du chronomètre
       attentionService->getChrono()->restart();

    QTimer::singleShot(120000, this, &Attention::timedOut);
}

void Attention::timedOut() {
    attentionService->getListeTemps()->push_back(0);
    passageFinition();
}

void Attention::passageFinition()
{
    if(stackedWidget->currentIndex() != 3 || stackedWidget->currentIndex() != 1) {
        // Je vérifie s'il y a d'autres niveaux
        int niveau = attentionService->getNiveau();
        niveau++;
        if(niveau < attentionService->getListeItem()->length()) {
            stackedWidget->setCurrentIndex(1);
            QTimer::singleShot(1100, this, &Attention::blocSuivant);
        } else {
            // L'exercice est terminé
            int chrono = attentionService->getChrono()->elapsed();
            qDebug() << chrono;
            stackedWidget->setCurrentIndex(3);
            enregistrer();
        }
    }
}

void Attention::blocSuivant()
{
    int niveau = attentionService->getNiveau();
    niveau++;
    attentionService->initBloc(niveau);
    fenetre->versAttentionPage();
}

void Attention::enregistrer()
{
    Utilisateur utilisateur = attentionService->getUtilisateur()[0];
    QString lieu = utilisateur.getLieu() == 1 ? "Hôpital" : "Ecole";
    QString genre = utilisateur.getGenre() == 'f' ? "Fille" : "Garçon";
    QString ligne = utilisateur.getId() + ";" + lieu + ";" + utilisateur.getDate_naissance() + ";" + genre;
    QVector<int> listeChrono = attentionService->getListeTemps()[0];
    for (int chrono : listeChrono) {
        double chrono_float = ((float) chrono) / 1000.0;
        QString chrono_str = QString::number(chrono_float, 'f', 3);
        ligne += ";" + chrono_str;
    }
    qDebug() << ligne;

    QFile file("attention_"+attentionService->getTypeJeu()+".csv");
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf16);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "le fichier ne peut pas se créer";

    }

    if(file.size() == 0) {
        out << "Nom complet;ID participant;Lieu de test;Date de naissance;Genre;Temps de réponse Item 1;Temps de réponse Item 2;Temps de réponse Item 3;Temps de réponse Item 4\n";
    }
    out << ";" + ligne + "\n";

}

void Attention::decompte()
{
    QTimer::singleShot(2200, this, &Attention::passageCroixBlanc);
}

void Attention::setPagePresentation()
{
    QHBoxLayout *hlayout = new QHBoxLayout(pagePresentation);

    QString image = attentionService->getImagesRetenir()[0][0]->getFilepath();
    qDebug() << image;
    QPixmap img(image);
    img = img.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *label = new QLabel;
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(img);

    hlayout->addWidget(label);
}

void Attention::setPageCroixBlanc()
{
    QVBoxLayout *hlayout = new QVBoxLayout(pageCroixBlanc);
    hlayout->addStretch();

    QString image = "assets/images/diapo_exemple/plus.png";
    QPixmap img(image);
    img = img.scaled(60, 60, Qt::KeepAspectRatio);
    QLabel *logo = new QLabel;
    logo->setPixmap(img);
    logo->setAlignment(Qt::AlignCenter);


    hlayout->addWidget(logo);
    hlayout->addStretch();

}

void Attention::setPageGrille()
{
    QVBoxLayout *hlayout = new QVBoxLayout(pageGrille);

    QVector<QVector<TuileAttention*>*> *imagesGrilleAff = attentionService->getImagesGrilleAff();

    QGridLayout *grid = new QGridLayout;
    for(int i=0; i<imagesGrilleAff->length(); i++) {
        QVector<TuileAttention*> *tab = imagesGrilleAff[0][i];
        int colonne = i % 2;
        for(int e=0; e<tab->length(); e++) {
            TuileAttention *tuile = tab[0][e];
            tuile->setAttention(this);
            grid->addWidget(tuile, i, colonne, 1, 2);
            colonne += 2;
        }
    }
//    grid->setAlignment(Qt::AlignCenter);
    hlayout->addLayout(grid, 0);
}

void Attention::setPageFinition()
{
    QVBoxLayout *hlayout =  new QVBoxLayout(pageFinition);

    QPixmap img("assets/images/diapo_exemple/check.png");
    img = img.scaled(125, 125, Qt::KeepAspectRatio);
    QLabel *label = new QLabel;
    label->setPixmap(img);
    label->setAlignment(Qt::AlignCenter);
    hlayout->addWidget(label);
}
