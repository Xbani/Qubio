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
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);

    // QuEntity interface
public:
    int getClassId();
};

#endif // QUPLAYABLECHARACTER_H
