#include "qulistblock.h"

QuListBlock::QuListBlock()
{
    metaEnum = QMetaEnum::fromType<QuListBlock::SolidBlock>();
}

QString QuListBlock::getBlockName(QuListBlock::SolidBlock value)
{
    return metaEnum.key(value);
}

QString QuListBlock::getBlockFile(QuListBlock::SolidBlock value)
{
    return FILE_PATH + metaEnum.key(value) + ".png";
}

int QuListBlock::getNumberOfSolidBlock()
{
    return metaEnum.keyCount();
}
