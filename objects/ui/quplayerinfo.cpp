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
    QSize sprite_size=sprite.size();
    setY(sprite_size.height()*QuObject::PIXEL_SIZE*pos);
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
                             -QuObject::PIXEL_SIZE*2,
                             sprite_perso_size.width()*QuObject::PIXEL_SIZE*2,
                             sprite_perso_size.height()*QuObject::PIXEL_SIZE*2);

    painter->drawImage(boundingRect(),sprite,sprite.rect());
    painter->drawImage(perso_rect,sprite_player,sprite_player.rect());

    painter->setFont(QFont("Sans Serif", TEXT_FONT_SIZE));
    painter->setPen(QColor(242, 211, 171));

    // to center the text
    int xGap = QuObject::PIXEL_SIZE * 3;
    int yGap = sprite.size().height()*QuObject::PIXEL_SIZE /2 - TEXT_FONT_SIZE / 2;

    qreal xCoord = boundingRect().bottomLeft().x() + xGap;
    qreal yCoord = boundingRect().bottomLeft().y() - yGap;
    QPointF pointWhereDraw = boundingRect().bottomLeft();
    pointWhereDraw.setX(xCoord);
    pointWhereDraw.setY(yCoord);
    painter->drawText(pointWhereDraw, player_name);
}

QJsonObject* QuPlayerInfo::toJSON()
{
    return new QJsonObject(); //do nothing
}

void QuPlayerInfo::fromJSON(QJsonObject &qJsonObject)
{
    //do nothing
}
