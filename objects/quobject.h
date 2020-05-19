#ifndef QUOBJECT_H
#define QUOBJECT_H

#include <QGraphicsItem>


/**
 * @brief The QuObject class
 * @details Abstract class which represent a game object.
 */
class QuObject : public QGraphicsItem
{
public:
    QuObject();
    virtual QJsonObject toJSON()   = 0;
    virtual void fromJSON(QJsonObject qJsonObject) = 0;
};

#endif // QUOBJECT_H
