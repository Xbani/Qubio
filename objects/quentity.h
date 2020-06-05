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
    QVector2D speed;
    QVector2D acceleration;
    bool previouslyOnGround;
    bool mutex;

public:
    QuEntity();
    QuEntity(int instance_id);

    virtual int getClassId()    = 0;
    inline int getInstanceId()const {return instance_id;};

    inline bool getPreviouslyOnGround() const {return previouslyOnGround;}
    inline void setPreviouslyOnGround(bool value) {previouslyOnGround = value;}


    inline QVector2D getSpeed() const {return speed;}
    inline void setSpeed(QVector2D speed) {this->speed = speed;}
    inline void setSpeedX(float value) {speed.setX(value);}
    inline void setSpeedY(float value) {speed.setY(value);}

    inline  QVector2D getAcceleration() const {return acceleration;}
    inline void setAcceleration(QVector2D acceleration) {this->acceleration = acceleration;}
    inline void setAccelerationX(float value) {acceleration.setX(value);}
    inline void setAccelerationY(float value) {acceleration.setY(value);}

public:
    static const int PLAYABLE_CHARACTER_ID=1;
    static const int UNPLAYABLE_CHARACTER_ID=2;
    static const int CROWN_ID=3;
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
