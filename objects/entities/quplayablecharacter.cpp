#include "quplayablecharacter.h"
#include "quphysicsconst.h"
#include "quunplayablecharacter.h"
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
#include <QJsonObject>
#include <QJsonArray>
#include <rooms/qugame.h>
#include <objects/blocks/quspawnblock.h>
#include <objects/entities/qucrown.h>
#include <network/client/quclient.h>


QuPlayableCharacter::QuPlayableCharacter(int instance_id, int hue):QuCharacter(instance_id,hue)
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

    //buttons change acceleration only
    if(!hasFocus())
    {
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
        !(getPreviouslyOnGround()) ? setAnimationState(JUMP_LEFT) : setAnimationState(MOVE_LEFT);
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
        !(getPreviouslyOnGround()) ? setAnimationState(JUMP_RIGHT) : setAnimationState(MOVE_RIGHT);
    }

    if(key_up && getPreviouslyOnGround())
    {
        setAccelerationY(- QuPhysicsConst::ACC_JUMP);
        getAnimationState() == MOVE_RIGHT or getAnimationState() == STATIC_RIGHT ? setAnimationState(JUMP_RIGHT) : setAnimationState(JUMP_LEFT);
    }

    if(key_left && key_right)
    {
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);
        getAnimationState() == MOVE_RIGHT and getPreviouslyOnGround() ? setAnimationState(STATIC_RIGHT) : setAnimationState(STATIC_LEFT);
    }

    if (    !key_left
        and !key_right
        and !(key_up && getPreviouslyOnGround())
        and !(key_left && key_right))
    {
        setAcceleration({0,QuPhysicsConst::G_FORCE});
        setSpeedX(getSpeed().x()/QuPhysicsConst::INERTIA);

        if (getPreviouslyOnGround() and getAnimationState() == JUMP_RIGHT) setAnimationState(STATIC_RIGHT);
        else if (getPreviouslyOnGround() and getAnimationState() == JUMP_LEFT) setAnimationState(STATIC_LEFT);

        if (getAnimationState() == MOVE_RIGHT) setAnimationState(STATIC_RIGHT);
        else if (getAnimationState() == MOVE_LEFT) setAnimationState(STATIC_LEFT);
    }

//    if(!getPreviouslyOnGround())
//    {
//        getAnimationState() == JUMP_LEFT || getAnimationState() == MOVE_LEFT || getAnimationState() == STATIC_LEFT ? setAnimationState(JUMP_LEFT):setAnimationState(JUMP_RIGHT);
//    }

    //update speed and pos
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

    //if out of room
    QRectF sRect=scene()->sceneRect();
    if(x()-boundingRect().x()+boundingRect().width()  < sRect.x()
    || y()-boundingRect().y()+boundingRect().height() < sRect.y()
    || x()>sRect.x()+sRect.width()
    || y() > sRect.y() + sRect.height()){
        kill(true);
    }
    //collisions
    QuObject * topCollidingObject;
    QuObject * bottomCollidingObject;
    QuObject * leftCollidingObject;
    QuObject * rightCollidingObject;

    QList <QGraphicsItem*> listCollision = scene()->collidingItems(this);

    //if there are no collision
    if (listCollision.isEmpty() || listCollision.size()==1 && getCrown()!=nullptr && listCollision.contains(getCrown()))
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

        bool isCollidingWithCrown=false;
        QuCrown * collidingCrown=nullptr;

        for (int i = 0; i<listCollision.size() and !(collisionTop and collisionBottom and collisionLeft and collisionRight); i++) {

            // vector between gravity centers of the two colliding object
            QVector2D centerToCenter = {float((pos().x() + boundingRect().width()/2) - (listCollision[i]->pos().x() + listCollision[i]->boundingRect().width()/2)),
                                        float((pos().y() + boundingRect().height()/2) - (listCollision[i]->pos().y() + listCollision[i]->boundingRect().height()/2))};

            qreal angleWithAbscisse = qAtan2(centerToCenter.x(), centerToCenter.y()) - qAtan2(1,0);
            qreal sinAngle = qSin(angleWithAbscisse);
            qreal cosAngle = qCos(angleWithAbscisse);

            // four scenarios
            // collision from the top
            if (sinAngle < -QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionTop = true;
                topCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]);
                if(topCollidingObject==nullptr){
                    topCollidingObject=dynamic_cast<QuUnplayableCharacter *>(listCollision[i]);
                }
                if(topCollidingObject==nullptr){
                    collidingCrown=dynamic_cast<QuCrown *>(listCollision[i]);
                    isCollidingWithCrown=true;
                    collisionTop = false;
                    topCollidingObject=collidingCrown;
                }
            }

            // collision from the bottom
            if (sinAngle > QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionBottom = true;
                setPreviouslyOnGround(true);
                bottomCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
                if(bottomCollidingObject==nullptr){
                    bottomCollidingObject=dynamic_cast<QuUnplayableCharacter *>(listCollision[i]);
                }
                if(bottomCollidingObject==nullptr){
                    collidingCrown=dynamic_cast<QuCrown *>(listCollision[i]);
                    isCollidingWithCrown=true;
                    collisionBottom = false;
                    bottomCollidingObject=collidingCrown;
                }
            }

            // collision from the left
            if (cosAngle > QuPhysicsConst::APPROX_COS_PI_4*1.001)
            {
                collisionLeft = true;
                leftCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
                if(leftCollidingObject==nullptr){
                    leftCollidingObject=dynamic_cast<QuUnplayableCharacter *>(listCollision[i]);
                }
                if(leftCollidingObject==nullptr){
                    collidingCrown=dynamic_cast<QuCrown *>(listCollision[i]);
                    isCollidingWithCrown=true;
                    collisionLeft = false;
                    leftCollidingObject=collidingCrown;
                }
            }

            // collision from the right
            if (cosAngle < -QuPhysicsConst::APPROX_COS_PI_4*1.001)
            {
                collisionRight = true;
                rightCollidingObject=dynamic_cast<QuSolidBlock *>(listCollision[i]) ;
                if(rightCollidingObject==nullptr){
                    rightCollidingObject=dynamic_cast<QuUnplayableCharacter *>(listCollision[i]);
                }
                if(rightCollidingObject==nullptr){
                    collidingCrown=dynamic_cast<QuCrown *>(listCollision[i]);
                    isCollidingWithCrown=true;
                    collisionRight = false;
                    rightCollidingObject=collidingCrown;
                }
            }
        }
        if(isCollidingWithCrown && getCrown()==nullptr){
            collidingCrown->setOwner(this);
            setCrown(collidingCrown);
        }
        //update speed and position

        if ((collisionTop or collisionBottom ))
        {
            setSpeedY(0);
            collisionTop ? setY(topCollidingObject->y() + topCollidingObject->boundingRect().y() + topCollidingObject->boundingRect().height() + QuPhysicsConst::QUANTUM) : setY(bottomCollidingObject->y()+ bottomCollidingObject->boundingRect().y() - boundingRect().height() - QuPhysicsConst::QUANTUM);
            if(collisionTop && dynamic_cast<QuUnplayableCharacter *>(topCollidingObject)!=nullptr ){
                kill(false);
            }
        }

        if (collisionLeft or collisionRight)
        {
            setSpeedX(0);
            collisionLeft ? setX(leftCollidingObject->x() + leftCollidingObject->boundingRect().x()+ leftCollidingObject->boundingRect().width() + QuPhysicsConst::QUANTUM) : setX(rightCollidingObject->x()+ rightCollidingObject->boundingRect().x() - boundingRect().width() - QuPhysicsConst::QUANTUM);
        }
    }

    QuGame *quGame = dynamic_cast<QuGame *>(scene());
    quGame->sentToServer(toJSON());
    if (getCrown()!=nullptr)
        quGame->sentToServer(getCrown()->toJSON());
}

void QuPlayableCharacter::kill(bool is_out_of_bound)
{
    QuGame *quGame = dynamic_cast<QuGame *>(scene());

    QJsonObject *jsonDeathCharacter = new QJsonObject();
    QJsonArray jsonArrayDeathPosition;

    (*jsonDeathCharacter)["instanceId"] = getInstanceId();
    (*jsonDeathCharacter)["wasCrowned"] = (getCrown()!=nullptr);
    (*jsonDeathCharacter)["outOfBound"] = is_out_of_bound;

    jsonArrayDeathPosition.append(pos().x());
    jsonArrayDeathPosition.append(pos().y());
    (*jsonDeathCharacter)["deathPosition"] = jsonArrayDeathPosition;
    quGame->getQuClient()->sentDeath(jsonDeathCharacter);
    setPos(getSpawnBlock()->getPos());
    if(getCrown()!=nullptr){
        getCrown()->setOwner(nullptr);
        //quGame->sentToServer(getCrown()->toJSON());
        setCrown(nullptr); 
    }
}

void QuPlayableCharacter::keyPressEvent(QKeyEvent *event)
{
    // Call functions on your character here.
       switch (event->key())
       {
       case Qt::Key_Right:
           key_right=true;
           break;
       case Qt::Key_Left:
           key_left=true;
           break;
       case Qt::Key_Up:
           key_up=true;
           break;
       case Qt::Key_Down:
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
           key_right=false;
           break;
       case Qt::Key_Left:
           key_left=false;
           break;
       case Qt::Key_Up:
           key_up=false;
           break;
       case Qt::Key_Down:
           key_down=false;
           break;
       }
}
