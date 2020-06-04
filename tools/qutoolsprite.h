#ifndef QUTOOLSPRITE_H
#define QUTOOLSPRITE_H

#include <QImage>



class QuToolSprite
{
public:
    QuToolSprite();
public:
    static const QImage SetSpriteCharacterHUE(int hue);
    static const QImage setCharacterHUE(QImage image,int hue);
};

#endif // QUTOOLSPRITE_H
