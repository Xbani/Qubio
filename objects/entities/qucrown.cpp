#include "qucrown.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QPainter>
#include <QDebug>

#include <rooms/qugame.h>

QuCrown::QuCrown(int instenceId):QuEntity(instenceId)
{
    sprite_crown = QImage(":/resources/sprites/character/crown.png");
    character=nullptr;
}

QRectF QuCrown::boundingRect() const
{
    return QRectF(0,-4*QuObject::PIXEL_SIZE,QuObject::PIXEL_SIZE*6,QuObject::PIXEL_SIZE*4);
}

void QuCrown::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(getOwner()!=nullptr){
        QRectF rect=boundingRect();
        rect.moveTo(getOwner()->boundingRect().topRight());
        painter->drawImage(boundingRect(), sprite_crown,QRectF(0,0,6,4));
    }
    else
        painter->drawImage(boundingRect(), sprite_crown,QRectF(0,0,6,4));
}

QJsonObject *QuCrown::toJSON()
{
    QJsonObject *jsonCrown = new QJsonObject();
    QJsonArray jsonArrayPosition;
    QJsonArray jsonArrayspeed;
    QJsonArray jsonArrayAcceleration;

    (*jsonCrown)["instanceId"] = getInstanceId();
    (*jsonCrown)["classId"] = getClassId();


    jsonArrayPosition.append(pos().x());
    jsonArrayPosition.append(pos().y());
    (*jsonCrown)["position"] = jsonArrayPosition;

    jsonArrayspeed.append(getSpeed().x());
    jsonArrayspeed.append(getSpeed().y());
    (*jsonCrown)["speed"] = jsonArrayspeed;

    jsonArrayAcceleration.append(getAcceleration().x());
    jsonArrayAcceleration.append(getAcceleration().y());
    (*jsonCrown)["acceleration"] = jsonArrayAcceleration;

    (*jsonCrown)["owner"] = character != nullptr ? character->getInstanceId() : -1;

    return jsonCrown;
}

void QuCrown::fromJSON(QJsonObject &qJsonObject)
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

        QuGame *quGame =dynamic_cast<QuGame*>(scene());
        if (quGame){
            character = dynamic_cast<QuCharacter*>(quGame->getEntities().take((qJsonObject)["owner"].toInt()));
            if (character != nullptr){
                character->setCrown(this);
            }
        }
    }
}

int QuCrown::getClassId()
{
    return QuEntity::CROWN_ID;
}

void QuCrown::advance(int phase)
{
    if(!phase){
        return;
    }
    if(getOwner()!=nullptr){
        setX(getOwner()->x());
        setY(getOwner()->y());
    }
}
