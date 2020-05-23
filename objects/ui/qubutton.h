#ifndef QUBUTTON_H
#define QUBUTTON_H

#include <objects/quobject.h>



class QuButton : public QuObject
{
protected:
    QImage sprite;
    QImage sprite_hover;
    int texture_id;
    int texture_hover_id;
    bool mouse_is_hover;

public:
    QuButton();
    QuButton(int texture_id, int texture_hover_id);


public:
    static const int MAX_TEXTURE_ID=5;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    // QuObject interface
public:
    QJsonObject toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // QUBUTTON_H
