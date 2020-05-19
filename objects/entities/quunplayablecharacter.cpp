#include "quunplayablecharacter.h"

#include <QJsonObject>

QuUnplayableCharacter::QuUnplayableCharacter()
{

}

QuUnplayableCharacter::QuUnplayableCharacter(int instance_id)
{
    instance_id=instance_id;
}

QJsonObject QuUnplayableCharacter::toJSON()
{
    return QJsonObject();//TODO
}

void QuUnplayableCharacter::fromJSON(QJsonObject qJsonObject)
{
    //TODO
}

int QuUnplayableCharacter::getClassId()
{
    return QuEntity::UNPLAYABLE_CHARACTER_ID;
}
