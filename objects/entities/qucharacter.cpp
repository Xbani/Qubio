#include "qucharacter.h"
#include "quphysicsconst.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGuiApplication>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <iostream>
#include <QtMath>

#include <QJsonArray>
#include <QJsonObject>
#include <qdatetime.h>

#include <tools/qutoolsprite.h>


QuCharacter::QuCharacter(int instance_id):QuCharacter(instance_id,50)
{

}

QuCharacter::QuCharacter(int instance_id, int hue):QuEntity(instance_id)
{
    setAcceleration({0,QuPhysicsConst::G_FORCE});
    animation_state = STATIC_LEFT;
    strite_static_left  = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_STATIC.png"),hue);
    strite_static_right = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_STATIC.png").mirrored(true, false),hue);
    strite_move_left    = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_MOVE.png"),hue);
    strite_move_right   = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_MOVE.png").mirrored(true, false),hue);
    strite_jump_left    = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_JUMP.png"),hue);
    strite_jump_right   = QuToolSprite::setCharacterHUE(QImage(":/resources/sprites/character/character_JUMP.png").mirrored(true, false),hue);
}

QRectF QuCharacter::boundingRect() const
{
    return QRectF(0,0,QuObject::PIXEL_SIZE*6,QuObject::PIXEL_SIZE*6);
}

void QuCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage * sprite;

    switch( animation_state )
    {
    case STATIC_RIGHT:
        sprite = &strite_static_right;
        break ;
    case STATIC_LEFT :
        sprite = &strite_static_left;
        break ;
    case MOVE_RIGHT :
        if ((QTime::currentTime().msec()) / 100 % 5 <=  2) {
            sprite = &strite_static_right;
        }
        else {
            sprite = &strite_move_right;
        }
        break ;
    case MOVE_LEFT:
        if (QTime::currentTime().msec() / 100 % 5 <=  2) {
            sprite = &strite_static_left;
        }
        else {
            sprite = &strite_move_left;
        }
        break ;
    case JUMP_RIGHT :
        sprite = &strite_jump_right;
        break ;
    case JUMP_LEFT:
        sprite = &strite_jump_left;
        break ;
    default:
        qDebug() << "animation_stats invalid at the animation moment";
        sprite = &strite_static_right;
    }
    QRectF paint_rect = boundingRect();
//    paint_rect.setWidth(paint_rect.width()+2*QuObject::PIXEL_SIZE);
//    paint_rect.setX(paint_rect.x()-1*QuObject::PIXEL_SIZE);
    painter->drawImage(paint_rect, *sprite,QRectF(1,2,6,6));

}

QPainterPath QuCharacter::shape() const
{
    QPainterPath path;
    path.addRect(0,16,64,56);
    return path;
}

QJsonObject QuCharacter::toJSON()
{
    QJsonObject jsonCharacter;
    QJsonArray jsonArrayPosition;
    QJsonArray jsonArrayspeed;
    QJsonArray jsonArrayAcceleration;

    jsonCharacter["instanceId"] = getInstanceId();
    jsonCharacter["classId"] = getClassId();

    jsonArrayPosition.append(pos().x());
    jsonArrayPosition.append(pos().y());
    jsonCharacter["position"] = jsonArrayPosition;

    jsonArrayspeed.append(getSpeed().x());
    jsonArrayspeed.append(getSpeed().y());
    jsonCharacter["speed"] = jsonArrayspeed;

    jsonArrayAcceleration.append(getAcceleration().x());
    jsonArrayAcceleration.append(getAcceleration().y());
    jsonCharacter["acceleration"] = jsonArrayAcceleration;

    return jsonCharacter;
}

void QuCharacter::fromJSON(QJsonObject &qJsonObject)
{
    if(getInstanceId() == qJsonObject["instanceId"].toInt()){
        QJsonArray jsonArray = qJsonObject["position"].toArray();
        QPointF QpoitF;
        QpoitF.setX(jsonArray.at(0).toDouble());
        QpoitF.setY(jsonArray.at(1).toDouble());
        setPos(QpoitF);

        QVector2D vector2d;
        jsonArray = qJsonObject["speed"].toArray();
        vector2d.setX(jsonArray.at(0).toDouble());
        vector2d.setY(jsonArray.at(1).toDouble());
        setSpeed(vector2d);

        jsonArray = qJsonObject["acceleration"].toArray();
        vector2d.setX(jsonArray.at(0).toDouble());
        vector2d.setY(jsonArray.at(1).toDouble());
        setAcceleration(vector2d);
    }
}
