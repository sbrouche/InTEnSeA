#include "instructionmemoire.h"
#include "fenetre.h"

InstructionMemoire::InstructionMemoire(QString destination, Fenetre * f,QWidget *parent)
    : QWidget{parent}
{
    this->destination = destination;
    this->fenetre = f;
    init();
}

void InstructionMemoire::init()
{
    stackedWidget  = new QStackedWidget;
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    vlayout->addWidget(stackedWidget);

    page1 = new QWidget;
    setPage1();
    page2 = new QWidget;
    setPage2();

    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);

    stackedWidget->setCurrentIndex(0);

    this->connect(this, SIGNAL(clicked()), this, SLOT(onPageSuivant()));
}

void InstructionMemoire::setPage1()
{
    QLabel *phrase1 = new QLabel("Bonjour et bienvenue à l'étude InTEnSeA");
    phrase1->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase1->setAlignment(Qt::AlignCenter);
    QLabel *phrase2 = new QLabel("Un grand merci pour ta participation");
    phrase2->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase2->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vlayout = new QVBoxLayout(page1);
    vlayout->addStretch();
    vlayout->addWidget(phrase1);
    vlayout->addWidget(phrase2);
    vlayout->addStretch();
}

void InstructionMemoire::setPage2()
{
    QLabel *phrase1 = new QLabel("Pour cette tâche, tu vas voir apparaître une ou plusieurs images");
    phrase1->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase1->setAlignment(Qt::AlignCenter);
    QLabel *phrase2 = new QLabel("Tu dois la mémoriser");
    phrase2->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase2->setAlignment(Qt::AlignCenter);
    QLabel *phrase3 = new QLabel("Ensuite, tu devras retrouver l'image parmi d'autres images");
    phrase3->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase3->setAlignment(Qt::AlignCenter);
    QLabel *phrase4 = new QLabel("Clique pour continuer");
    phrase4->setStyleSheet("font-size: 35px; color: white; margin: 20px;");
    phrase4->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vlayout = new QVBoxLayout(page2);
    vlayout->addStretch();
    vlayout->addWidget(phrase1);
    vlayout->addWidget(phrase2);
    vlayout->addWidget(phrase3);
    vlayout->addWidget(phrase4);
    vlayout->addStretch();
}

QStackedWidget *InstructionMemoire::getStackedWidget() const
{
    return stackedWidget;
}



void InstructionMemoire::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void InstructionMemoire::onPageSuivant()
{
    int index = stackedWidget->currentIndex();
    if (index < 1) {
        stackedWidget->setCurrentIndex(index+1);
    } else {

        if (destination == "memoire") {

            QStringList images;

            images.push_back("assets/diaporama/memoire/1.png");
            images.push_back("assets/diaporama/memoire/2.png");
            images.push_back("assets/diaporama/memoire/3.png");
            images.push_back("assets/diaporama/memoire/4.png");
            images.push_back("assets/diaporama/memoire/5.png");

            fenetre->versMenuMemoirePage();



        } else if (destination == "attention") {
            QStringList images;

            images.push_back("assets/diaporama/attention/1.png");
            images.push_back("assets/diaporama/attention/2.png");
            images.push_back("assets/diaporama/attention/3.png");
            images.push_back("assets/diaporama/attention/4.png");
            images.push_back("assets/diaporama/attention/5.png");
            images.push_back("assets/diaporama/attention/6.png");

            fenetre->versMenuAttentionPage();
        } else {
            qDebug() << "tsisy aleha";
        }

    }
}
