#include "tuilememoire.h"
#include "memoireservice.h"
#include "memoire.h"

TuileMemoire::TuileMemoire(QString path, MemoireService *memoireService)
{
    this->memoireService = memoireService;
    filenamePath = path;
    QPixmap img(path);
    img = img.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(img);

    rien = QPixmap("assets/images/void.png");
    rien = rien.scaled(100, 100, Qt::KeepAspectRatio);

    resize(100, 100);

}

const QString &TuileMemoire::getFilenamePath() const
{
    return filenamePath;
}

void TuileMemoire::setFilenamePath(const QString &newFilenamePath)
{
    filenamePath = newFilenamePath;
}

void TuileMemoire::mousePressEvent(QMouseEvent *event)
{
    int choix = memoireService->choisirImage(this);
    if (choix == 0 || choix == 1) {
        setPixmap(rien);
    }
    if (choix == 2 || choix == 1) {
        // je finis le niveau
        memoire->getPoint()->show();
        QTimer::singleShot(4000, memoire, &Memoire::passageFinition);
    }
}

Memoire *TuileMemoire::getMemoire() const
{
    return memoire;
}

void TuileMemoire::setMemoire(Memoire *newMemoire)
{
    memoire = newMemoire;
}

//void TuileMemoire::onClick()
//{
//    qDebug() << "yoo";
//}
