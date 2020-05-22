#include "qubutton.h"

#include <QDebug>
#include <QJsonObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
QuButton::QuButton():QuButton(0,0)
{

}

QuButton::QuButton(int texture_id, int texture_hover_id)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlags(ItemIsFocusable);
    this->texture_id=texture_id;
    this->texture_hover_id=texture_hover_id;

    QString path        = QString(":/resources/sprites/ui/buttons/button");
    QString path_hover  = QString(":/resources/sprites/ui/buttons/button");

    path.append(QString::number(texture_id));
    path_hover.append(QString::number(texture_hover_id));

    path.append(".png");
    path_hover.append(".png");

    sprite          = QImage(path);
    sprite_hover    = QImage(path_hover);
}

QRectF QuButton::boundingRect() const
{
    QSize sprite_size=sprite.size();
    return QRectF(-sprite_size.width()*QuObject::PIXEL_SIZE/2,
                  -sprite_size.height()*QuObject::PIXEL_SIZE/2,
                  sprite_size.width()*QuObject::PIXEL_SIZE,
                  sprite_size.height()*QuObject::PIXEL_SIZE);
}

void QuButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSize sprite_size=sprite.size();
    painter->fillRect(boundingRect(),scene()->backgroundBrush());
    if(!mouse_is_hover)
        painter->drawImage(boundingRect(),sprite,sprite.rect());
    else
        painter->drawImage(boundingRect(),sprite_hover,QRectF(0,0,sprite_size.width(),sprite_size.height()));
}

void QuButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mouse_is_hover=true;
    update(boundingRect());
}

void QuButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouse_is_hover=false;
    update(boundingRect());
}

QJsonObject QuButton::toJSON()
{
    return QJsonObject();
}

void QuButton::fromJSON(QJsonObject qJsonObject)
{
    //do nothing
}

void QuButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}
