#include "qublock.h"

QuBlock::QuBlock():QuBlock(0)
{

}

QuBlock::QuBlock(int texture_id)
{
    this->texture_id=texture_id;
    QString path=QString(":/resources/block");
    path.append(QString::number(texture_id));
    path.append(".png");
    sprite=QImage(path);
}

QImage QuBlock::getSprite() const
{
    return sprite;
}

int QuBlock::getTextureId() const
{
    return texture_id;
}
