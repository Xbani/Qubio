#ifndef QUCROWN_H
#define QUCROWN_H

#include "qucharacter.h"

#include <objects/quentity.h>


class QuCharacter;
class QuCrown : public QuEntity
{
public:
    QuCrown();

private:
    QImage sprite_crown;
    QuCharacter * character;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setOwner(QuCharacter * character){this->character=character;};
    QuCharacter * getOwner(){return character;};

    // QuObject interface
public:
    QJsonObject *toJSON();
    void fromJSON(QJsonObject &qJsonObject);

    // QuEntity interface
public:
    int getClassId();

    // QGraphicsItem interface
public:
    void advance(int phase);
};

#endif // QUCROWN_H
