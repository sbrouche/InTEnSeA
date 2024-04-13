#ifndef INSTRUCTIONMEMOIRE_H
#define INSTRUCTIONMEMOIRE_H

#include <QtWidgets>

class Fenetre;

class InstructionMemoire : public QWidget
{
    Q_OBJECT
public:
    explicit InstructionMemoire(QString destination, Fenetre * f, QWidget *parent = nullptr);
    void init();


    void mousePressEvent ( QMouseEvent * event);


    QStackedWidget *getStackedWidget() const;

signals:
    void clicked();

private slots:
    void onPageSuivant();

private:
    void setPage1();
    void setPage2();

    QStackedWidget *stackedWidget;
    QString destination;

    QWidget *page1;
    QWidget *page2;

    Fenetre *fenetre;

};

#endif // INSTRUCTIONMEMOIRE_H
