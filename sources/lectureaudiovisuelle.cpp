#include "lectureaudiovisuelle.h"
#include <QVideoWidget>
#include <QDebug>
#include   "fenetre.h"

LectureAudioVisuelle::LectureAudioVisuelle(QString med, Fenetre *fenetre ,QWidget *parent)
    : QWidget{parent}
{
    this->fenetre = fenetre;
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    player = new QMediaPlayer;


    player->setAudioOutput(new QAudioOutput);
    media = med;
    player->setSource(QUrl::fromLocalFile("assets/audiovisuel/"+media));

//    player->play();
    qDebug () << player->source();

    if(med.startsWith("audio-visuel") || med.startsWith("visuel")) {
        QVideoWidget* vw = new QVideoWidget;
        vlayout->addWidget(vw);
        player ->setVideoOutput(vw);
    } else {
        QVideoWidget *output = new QVideoWidget;
        player ->setVideoOutput(output);

        QWidget *vw = new QWidget;
        QString image = "assets/images/diapo_exemple/plus.png";
        QPixmap img(image);
        img = img.scaled(60, 60, Qt::KeepAspectRatio);
        QLabel *logo = new QLabel;
        logo->setPixmap(img);
        logo->setAlignment(Qt::AlignCenter);

        QHBoxLayout *hlayout = new QHBoxLayout(vw);
        hlayout->addWidget(logo);
        vlayout->addWidget(vw);
    }

//    player->play();
}

LectureAudioVisuelle::~LectureAudioVisuelle()
{
    delete player;
}


void LectureAudioVisuelle::keyPressEvent(QKeyEvent *event)
{
    player->play();
}

bool LectureAudioVisuelle::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Space) ) {
                player->play();
            } else {
                return QObject::eventFilter(obj, event);
            }
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
        return false;
}

