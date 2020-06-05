#include "qucrown.h"

#include <QPainter>

QuCrown::QuCrown()
{
    sprite_crown = QImage(":/resources/sprites/character/crown.png");
}

QRectF QuCrown::boundingRect() const
{
    return QRectF(0,0,QuObject::PIXEL_SIZE*6,QuObject::PIXEL_SIZE*4);
}

void QuCrown::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(), sprite_crown,QRectF(0,0,6,4));
}

void QuCrown::setPos(qreal x, qreal y)
{
    setX(x);
    setY(y);
}

int QuCrown::getClassId()
{
    return QuEntity::CROWN_ID;
}
