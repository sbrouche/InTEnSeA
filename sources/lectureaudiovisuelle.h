#ifndef LECTUREAUDIOVISUELLE_H
#define LECTUREAUDIOVISUELLE_H

#include <QWidget>
#include <QAudioOutput>
#include <QMediaPlayer>

class Fenetre;

class LectureAudioVisuelle : public QWidget
{
    Q_OBJECT
public:
    explicit LectureAudioVisuelle(QString med, Fenetre *fenetre, QWidget *parent = nullptr);
    ~LectureAudioVisuelle();

    virtual void keyPressEvent( QKeyEvent * event );

signals:

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private :
    Fenetre *fenetre;

    QMediaPlayer *player;

    QString media;

};

#endif // LECTUREAUDIOVISUELLE_H
