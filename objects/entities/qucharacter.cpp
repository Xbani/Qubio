#include "qucharacter.h"

QuCharacter::QuCharacter()
{

}
QuCharacter::QuCharacter(int instance_id):QuEntity(instance_id)
{

}
void QuCharacter::step()
{
    //TODO
}

QRectF QuCharacter::boundingRect() const
{
    return QRectF(0,0,0,0);//TODO
}

void QuCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
