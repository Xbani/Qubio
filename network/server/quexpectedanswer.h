#ifndef QUEXPECTEDANSWER_H
#define QUEXPECTEDANSWER_H

#include <QObject>
#include "network/messagetype.h"

/**
 * @brief The QuExpectedAnswer class represents an answer expected from a client
 */
class QuExpectedAnswer : public QObject
{
    Q_OBJECT
public:
    explicit QuExpectedAnswer(int messageSentId, MessageType answerType, QObject *parent = nullptr);
    inline int getMessageSentId() const { return this->messageSentId; };
    inline void setMessageSentId(int messageSentId) { this->messageSentId = messageSentId; };
    inline MessageType getAnswerType() const { return this->answerType; };
    inline int getCounterForTimeOut() const { return this->counterForTimeOut; };
    inline void incrementCounterForTimeOut() { this->counterForTimeOut++; };


private:
    /**
     * @brief messageSentId is the id of the message sent by the server
     */
    int messageSentId;
    /**
     * @brief answerType
     */
    MessageType answerType;
    int counterForTimeOut;
signals:

};

#endif // QUEXPECTEDANSWER_H
