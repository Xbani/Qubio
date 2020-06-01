#include "quexpectedanswer.h"

QuExpectedAnswer::QuExpectedAnswer(int messageSentId, MessageType answerType, QObject *parent) : QObject(parent)
{
    this->messageSentId = messageSentId;
    this->answerType = answerType;
}
