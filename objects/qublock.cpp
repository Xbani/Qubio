#include "qublock.h"

QuBlock::QuBlock():QuBlock(0)
{

}

QuBlock::QuBlock(int texture_id)
{
    texture_id=texture_id;
    QString path=QString(":/resources/block");
    path.append(QString::number(texture_id));
    path.append(".png");
    sprite=QImage(path);
}

QImage QuBlock::getSprite()
{
    return sprite;
}

int QuBlock::getTextureId()
{
    return texture_id;
}
