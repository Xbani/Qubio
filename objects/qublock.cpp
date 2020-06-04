#include "qublock.h"

#include <objects/enumblock/qulistblock.h>

QuBlock::QuBlock():QuBlock(0)
{

}

QuBlock::QuBlock(int texture_id)
{
    this->texture_id=texture_id;
    QuListBlock quListBlock;
    sprite=QImage(quListBlock.getBlockFile(QuListBlock::SolidBlock(texture_id)));
}

QImage QuBlock::getSprite() const
{
    return sprite;
}

int QuBlock::getTextureId() const
{
    return texture_id;
}
