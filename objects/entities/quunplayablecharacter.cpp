#include "quunplayablecharacter.h"
#include "quphysicsconst.h"

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

#include <QJsonObject>


QuUnplayableCharacter::QuUnplayableCharacter(int instance_id):QuCharacter(instance_id)
{

}

int QuUnplayableCharacter::getClassId()
{
    return QuEntity::UNPLAYABLE_CHARACTER_ID;
}

void QuCharacter::advance(int step)
{
    if (!step)
        return;

    /* #############################################################
     * ----------------AI MOVEMENTS--------------------------------
     * #############################################################
     */


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
        if (qAbs(newSpeed.x()) > QuPhysicsConst::MAX_VITESSE_VERTICALE)
        {
            (newSpeed.x() < 0) ? setSpeedX(-QuPhysicsConst::MAX_VITESSE_VERTICALE) : setSpeedX(QuPhysicsConst::MAX_VITESSE_VERTICALE);
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
            if (sinAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionBottom = true;
                setPreviouslyOnGround(true);
            }

            //collision from the top
            if (sinAngle <= -QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionTop = true;
            }

            //collision from the left or the right
            if (cosAngle <= -QuPhysicsConst::APPROX_COS_PI_4 or cosAngle >= QuPhysicsConst::APPROX_COS_PI_4)
            {
                collisionLeftOrRight = true;
            }
        }

        //update speed and position
        if (collisionTop or collisionBottom)
        {
            //we check if new latteral speedx is higher than MAX_VITESSE_LATERAL
            QVector2D newSpeed = {getSpeed().x()+getAcceleration().x()/60l, getSpeed().y()+getAcceleration().y()/60l};
            if (qAbs(newSpeed.x()) > QuPhysicsConst::MAX_VITESSE_VERTICALE)
            {
                (newSpeed.x() < 0) ? setSpeedX(-QuPhysicsConst::MAX_VITESSE_VERTICALE) : setSpeedX(QuPhysicsConst::MAX_VITESSE_VERTICALE);
            } else {
                setSpeedX(newSpeed.x());
            }

            //update speed, position, previousPosition and previouslyOnGround
            setSpeedX(getSpeed().x()+getAcceleration().x()/60l);
            setSpeedY(0);
        }

        else if (collisionLeftOrRight)
        {
            setSpeedX(0);
            setSpeedY(getSpeed().y()+getAcceleration().y()/60l);
        }

        else //(collisionLeftOrRight and collisionTopOrBottom)
        {
            setSpeedX(0);
            setSpeedY(0);
        }
    }
}
