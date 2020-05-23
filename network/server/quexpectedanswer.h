#ifndef QUEXPECTEDANSWER_H
#define QUEXPECTEDANSWER_H

#include <QObject>
#include "network/MessageType.h"

/**
 * @brief The QuExpectedAnswer class represents an answer expected from a client
 */
class QuExpectedAnswer : public QObject
{
    Q_OBJECT
public:
    explicit QuExpectedAnswer(int messageSentId, MessageType answerType, QObject *parent = nullptr);
    inline MessageType getAnswerType() const { return this->answerType; }
private:
    /**
     * @brief playerId
     */
    int playerId;
    /**
     * @brief messageSentId is the id of the message sent by the server
     */
    int messageSentId;
    /**
     * @brief answerType
     */
    MessageType answerType;
signals:

};

#endif // QUEXPECTEDANSWER_H
