#ifndef TUILEMEMOIRE_H
#define TUILEMEMOIRE_H


#include <QLabel>
#include <QObject>

class MemoireService;
class Memoire;

class TuileMemoire : public QLabel
{

public:

    TuileMemoire(QString path, MemoireService *memoireService);

    const QString &getFilenamePath() const;
    void setFilenamePath(const QString &newFilenamePath);
    void mousePressEvent ( QMouseEvent * event);

//private slots:
//    void onClick();

    Memoire *getMemoire() const;
    void setMemoire(Memoire *newMemoire);

private:
    QString filenamePath;
    MemoireService *memoireService;

    Memoire *memoire;

    QPixmap rien;
};

#endif // TUILEMEMOIRE_H
