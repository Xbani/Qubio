#ifndef QUCHARACTER_H
#define QUCHARACTER_H

#include <objects/quentity.h>



class QuCharacter : public QuEntity
{
private:
    QString name;
    QColor color;
    int statement;
public:
    QuCharacter();
    void step();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    static const int STATIC_RIGHT =  1;
    static const int  STATIC_LEFT = -1;
    static const int   MOVE_RIGHT =  2;
    static const int    MOVE_LEFT = -2;
    static const int   JUMP_RIGHT =  3;
    static const int    JUMP_LEFT = -3;
};

#endif // QUCHARACTER_H
