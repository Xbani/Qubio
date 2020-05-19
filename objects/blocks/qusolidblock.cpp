#include "qusolidblock.h"

#include <QJsonObject>
#include <QPainter>

QuSolidBlock::QuSolidBlock():QuSolidBlock(0)
{

}

QuSolidBlock::QuSolidBlock(int texture_block_id):QuBlock(texture_block_id)
{

}

QRectF QuSolidBlock::boundingRect() const
{
    QSize sprite_size=getSprite().size();
    return QRectF(0,0,sprite_size.width(),sprite_size.height());
}

void QuSolidBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSize sprite_size=getSprite().size();
    painter->drawImage(boundingRect(),QImage(":/resources/block1.png"),QRectF(0,0,sprite_size.width(),sprite_size.height()));
}

QJsonObject QuSolidBlock::toJSON()
{
    return QJsonObject();
}
