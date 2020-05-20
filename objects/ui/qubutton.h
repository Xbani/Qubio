#ifndef QUBUTTON_H
#define QUBUTTON_H

#include <objects/quobject.h>



class QuButton : public QuObject
{
private:
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
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);
};

#endif // QUBUTTON_H
