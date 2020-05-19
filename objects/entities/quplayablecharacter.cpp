#include "quplayablecharacter.h"

#include <QJsonObject>

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

QJsonObject QuPlayableCharacter::toJSON()
{
    return QJsonObject();//TODO
}

void QuPlayableCharacter::fromJSON(QJsonObject qJsonObject)
{
    //TODO
}

int QuPlayableCharacter::getClassId()
{
    return QuEntity::PLAYABLE_CHARACTER_ID;
}
