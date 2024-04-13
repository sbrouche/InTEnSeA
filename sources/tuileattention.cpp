#include "tuileattention.h"
#include "attentionservice.h"
#include "attention.h"

TuileAttention::TuileAttention(int id, QString filepath, AttentionService *attentionService) : QLabel()
{
    this->filepath = filepath;
    this->id = id;
    this->attentionService = attentionService;

    QPixmap img(filepath);
    img = img.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    resize(50, 50);
    setPixmap(img);

//    setStyleSheet("margin-right : 15px;");
}

const QString &TuileAttention::getFilepath() const
{
    return filepath;
}

void TuileAttention::mousePressEvent(QMouseEvent *event)
{
    int reponse = attentionService->choisirTuile(this);
    if(reponse % 2 == 1) {
        QPixmap img("assets/images/void.png");
        img = img.scaled(50,50);
        setPixmap(img);
    }
    if (reponse >= 3) {
        this->getAttention()->passageFinition();
    }
}

int TuileAttention::getId() const
{
    return id;
}

Attention *TuileAttention::getAttention() const
{
    return attention;
}

void TuileAttention::setAttention(Attention *newAttention)
{
    attention = newAttention;
}
