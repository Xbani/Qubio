#include "quplayablecharacter.h"
#include "quphysicsconst.h"
#include "objects/blocks/qusolidblock.h"

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
#include <QKeyEvent>


QuPlayableCharacter::QuPlayableCharacter(int instance_id):QuCharacter(instance_id)
{
    setFlags(ItemIsFocusable);
    setFocus();
    key_up=0;
    key_right=0;
    key_down=0;
    key_left=0;
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
    if(!hasFocus()){
        setFocus();
    }
    if(key_left && !key_right)
    {
        if (getAnimationState() == MOVE_RIGHT or getAnimationState() == JUMP_RIGHT)
        {
            setAcceleration({0,QuPhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        }
        setAccelerationX(-QuPhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(QuPhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_LEFT);
    }

    if(key_right && !key_left)
    {
        if (getAnimationState() == MOVE_LEFT or getAnimationState() == JUMP_LEFT)
        {
            setAcceleration({0,QuPhysicsConst::G_FORCE});
            setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        }
        setAccelerationX(QuPhysicsConst::ACC_LATERAL_MOUVEMENT);
        setAccelerationY(QuPhysicsConst::G_FORCE);
        if (getPreviouslyOnGround()) setAnimationState(MOVE_RIGHT);
    }

    if(key_up && getPreviouslyOnGround())
    {
        setAccelerationY(- QuPhysicsConst::ACC_JUMP);
        getAnimationState() == MOVE_RIGHT or getAnimationState() == STATIC_RIGHT ? setAnimationState(JUMP_RIGHT) : setAnimationState(JUMP_LEFT);
    }

    if(key_left && key_right)
    {
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        getAnimationState() == MOVE_RIGHT and getPreviouslyOnGround() ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    }

    if (!key_left
            and !key_right
            and !(key_up && getPreviouslyOnGround())
            and !(key_left && key_right))
    {
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        getPreviouslyOnGround() and getAnimationState() == JUMP_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
        getAnimationState() == MOVE_RIGHT ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    };

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


    setPos(x()+getSpeed().x()/60l*64, y()+getSpeed().y()/60l*64);
    /* ###################################################################################
     * ----------------------------------COLLISION----------------------------------------
     * ###################################################################################
     */


    QuSolidBlock * topCollidingObject;
    QuSolidBlock * bottomCollidingObject;
    QuSolidBlock * leftCollidingObject;
    QuSolidBlock * rightCollidingObject;

    QList <QGraphicsItem*> listCollision = scene()->collidingItems(this);

    //if there are no collision
    if (listCollision.isEmpty())
    {
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
                topCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
            }

            // collision from the bottom
            if (sinAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionBottom = true;
                setPreviouslyOnGround(true);
                bottomCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
            }

            // collision from the left
            if (cosAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionLeft = true;
                leftCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
            }

            // collision from the right
            if (cosAngle <= -QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionRight = true;
                rightCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
            }
        }

        //update speed and position

        if ((collisionTop or collisionBottom ))
        {
            setSpeedY(0);
            collisionTop ? setY(topCollidingObject->y() + topCollidingObject->boundingRect().height() + QuPhysicsConst::QUANTUM) : setY(bottomCollidingObject->y() - boundingRect().height() - QuPhysicsConst::QUANTUM);
        }

        if (collisionLeft or collisionRight)
        {
            setSpeedX(0);
            collisionLeft ? setX(leftCollidingObject->x() + leftCollidingObject->boundingRect().width() + QuPhysicsConst::QUANTUM) : setX(rightCollidingObject->x() - boundingRect().width() - QuPhysicsConst::QUANTUM);
        }
    }
}

void QuPlayableCharacter::keyPressEvent(QKeyEvent *event)
{
    // Call functions on your character here.
       switch (event->key())
       {
       case Qt::Key_Right:
           //playableCharacter.moveLeft(); // For example
           key_right=true;
           break;
       case Qt::Key_Left:
           //playableCharacter.moveRight(); // For example
           key_left=true;
           break;
       case Qt::Key_Up:
           //playableCharacter.moveRight(); // For example
           key_up=true;
           break;
       case Qt::Key_Down:
           //playableCharacter.moveRight(); // For example
           key_down=true;
           break;
       }
}

void QuPlayableCharacter::keyReleaseEvent(QKeyEvent *event)
{
    // Call functions on your character here.
       switch (event->key())
       {
       case Qt::Key_Right:
           //playableCharacter.moveLeft(); // For example
           key_right=false;
           break;
       case Qt::Key_Left:
           //playableCharacter.moveRight(); // For example
           key_left=false;
           break;
       case Qt::Key_Up:
           //playableCharacter.moveRight(); // For example
           key_up=false;
           break;
       case Qt::Key_Down:
           //playableCharacter.moveRight(); // For example
           key_down=false;
           break;
       }
}
