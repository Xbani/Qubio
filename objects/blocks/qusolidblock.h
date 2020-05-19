#ifndef QUSOLIDBLOCK_H
#define QUSOLIDBLOCK_H

#include <objects/qublock.h>


/**
 * @brief The QuSolidBlock class
 * @details Class which represent a solid game block
 */
class QuSolidBlock : public QuBlock
{

public:
    QuSolidBlock();
    QuSolidBlock(int texture_block_id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);
};

#endif // QUSOLIDBLOCK_H
