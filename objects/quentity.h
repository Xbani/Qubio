#ifndef QUENTITY_H
#define QUENTITY_H

#include <objects/quobject.h>

#include <QVector2D>


/**
 * @brief The QuEntity class
 * @details Abstract class which represent a game entity
 */
class QuEntity : public QuObject
{
private:
    int instance_id;
    int class_id;
    QVector2D position;
    QVector2D speed;
    QVector2D acceleration;

public:
    QuEntity();

    virtual int getClassId()    = 0;
    virtual int getInstanceId() = 0;

public:
    static const int PLAYABLE_CHARACTER_ID=1;
    static const int UNPLAYABLE_CHARACTER_ID=2;
};

#endif // QUENTITY_H
