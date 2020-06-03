#include "quplayerinfo.h"

#include <QColor>
#include <QJsonObject>
#include <QPainter>

#include <tools/qutoolsprite.h>


QuPlayerInfo::QuPlayerInfo(int player_id, QString player_name, int player_hue, int pos)
{
    this->player_id=player_id;
    this->player_name=player_name;
    this->player_hue=player_hue;
    this->pos=pos;
    sprite=QImage(":/resources/sprites/ui/playerinfo.png");
    sprite_player=QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/ui/buttons/button14.png"),player_hue);
}

QRectF QuPlayerInfo::boundingRect() const
{
    QSize sprite_size=sprite.size();
    return QRectF(0,
                  0,
                  sprite_size.width()*QuObject::PIXEL_SIZE,
                  sprite_size.height()*QuObject::PIXEL_SIZE);
}

void QuPlayerInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSize sprite_size=sprite.size();
    QSize sprite_perso_size= sprite_player.size();

    QRect perso_rect = QRect(boundingRect().width()-sprite_perso_size.width()*QuObject::PIXEL_SIZE*2,
                             -QuObject::PIXEL_SIZE*2+sprite_perso_size.height()*QuObject::PIXEL_SIZE*2*pos,
                             sprite_perso_size.width()*QuObject::PIXEL_SIZE*2,
                             sprite_perso_size.height()*QuObject::PIXEL_SIZE*2);

    painter->drawImage(boundingRect(),sprite,sprite.rect());
    painter->drawImage(perso_rect,sprite_player,sprite_player.rect());

    painter->setFont(QFont("Sans Serif", 42));
    painter->setPen(Qt::red);
    painter->drawText(boundingRect().bottomLeft(),player_name);
}

QJsonObject* QuPlayerInfo::toJSON()
{
    return new QJsonObject(); //do nothing
}

void QuPlayerInfo::fromJSON(QJsonObject &qJsonObject)
{
    //do nothing
}
