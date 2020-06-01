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
public:
    QuCharacter();
    QuCharacter(int instance_id);
    void step();

    // QGraphicsItem interface
public:

    inline int getAnimationState() const {return animation_state;}
    inline void setAnimationState(int animation_state) {this->animation_state = animation_state;}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    void advance(int step) override;

    QJsonObject toJSON() override;
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
