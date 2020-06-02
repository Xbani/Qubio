#include "quplayablecharacter.h"
#include "quphysicsconst.h"
#include "objects/blocks/qusolidblock.h"
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

void QuPlayableCharacter::moveRight()
{

}

void QuPlayableCharacter::moveLeft()
{

}

void QuPlayableCharacter::moveJump()
{

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
            setAcceleration({0,QuPhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() - QuPhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(QuPhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_LEFT);
    }

    if(GetKeyState(VK_RIGHT) & 0x8000 && !(GetKeyState(VK_LEFT) & 0x8000))
    {
        if (getAnimationState() == MOVE_LEFT or getAnimationState() == JUMP_LEFT)
        {
            setAcceleration({0,QuPhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        }
        setAccelerationX(getAcceleration().x() + QuPhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(QuPhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_RIGHT);
    }

    if(GetKeyState(VK_UP) & 0x8000 && getPreviouslyOnGround())
    {
        setAccelerationY(getAcceleration().y() - QuPhysicsConst::ACC_JUMP);
        getAnimationState() == MOVE_RIGHT or getAnimationState() == STATIC_RIGHT ? setAnimationState(JUMP_RIGHT) : setAnimationState(JUMP_LEFT);
    }

    if(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000)
    {
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        getAnimationState() == MOVE_RIGHT and getPreviouslyOnGround() ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    }

    if (!(GetKeyState(VK_LEFT) & 0x8000)
            and !(GetKeyState(VK_RIGHT) & 0x8000)
            and !(GetKeyState(VK_UP) & 0x8000  && getPreviouslyOnGround())
            and !(GetKeyState(VK_LEFT) & 0x8000 && GetKeyState(VK_RIGHT) & 0x8000))
    {
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        getPreviouslyOnGround() and getAnimationState() == JUMP_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
        getAnimationState() == MOVE_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    };

    /* ###################################################################################
     * ----------------------------------COLLISION----------------------------------------
     * ###################################################################################
     */


    QuSolidBlock topCollidingObject;
    QuSolidBlock bottomCollidingObject;
    QuSolidBlock leftCollidingObject;
    QuSolidBlock rightCollidingObject;

    QList <QGraphicsItem*> listCollision = scene()->collidingItems(this);

    //if there are no collision
    if (listCollision.isEmpty())
    {
        //we check if new latteral speed is higher than MAX_VITESSE_LATERAL
        QVector2D newSpeed = {getSpeed().x()+getAcceleration().x()/60l, getSpeed().y()+getAcceleration().y()/60l};
        if (qAbs(newSpeed.x()) > QuPhysicsConst::MAX_VITESSE_HORIZONTALE)
        {
            (newSpeed.x() < 0) ? setSpeedX(-QuPhysicsConst::MAX_VITESSE_HORIZONTALE) : setSpeedX(QuPhysicsConst::MAX_VITESSE_HORIZONTALE);
        } else {
            setSpeedX(newSpeed.x());
        }
        if (qAbs(newSpeed.y()) > QuPhysicsConst::MAX_VITESSE_VERTICALE)
        {
            (newSpeed.y() < 0) ? setSpeedY(-QuPhysicsConst::MAX_VITESSE_VERTICALE) : setSpeedY(QuPhysicsConst::MAX_VITESSE_VERTICALE);
        } else {
            setSpeedY(newSpeed.y());
        }

        //update speed, position, previousPosition and previouslyOnGround
        setPreviousPosition(pos());
        setPos(x()+getSpeed().x()/60l*64, y()+getSpeed().y()/60l*64);
        setPreviouslyOnGround(false);
    }

    //if collisions
    else
    {
        // two kind of collision
        bool collisionTop = false;
        bool collisionBottom = false;
        bool collisionLeft = false;
        bool collisionRight = false;

        //loop for all object colliding with the character, stop at the end of the list or if the two kind of collision appeared
        for (int i = 0; i<listCollision.size() and !(collisionTop and collisionBottom and collisionLeft and collisionRight); i++) {

            QVector2D centerToCenter = {float(pos().x() - listCollision[i]->pos().x()), float(pos().y() - listCollision[i]->pos().y())};

            qreal angleWithAbscisse = qAtan2(centerToCenter.x(), centerToCenter.y()) - qAtan2(1,0);
            qreal sinAngle = qSin(angleWithAbscisse);
            qreal cosAngle = qCos(angleWithAbscisse);

            // four scenarios

            // collision from the top
            if (sinAngle <= -QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionTop = true;
                topCollidingObject.setPos(listCollision[i]->x(), listCollision[i]->y());
            }

            // collision from the bottom
            if (sinAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionBottom = true;
                setPreviouslyOnGround(true);
                bottomCollidingObject.setPos(listCollision[i]->x(), listCollision[i]->y());
            }

            // collision from the left
            if (cosAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionLeft = true;
                leftCollidingObject.setPos(listCollision[i]->x(), listCollision[i]->y());
            }

            // collision from the right
            if (cosAngle <= -QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionRight = true;
                rightCollidingObject.setPos(listCollision[i]->x(), listCollision[i]->y());
            }
        }

        //update speed and position

        if (collisionTop or collisionBottom)
        {
            //we check if new latteral speedx is higher than MAX_VITESSE_LATERAL
            QVector2D newSpeed = {getSpeed().x()+getAcceleration().x()/60l, getSpeed().y()+getAcceleration().y()/60l};
            if (qAbs(newSpeed.x()) > QuPhysicsConst::MAX_VITESSE_HORIZONTALE)
            {
                (newSpeed.x() < 0) ? setSpeedX(-QuPhysicsConst::MAX_VITESSE_HORIZONTALE) : setSpeedX(QuPhysicsConst::MAX_VITESSE_HORIZONTALE);
            } else {
                setSpeedX(newSpeed.x());
            }

            //update speed, position, previousPosition
            setSpeedX(getSpeed().x()+getAcceleration().x()/60l);
            setSpeedY(0);

            //repositionning of the character : bottom of the object if collisionTop, top of the object if collisionBottom
            setX(x()+getSpeed().x()/60l*64);
            collisionTop ? setY(topCollidingObject.y() + topCollidingObject.boundingRect().height() + QuPhysicsConst::QUANTUM) : setY(bottomCollidingObject.y() - boundingRect().height() - QuPhysicsConst::QUANTUM);
        }

        else if (collisionLeft or collisionRight)
        {
            setSpeedX(0);
            setSpeedY(getSpeed().y()+getAcceleration().y()/60l);

            //repositionning of the character : left of the object if collisionRight, right of the object if collisionLeft
            setY(y()+getSpeed().y()/60l*64);
            collisionLeft ? setX(leftCollidingObject.x() + leftCollidingObject.boundingRect().width() + QuPhysicsConst::QUANTUM) : setX(rightCollidingObject.x() - boundingRect().width() - QuPhysicsConst::QUANTUM);
            qDebug() << "collisionLeftRight";
        }
        else if (collisionTop and collisionLeft)
        {
            setSpeedX(0);
            setSpeedY(0);
            setPos(leftCollidingObject.x() + leftCollidingObject.boundingRect().width() + QuPhysicsConst::QUANTUM, topCollidingObject.y() + topCollidingObject.boundingRect().height() + QuPhysicsConst::QUANTUM);
            qDebug() << "collisionTopLeft";
        }

        else if (collisionTop and collisionRight)
        {
            setSpeedX(0);
            setSpeedY(0);
            setPos(rightCollidingObject.x() - boundingRect().width() - QuPhysicsConst::QUANTUM, topCollidingObject.y() + topCollidingObject.boundingRect().height() + QuPhysicsConst::QUANTUM);
            qDebug() << "collisionTopRight";
        }

        else if (collisionBottom and collisionLeft)
        {
            setSpeedX(0);
            setSpeedY(0);
            setPos(leftCollidingObject.x() + leftCollidingObject.boundingRect().width() + QuPhysicsConst::QUANTUM, bottomCollidingObject.y() - boundingRect().height() - QuPhysicsConst::QUANTUM);
            qDebug() << "collisionBottomLeft";
        }

        else if (collisionBottom and collisionRight)
        {
            setSpeedX(0);
            setSpeedY(0);
            setPos(rightCollidingObject.x() - boundingRect().width() - QuPhysicsConst::QUANTUM, bottomCollidingObject.y() - boundingRect().height() - QuPhysicsConst::QUANTUM);
            qDebug() << "collisionBottomRight";
        }
    }
}
