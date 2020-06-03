#include "quplayerinfo.h"

#include <QColor>
#include <QJsonObject>
#include <QPainter>

QuPlayerInfo::QuPlayerInfo():QuPlayerInfo("",QColor())
{

}

QuPlayerInfo::QuPlayerInfo(QString player_name, QColor player_color)
{
    this->player_name=player_name;
    this->player_color=player_color;
    sprite=QImage(":/resources/sprites/ui/playerinfo.png");
    sprite_player=QImage(":/resources/sprites/ui/buttons/button14.png");
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
    QSize sprite_perso_size=sprite_player.size();

    QRect perso_rect = QRect(boundingRect().width()-sprite_perso_size.width()*QuObject::PIXEL_SIZE,
                             0,
                             sprite_perso_size.width()*QuObject::PIXEL_SIZE,
                             sprite_perso_size.height()*QuObject::PIXEL_SIZE);

    painter->drawImage(boundingRect(),sprite,sprite.rect());
    painter->drawImage(perso_rect,sprite_player,sprite_player.rect());

    painter->setFont(QFont("Sans Serif", 42));
    painter->drawText(boundingRect().bottomLeft(),player_name);
}

QJsonObject QuPlayerInfo::toJSON()
{
    return QJsonObject(); //do nothing
}

void QuPlayerInfo::fromJSON(QJsonObject &qJsonObject)
{
    //do nothing
}
