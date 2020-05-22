#ifndef QUPLAYERINFO_H
#define QUPLAYERINFO_H

#include <objects/quobject.h>



class QuPlayerInfo : public QuObject
{
private:
    QImage sprite;
    QImage sprite_player;
    QColor player_color;
    QString player_name;


public:
    QuPlayerInfo();
    QuPlayerInfo(QString player_name, QColor player_color);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);
};

#endif // QUPLAYERINFO_H
