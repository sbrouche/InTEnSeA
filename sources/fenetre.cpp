#include "fenetre.h"
#include "mainmenu.h"
#include "formulaireutilisateur.h"
#include "menusensoriel.h"
#include "menumemoire.h"
#include "menuattention.h"
#include "instructionmemoire.h"
#include "memoire.h"
#include "attention.h"
#include "lectureaudiovisuelle.h"
#include "questionnaire.h"

Fenetre::Fenetre(MemoireService * memoireService, AttentionService* attentionService,QWidget *parent)
    : QMainWindow{parent}
{
    // Barre d'outil
    QAction *actionAccueil = new QAction("Accueil" ,this);
    QToolBar *toolBarFichier= addToolBar("fichier");
    toolBarFichier->addAction(actionAccueil);
    toolBarFichier->setStyleSheet("color: white");

    this->memoireService = memoireService;
    this->attentionService = attentionService;

    resize(1366, 768);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//    this->show();
    this->showFullScreen();
    setFixedSize(width(), height());

    versPageMainMenu();

    connect(actionAccueil, SIGNAL(triggered()), this, SLOT(versPageMainMenu()));
}

void Fenetre::setPageDiaporama(QString mode)
{
    Diaporama *page = new Diaporama(mode, memoireService, attentionService, this);

    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    page->setStyleSheet("background-color : rgb(14,14,14;)");
}

void Fenetre::versPageMainMenu()
{
    MainMenu *menu = new MainMenu(memoireService, attentionService, this);

    setCentralWidget(menu);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    menu->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versAttentionPage()
{
    Attention *page = new Attention(attentionService, this);
    setCentralWidget(page);
    page->init();
    this->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versMemoirePage()
{
    Memoire *page = new Memoire(memoireService, this);
    setCentralWidget(page);
    page->init();
    this->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versMenuMemoirePage()
{
    MenuMemoire *page = new MenuMemoire(memoireService, this);

    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

}

void Fenetre::versMenuAttentionPage()
{
    MenuAttention *page = new MenuAttention(attentionService, this);

    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

}

void Fenetre::versFormulaireUtilisateur(QString destination)
{
    FormulaireUtilisateur *page = new FormulaireUtilisateur(memoireService, attentionService, this, destination);

    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");


}

void Fenetre::versSousMenuSensorielPage(QVector<sensoriel_bouton> *bts)
{
    SousMenuSensoriel *page = new SousMenuSensoriel(bts, this);
    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    page->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versMenuSensorielPage()
{
    MenuSensoriel *page = new MenuSensoriel(this);
    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    page->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versAudioVisuelPage(QString media)
{
    LectureAudioVisuelle *page = new LectureAudioVisuelle(media, this);
    installEventFilter(page);

    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    page->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versInstruction(QString destination)
{
    InstructionMemoire *page = new InstructionMemoire(destination, this);
    setCentralWidget(page);
    this->setStyleSheet("background-color : rgb(14,14,14);");

    page->setStyleSheet("background-color : rgb(14,14,14);");
}

void Fenetre::versQuestionnairePage()
{
    Questionnaire *page = new Questionnaire(this);
    setCentralWidget(page);
    this->setStyleSheet("background-color : white;");

    page->setStyleSheet("background-color : white;");
}



