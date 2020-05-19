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
    QuUnplayableCharacter();
    QuUnplayableCharacter(int instance_id);

    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);

    // QuEntity interface
public:
    int getClassId();
};

#endif // QUUNPLAYABLECHARACTER_H
