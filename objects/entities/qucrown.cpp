#include "qucrown.h"

#include <QJsonObject>
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

QJsonObject *QuCrown::toJSON()
{
    return new QJsonObject();
}

void QuCrown::fromJSON(QJsonObject &qJsonObject)
{

}

int QuCrown::getClassId()
{
    return QuEntity::CROWN_ID;
}

void QuCrown::advance(int phase)
{
    if(phase){
        return;
    }
    if(getOwner()!=nullptr){
        setPos(getOwner()->pos());
    }
}
