#include "quplayablecharacter.h"

#include <QJsonArray>
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

int QuPlayableCharacter::getClassId()
{
    return QuEntity::PLAYABLE_CHARACTER_ID;
}
