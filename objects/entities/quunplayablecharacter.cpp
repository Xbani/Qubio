#include "quunplayablecharacter.h"

#include <QJsonObject>

QuUnplayableCharacter::QuUnplayableCharacter()
{

}

QuUnplayableCharacter::QuUnplayableCharacter(int instance_id):QuCharacter(instance_id)
{

}

int QuUnplayableCharacter::getClassId()
{
    return QuEntity::UNPLAYABLE_CHARACTER_ID;
}
