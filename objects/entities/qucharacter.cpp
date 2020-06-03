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

QuCharacter::QuCharacter()
{
    setAcceleration({0,QuPhysicsConst::G_FORCE});
}

QuCharacter::QuCharacter(int instance_id):QuEntity(instance_id)
{

}

QRectF QuCharacter::boundingRect() const
{
    return QRectF(0,0,QuObject::PIXEL_SIZE*6,QuObject::PIXEL_SIZE*6);
}

void QuCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // painter->drawImage(boundingRect(),QImage(":/resources/sprites/character/character_JUMP.png"),QRectF(1,2,6,6));
    qDebug() << animation_state;
    if (animation_state == STATIC_RIGHT  || animation_state == STATIC_LEFT) {
        painter->drawImage(boundingRect(),QImage(":/resources/sprites/character/character_STATIC.png"),QRectF(1,2,6,6));
        qDebug() << "STATIC";
    }
    else if (animation_state == MOVE_RIGHT  || animation_state == MOVE_LEFT) {
        painter->drawImage(boundingRect(),QImage(":/resources/sprites/character/character_MOVE.png"),QRectF(1,2,6,6));
        qDebug() << "MOVE";
    }
    else {
        painter->drawImage(boundingRect(),QImage(":/resources/sprites/character/character_JUMP.png"),QRectF(1,2,6,6));
        qDebug() << "JUMP";
    }

}

QPainterPath QuCharacter::shape() const
{
    QPainterPath path;
    path.addRect(0,16,64,56);
    return path;
}

QJsonObject QuCharacter::toJSON()
{
//    QJsonObject jsonCharacter;
//    QJsonArray jsonArrayPosition;
//    QJsonArray jsonArrayspeed;
//    QJsonArray jsonArrayAcceleration;

//    jsonCharacter["instanceId"] = getInstanceId();
//    jsonCharacter["classId"] = getClassId();

//    jsonArrayPosition.append(getPosition().x());
//    jsonArrayPosition.append(getPosition().y());
//    jsonCharacter["position"] = jsonArrayPosition;

//    jsonArrayspeed.append(getSpeed().x());
//    jsonArrayspeed.append(getSpeed().y());
//    jsonCharacter["speed"] = jsonArrayspeed;

//    jsonArrayAcceleration.append(getAcceleration().x());
//    jsonArrayAcceleration.append(getAcceleration().y());
//    jsonCharacter["acceleration"] = jsonArrayAcceleration;

//    return jsonCharacter;
}

void QuCharacter::fromJSON(QJsonObject &qJsonObject)
{
//    if(getInstanceId() == qJsonObject["instanceId"].toInt()){
//        QJsonArray jsonArray = qJsonObject["position"].toArray();
//        QVector2D vector2d;
//        vector2d.setX(jsonArray.at(0).toDouble());
//        vector2d.setX(jsonArray.at(1).toDouble());
//        setPosition(vector2d);

//        jsonArray = qJsonObject["speed"].toArray();
//        vector2d.setX(jsonArray.at(0).toDouble());
//        vector2d.setX(jsonArray.at(1).toDouble());
//        setSpeed(vector2d);

//        jsonArray = qJsonObject["acceleration"].toArray();
//        vector2d.setX(jsonArray.at(0).toDouble());
//        vector2d.setX(jsonArray.at(1).toDouble());
//        setAcceleration(vector2d);
//    }
}
