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
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QuObject interface
public:
    QJsonObject* toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;
};

#endif // QUSPAWNPLAYER_H
