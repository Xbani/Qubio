#include "quentity.h"

QuEntity::QuEntity()
{

}

QuEntity::QuEntity(int instance_id)
{
    this->instance_id=instance_id;
}

int QuEntity::getInstanceId()
{
    return instance_id;
}

QVector2D QuEntity::getAcceleration()
{
    return acceleration;
}

void QuEntity::setAcceleration(QVector2D acceleration)
{
    this->acceleration=acceleration;
}
