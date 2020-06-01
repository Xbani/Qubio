#include "quplayablecharacter.h"
#include "physicsconst.h"
#include "windows.h"

#include "qucharacter.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGuiApplication>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <iostream>
#include <QtMath>

QuPlayableCharacter::QuPlayableCharacter()
{

}

QuPlayableCharacter::QuPlayableCharacter(int instance_id):QuCharacter(instance_id)
{

}

void QuPlayableCharacter::move()
{
    //TODO ( KEYCHECK AND UPDATE ACCELERATION INSTEAD)
}

int QuPlayableCharacter::getClassId()
{
    return QuEntity::PLAYABLE_CHARACTER_ID;
}

void QuPlayableCharacter::advance(int step)
{
    if (!step)
        return;

    /* #############################################################
     * ----------------MOVEMENTS BUTTON EVENTS----------------------
     * #############################################################
     */

    if(GetKeyState(VK_LEFT) & 0x8000 && !(GetKeyState(VK_RIGHT) & 0x8000))
    {
        if (getAnimationState() == MOVE_RIGHT or getAnimationState() == JUMP_RIGHT)
        {
            setAcceleration({0,PhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() - PhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(PhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_LEFT);
    }

    if(GetKeyState(VK_RIGHT) & 0x8000 && !(GetKeyState(VK_LEFT) & 0x8000))
    {
        if (getAnimationState() == MOVE_LEFT or getAnimationState() == JUMP_LEFT)
        {
            setAcceleration({0,PhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() + PhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(PhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_RIGHT);
    }

    if(GetKeyState(VK_UP) & 0x8000 && getPreviouslyOnGround())
    {
        setAccelerationY(getAcceleration().y() - PhysicsConst::ACC_JUMP);
        getAnimationState() == MOVE_RIGHT or getAnimationState() == STATIC_RIGHT ? setAnimationState(JUMP_RIGHT) : setAnimationState(JUMP_LEFT);
    }

    if(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000)
    {
        setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        setAcceleration({0,PhysicsConst::G_FORCE});
        getAnimationState() == MOVE_RIGHT and getPreviouslyOnGround() ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    }

    if (!(GetKeyState(VK_LEFT) & 0x8000)
            and !(GetKeyState(VK_RIGHT) & 0x8000)
            and !(GetKeyState(VK_UP) & 0x8000  && getPreviouslyOnGround())
            and !(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000))
    {
        setAcceleration({0,PhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/PhysicsConst::INERTIA);
        getPreviouslyOnGround() and getAnimationState() == JUMP_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
        getAnimationState() == MOVE_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
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
