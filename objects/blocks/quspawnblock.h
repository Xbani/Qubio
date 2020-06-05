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
    QPoint pos;
    int idPlayer;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QuObject interface
public:
    QJsonObject* toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;
    inline QPoint getPos()const{return pos;};
    inline void setPos(QPoint pos){this->pos = pos;};

    inline int getidPlayer()const{return idPlayer;};
    inline void setidPlayer(int idPlayer){this->idPlayer = idPlayer;};
};

#endif // QUSPAWNPLAYER_H
