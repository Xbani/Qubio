#include "qubuttonpersocolor.h"

#include <tools/qutoolsprite.h>

QuButtonPersoColor::QuButtonPersoColor():QuButton(14,14)
{
    hue=0;
    sprite_ref=sprite;
}

void QuButtonPersoColor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    hue+=30;
    sprite=QuToolSprite::SetSpriteCharacterHUE(hue);
    sprite_hover=sprite;
    update();

}
