#include "diaporama.h"
#include "fenetre.h"

Diaporama::Diaporama(QString mode, MemoireService *memoireService, AttentionService *attentionService, Fenetre *fenetre, QWidget *parent)
    : QWidget{parent}
{
    this->memoireService = memoireService;
    this->attentionService = attentionService;
    this->fenetre = fenetre;
    this->mode = mode;
    QHBoxLayout *layout = new QHBoxLayout(this);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    QStringList filenames;
    QDir directory("assets/diaporama/" + mode);
    filenames = directory.entryList(QStringList() << "*.png", QDir::Files);

    stackWidget = new QStackedWidget;
    stackWidget->setStyleSheet("background-color : rgb(14,14,14);");
    for (QString str : filenames) {
//        QVBoxLayout *stackLayout = new QVBoxLayout(stackWidget);
        QPixmap img("assets/diaporama/" + mode + "/" + str);
        img = img.scaled(fenetre->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel *label = new QLabel;
        qDebug() << fenetre->size();
        label->resize(fenetre->size());
        label->setPixmap(img);
        stackWidget->addWidget(label);
    }

    stackWidget->setCurrentIndex(0);
    layout->addWidget(stackWidget, 0, Qt::AlignCenter);

    QLabel *titre = new QLabel("Exemple", this);
    titre->setStyleSheet("color : white; background-color: rgba(0,0,0,0)");
    titre->setFont(QFont("Times", 30));
    titre->resize(200, 50);
    titre->move(20,20);

    QWidget *footer = new QWidget(this);
    footer->resize(fenetre->width(), 50);
    footer->setStyleSheet("background-color : rgba(14,14,14,0);");
    QPushButton *bt_suivant = new QPushButton("Suivant");
    bt_suivant->setStyleSheet("width : 30px; height : 100px; background-color : white;");
    QPushButton *bt_precedent = new QPushButton("Précédent");
    bt_precedent->setStyleSheet("width : 30px; height : 100px; background-color : white;");
    QHBoxLayout *hlayout = new QHBoxLayout(footer);
    hlayout->addWidget(bt_precedent, 0, Qt::AlignLeft);
    hlayout->addWidget(bt_suivant, 0, Qt::AlignRight);
    footer->move(0, fenetre->height() - 100);

    connect(bt_suivant, SIGNAL(clicked()), this, SLOT(onPageSuivant()));
    connect(bt_precedent, SIGNAL(clicked()), this, SLOT(onPagePrecedent()));
}

void Diaporama::onPageSuivant()
{
    int index = stackWidget->currentIndex();
    if(++index < stackWidget->count()) {
        stackWidget->setCurrentIndex(index);
    } else {
        if(mode == "memoire") {
            this->memoireService->init();
            fenetre->versMemoirePage();
        } else if(mode == "attention") {
            this->attentionService->init();
            fenetre->versAttentionPage();

        }
    }
}

void Diaporama::onPagePrecedent()
{
    int index = stackWidget->currentIndex();
    if(--index >= 0) {
        stackWidget->setCurrentIndex(index);
    }
}

