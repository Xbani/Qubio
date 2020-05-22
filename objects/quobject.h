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
public:
    static const int PIXEL_SIZE=8;
    static const int PIXEL_PER_CELL=8;
    static const int CELL_SIZE=PIXEL_SIZE*PIXEL_PER_CELL;
};

#endif // QUOBJECT_H
