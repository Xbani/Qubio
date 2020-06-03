#ifndef QUPLAYERINFO_H
#define QUPLAYERINFO_H

#include <objects/quobject.h>



class QuPlayerInfo : public QuObject
{
private:
    QImage sprite;
    QImage sprite_player;
    int player_hue;
    QString player_name;
    int player_id;


public:
    QuPlayerInfo(int player_id, QString player_name, int hue);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    inline int getPlayerId() const {return player_id;};
    inline int getPlayerHue() const {return player_hue;};
    inline QString getPlayerName() const {return player_name;};
    // QuObject interface
public:
    QJsonObject* toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;
};

#endif // QUPLAYERINFO_H
