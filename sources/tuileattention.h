#ifndef TUILEATTENTION_H
#define TUILEATTENTION_H

#include <QLabel>

class AttentionService;
class Attention;

class TuileAttention : public QLabel
{
public:
    TuileAttention(int id, QString filepath, AttentionService *attentionService);

    const QString &getFilepath() const;
    void mousePressEvent(QMouseEvent *event);
    int getId() const;

    Attention *getAttention() const;
    void setAttention(Attention *newAttention);

private :
    AttentionService *attentionService;
    Attention *attention;

    QString filepath;
    int id;
};

#endif // TUILEATTENTION_H
