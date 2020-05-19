#ifndef QUSPAWNPLAYER_H
#define QUSPAWNPLAYER_H

#include <objects/qublock.h>


/**
 * @brief The QuSpawnBlock class
 * @details Class which be use to indicate a possible spawn location for a character
 */
class QuSpawnBlock : public QuBlock
{
public:
    QuSpawnBlock();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);
};

#endif // QUSPAWNPLAYER_H
