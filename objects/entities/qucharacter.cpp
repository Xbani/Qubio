#include "qucharacter.h"

#include <QJsonArray>
#include <QJsonObject>

QuCharacter::QuCharacter()
{

}
QuCharacter::QuCharacter(int instance_id):QuEntity(instance_id)
{

}
void QuCharacter::step()
{
    //TODO
}

QRectF QuCharacter::boundingRect() const
{
    return QRectF(0,0,0*QuObject::PIXEL_SIZE,0*QuObject::PIXEL_SIZE);//TODO
}

void QuCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QJsonObject QuCharacter::toJSON()
{
    QJsonObject jsonCharacter;
    QJsonArray jsonArrayPosition;
    QJsonArray jsonArrayspeed;
    QJsonArray jsonArrayAcceleration;

    jsonCharacter["instanceId"] = getInstanceId();
    jsonCharacter["classId"] = getClassId();

    jsonArrayPosition.append(getPosition().x());
    jsonArrayPosition.append(getPosition().y());
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
        QVector2D vector2d;
        vector2d.setX(jsonArray.at(0).toDouble());
        vector2d.setX(jsonArray.at(1).toDouble());
        setPosition(vector2d);

        jsonArray = qJsonObject["speed"].toArray();
        vector2d.setX(jsonArray.at(0).toDouble());
        vector2d.setX(jsonArray.at(1).toDouble());
        setSpeed(vector2d);

        jsonArray = qJsonObject["acceleration"].toArray();
        vector2d.setX(jsonArray.at(0).toDouble());
        vector2d.setX(jsonArray.at(1).toDouble());
        setAcceleration(vector2d);
    }
}
