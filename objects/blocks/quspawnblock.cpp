#include "quspawnblock.h"

#include <QJsonObject>

QuSpawnBlock::QuSpawnBlock()
{

}

QRectF QuSpawnBlock::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void QuSpawnBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Nothing to do here
}

QJsonObject QuSpawnBlock::toJSON()
{
    return QJsonObject(); //TODO
}

void QuSpawnBlock::fromJSON(QJsonObject qJsonObject)
{
    //TODO
}
