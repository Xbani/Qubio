#ifndef QUCHARACTER_H
#define QUCHARACTER_H

#include <objects/quentity.h>


/**
 * @brief The QuCharacter class
 * @details Class which correspond to in game character.
 */
class QuCharacter : public QuEntity
{
private:
    QString name;
    QColor color;
    int animation_state;

    QImage sprite_static_left;
    QImage sprite_static_right;
    QImage sprite_move_left;
    QImage strite_move_right;
    QImage sprite_jump_left;
    QImage sprite_jump_right;

public:
    QuCharacter(int instance_id);
    QuCharacter(int instance_id,int hue);
    void step();

    // QGraphicsItem interface
public:

    inline int getAnimationState() const {return animation_state;}
    inline void setAnimationState(int animation_state) {this->animation_state = animation_state;}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    QJsonObject* toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;

public:
    static const int STATIC_RIGHT =  1;
    static const int  STATIC_LEFT = -1;
    static const int   MOVE_RIGHT =  2;
    static const int    MOVE_LEFT = -2;
    static const int   JUMP_RIGHT =  3;
    static const int    JUMP_LEFT = -3;
};

#endif // QUCHARACTER_H
