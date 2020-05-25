#include "qucharacter.h"
#include "physicsconst.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGuiApplication>
#include "windows.h"
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <iostream>
#include <QtMath>

#include <QJsonArray>
#include <QJsonObject>

QuCharacter::QuCharacter()
{
    setAcceleration({0,PhysicsConst::G_FORCE});
}

QuCharacter::QuCharacter(int instance_id):QuEntity(instance_id)
{

}

QRectF QuCharacter::boundingRect() const
{
    return QRect(0,16,64,56);
}

void QuCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),QImage(":/resources/sprites/character/perso.png"),QRectF(0,2,8,6));
}

QPainterPath QuCharacter::shape() const
{
    QPainterPath path;
    path.addRect(0,16,64,56);
    return path;
}

void QuCharacter::advance(int step)
{
    if (!step)
        return;

    /* #############################################################
     * ----------------MOVEMENTS BUTTON EVENTS----------------------
     * #############################################################
     */

    if(GetKeyState(VK_LEFT) & 0x8000 && !(GetKeyState(VK_RIGHT) & 0x8000))
    {
        if (animation_state == MOVE_RIGHT or animation_state == JUMP_RIGHT)
        {
            setAcceleration({0,PhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() - PhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(PhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) animation_state = MOVE_LEFT;
    }

    if(GetKeyState(VK_RIGHT) & 0x8000 && !(GetKeyState(VK_LEFT) & 0x8000))
    {
        if (animation_state == MOVE_LEFT or animation_state == JUMP_LEFT)
        {
            setAcceleration({0,PhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() + PhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(PhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) animation_state = MOVE_RIGHT;
    }

    if(GetKeyState(VK_UP) & 0x8000 && getPreviouslyOnGround())
    {
        setAccelerationY(getAcceleration().y() - PhysicsConst::ACC_JUMP);
        animation_state == MOVE_RIGHT or animation_state == STATIC_RIGHT ? animation_state = JUMP_RIGHT : animation_state = JUMP_LEFT;
    }

    if(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000)
    {
        setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        setAcceleration({0,PhysicsConst::G_FORCE});
        animation_state == MOVE_RIGHT and getPreviouslyOnGround() ? animation_state = STATIC_RIGHT : animation_state = STATIC_LEFT;
    }

    if (!(GetKeyState(VK_LEFT) & 0x8000)
            and !(GetKeyState(VK_RIGHT) & 0x8000)
            and !(GetKeyState(VK_UP) & 0x8000  && getPreviouslyOnGround())
            and !(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000))
    {
        setAcceleration({0,PhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        getPreviouslyOnGround() and animation_state == JUMP_RIGHT ? animation_state = STATIC_RIGHT : animation_state == STATIC_LEFT;
        animation_state == MOVE_RIGHT ? animation_state = STATIC_RIGHT : animation_state = STATIC_LEFT;
    };

    /* ###################################################################################
     * ----------------------------------COLLISION----------------------------------------
     * ###################################################################################
     */

    QList <QGraphicsItem*> listCollision = scene()->collidingItems(this);

    //if there are no collision
    if (listCollision.isEmpty())
    {
        //we check if new latteral speed is higher than MAX_VITESSE_LATERAL
        QVector2D newSpeed = {getSpeed().x()+getAcceleration().x()/60l, getSpeed().y()+getAcceleration().y()/60l};
        if (qAbs(newSpeed.x()) > PhysicsConst::MAX_VITESSE_LATERAL)
        {
            (newSpeed.x() < 0) ? setSpeedX(-PhysicsConst::MAX_VITESSE_LATERAL) : setSpeedX(PhysicsConst::MAX_VITESSE_LATERAL);
        } else {
            setSpeedX(newSpeed.x());
        }
        if (qAbs(newSpeed.y()) > PhysicsConst::MAX_VITESSE_VERTICAL)
        {
            (newSpeed.y() < 0) ? setSpeedY(-PhysicsConst::MAX_VITESSE_VERTICAL) : setSpeedY(PhysicsConst::MAX_VITESSE_VERTICAL);
        } else {
            setSpeedY(newSpeed.y());
        }

        //update speed, position, previousPosition and previouslyOnGround
        setPreviousPosition(pos());
        setPos(x()+getSpeed().x()/60l*64, y()+getSpeed().y()/60l*64);
        setPreviouslyOnGround(false);
    }

    //if collision
    else
    {
        //two kind of collision
        bool collisionLeftOrRight = false;
        bool collisionTop = false;
        bool collisionBottom = false;
        //loop for all object colliding with the character, stop at the end of the list or if the two kind of collision appeared
        for (int i = 0; i<listCollision.size() and !(collisionLeftOrRight and collisionTop and collisionBottom); i++) {

            QVector2D centerToCenter = {float(pos().x() - listCollision[i]->pos().x()), float(pos().y() - listCollision[i]->pos().y())};

            qreal angleWithAbscisse = qAtan2(centerToCenter.x(), centerToCenter.y()) - qAtan2(1,0);
            qreal sinAngle = qSin(angleWithAbscisse);
            qreal cosAngle = qCos(angleWithAbscisse);

            //three scenarios

            //collision from the bottom
            if (sinAngle >= PhysicsConst::APPROX_COS_PI_4)
            {
                collisionBottom = true;
                setPreviouslyOnGround(true);
            }

            //collision from the top
            if (sinAngle <= -PhysicsConst::APPROX_COS_PI_4)
            {
                collisionTop = true;
            }

            //collision from the left or the right
            if (cosAngle <= -PhysicsConst::APPROX_COS_PI_4 or cosAngle >= PhysicsConst::APPROX_COS_PI_4)
            {
                collisionLeftOrRight = true;
            }
        }

        //update speed and position
        if (collisionTop or collisionBottom)
        {
            //we check if new latteral speedx is higher than MAX_VITESSE_LATERAL
            QVector2D newSpeed = {getSpeed().x()+getAcceleration().x()/60l, getSpeed().y()+getAcceleration().y()/60l};
            if (qAbs(newSpeed.x()) > PhysicsConst::MAX_VITESSE_LATERAL)
            {
                (newSpeed.x() < 0) ? setSpeedX(-PhysicsConst::MAX_VITESSE_LATERAL) : setSpeedX(PhysicsConst::MAX_VITESSE_LATERAL);
            } else {
                setSpeedX(newSpeed.x());
            }

            //update speed, position, previousPosition and previouslyOnGround
            setSpeedX(getSpeed().x()+getAcceleration().x()/60l);
            setSpeedY(0);
            setPos(x()+getSpeed().x()/60l*64, getPreviousPosition().y());
        }

        else if (collisionLeftOrRight)
        {
            setSpeedX(0);
            setSpeedY(getSpeed().y()+getAcceleration().y()/60l);
            setPos(getPreviousPosition().x(), y()+getSpeed().y()/60l*64);
        }

        else //(collisionLeftOrRight and collisionTopOrBottom)
        {
            setSpeedX(0);
            setSpeedY(0);
            setPos(getPreviousPosition());
        }
    }
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
