#include "qubutton.h"

#include <QPainter>
QuButton::QuButton():QuButton(0,0)
{

}

QuButton::QuButton(int texture_id, int texture_hover_id)
{
    setAcceptHoverEvents(true);

    this->texture_id=texture_id;
    this->texture_hover_id=texture_hover_id;

    QString path        = QString(":/resources/sprites/ui/buttons");
    QString path_hover  = QString(":/resources/sprites/ui/buttons");

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
    return QRectF(0,0,sprite_size.width(),sprite_size.height());
}

void QuButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSize sprite_size=sprite.size();
    if(mouse_is_hover)
        painter->drawImage(boundingRect(),sprite,QRectF(0,0,sprite_size.width(),sprite_size.height()));
    else
        painter->drawImage(boundingRect(),sprite_hover,QRectF(0,0,sprite_size.width(),sprite_size.height()));
}

void QuButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mouse_is_hover=true;
}

void QuButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouse_is_hover=false;
}
