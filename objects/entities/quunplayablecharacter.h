#ifndef QUUNPLAYABLECHARACTER_H
#define QUUNPLAYABLECHARACTER_H

#include "qucharacter.h"


/**
 * @brief The QuUnplayableCharacter class
 * @details Class which is a player controlled by another client.
 */
class QuUnplayableCharacter : public QuCharacter
{
public:
    QuUnplayableCharacter(int instance_id);
    void advance(int step) override;

    // QuObject interface
public:

    // QuEntity interface
public:
    int getClassId() override;
};

#endif // QUUNPLAYABLECHARACTER_H
