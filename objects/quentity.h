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
    bool mutex;
    QVector2D position;
    QVector2D speed;
    QVector2D acceleration;

public:
    QuEntity();
    QuEntity(int instance_id);

    virtual int getClassId()    = 0;
    int getInstanceId();

    inline QVector2D getPosition() const {return position;};
    inline void setPosition(QVector2D position ) {this->position = position;};

    inline QVector2D getSpeed() const {return speed;};
    inline void setSpeed(QVector2D speed ) {this->speed = speed;};

    inline QVector2D getAcceleration() const {return acceleration;};
    inline void setAcceleration(QVector2D acceleration ) {this->acceleration = acceleration;};

public:
    static const int PLAYABLE_CHARACTER_ID=1;
    static const int UNPLAYABLE_CHARACTER_ID=2;
public:
    bool getMutex()
    {
        if(mutex)
            return false;
        mutex=true;
        return true;
    }
    void releaseMutex(){
        mutex=false;
    }
};

#endif // QUENTITY_H
