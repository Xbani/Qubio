#include "qutoolsprite.h"

QuToolSprite::QuToolSprite()
{

}

const QImage QuToolSprite::SetSpriteCharacterHUE(int hue)
{
    QImage sprite_ref=QImage(":/resources/sprites/ui/buttons/button14.png");
    QImage sprite_new=sprite_ref;

    QSize sprite_size=sprite_ref.size();

    QColor light_ref=sprite_ref.pixelColor(1,7);
    QColor dark_ref=sprite_ref.pixelColor(5,4);

    QColor light_new=light_ref;
    light_new.setHsl(hue+light_ref.hue()%360,light_ref.saturation(),light_ref.value());

    QColor dark_new=dark_ref;
    dark_new.setHsl((hue+dark_ref.hue())%360,dark_ref.saturation(),dark_ref.value());

    for(int i=0; i<sprite_size.width();i++){
        for(int j=0; j<sprite_size.height();j++){
            if(sprite_ref.pixelColor(i,j)==light_ref)
                sprite_new.setPixelColor(i,j,light_new);
            if(sprite_ref.pixelColor(i,j)==dark_ref)
                sprite_new.setPixelColor(i,j,dark_new);
        }
    }
    return sprite_new;
}

const QImage QuToolSprite::setCharacterHUE(QImage sprite_ref, int hue)
{
    QImage sprite_new=sprite_ref;

    QSize sprite_size=sprite_ref.size();

    QColor light_ref=sprite_ref.pixelColor(1,7);
    QColor dark_ref=sprite_ref.pixelColor(5,4);

    QColor light_new=light_ref;
    light_new.setHsl(hue+light_ref.hue()%360,light_ref.saturation(),light_ref.value());

    QColor dark_new=dark_ref;
    dark_new.setHsl((hue+dark_ref.hue())%360,dark_ref.saturation(),dark_ref.value());

    for(int i=0; i<sprite_size.width();i++){
        for(int j=0; j<sprite_size.height();j++){
            if(sprite_ref.pixelColor(i,j)==light_ref)
                sprite_new.setPixelColor(i,j,light_new);
            if(sprite_ref.pixelColor(i,j)==dark_ref)
                sprite_new.setPixelColor(i,j,dark_new);
        }
    }
    return sprite_new;
}

