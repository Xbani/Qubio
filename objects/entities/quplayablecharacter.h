#ifndef QUPLAYABLECHARACTER_H
#define QUPLAYABLECHARACTER_H

#include "qucharacter.h"


/**
 * @brief The QuPlayableCharacter class
 * @details Class which is the player controlled by our client.
 */
class QuPlayableCharacter : public QuCharacter
{
public:
    QuPlayableCharacter();
    QuPlayableCharacter(int instance_id);
    void move();

    // QuObject interface
public:


    // QuEntity interface
public:
    int getClassId() override;
    void advance(int step) override;
};

#endif // QUPLAYABLECHARACTER_H
