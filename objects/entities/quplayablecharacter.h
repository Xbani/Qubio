#ifndef QUPLAYABLECHARACTER_H
#define QUPLAYABLECHARACTER_H

#include "qucharacter.h"


/**
 * @brief The QuPlayableCharacter class
 * @details Class which is the player controlled by our client.
 */
class QuPlayableCharacter : public QuCharacter
{

private:
    bool key_up;
    bool key_right;
    bool key_down;
    bool key_left;

public:
    QuPlayableCharacter(int instance_id, int hue);

    // QuObject interface
public:


    // QuEntity interface
public:
    int getClassId() override;
    void advance(int step) override;
    void kill(bool is_out_of_bound);

    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // QUPLAYABLECHARACTER_H
