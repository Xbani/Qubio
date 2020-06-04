#include "qubuttonpersocolor.h"

#include <tools/qutoolsprite.h>

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

QuButtonPersoColor::QuButtonPersoColor():QuButton(14,14)
{
    hue=0;
    sprite_ref=sprite;
}

int QuButtonPersoColor::getHUE()
{
    return hue;
}

void QuButtonPersoColor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)    // Left button...
    {
        hue+=30;
    }
    else if (event->button() == Qt::RightButton)   // Right button...
    {
        qDebug() << "ahuehuee";
        hue-=30;
    }
    sprite=QuToolSprite::SetSpriteCharacterHUE(hue);
    sprite_hover=sprite;
    update();


}
