#ifndef QUBLOCK_H
#define QUBLOCK_H

#include "quobject.h"


/**
 * @brief The QuBlock class
 * @details Class which represent a game block
 */
class QuBlock : public QuObject
{
private:
    QImage sprite;
    int texture_id;
public:
    QuBlock();
    QuBlock(int texture_id);

    QImage getSprite() const;
    int getTextureId() const;

public:
    static const int MAX_TEXTURE_ID=1;
};

#endif // QUBLOCK_H
