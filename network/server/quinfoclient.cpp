#include "network/server/quexpectedanswer.h"
#include "network/server/quinfoclient.h"

QuInfoClient::QuInfoClient(QObject *parent) : QObject(parent)
{
    mapReception = false;
    playersListReception = false;
    isHost = false;
}

void QuInfoClient::addExpectedAnswer(int messageSentId, MessageType answerType)
{
    QuExpectedAnswer* quExpectedAnswer = new QuExpectedAnswer(messageSentId, answerType, this);
    expectedAnswersMap.insert(messageSentId, quExpectedAnswer);
}

bool QuInfoClient::checkAnswer(int messageSentId, MessageType messageSentType)
{
    if(this->expectedAnswersMap.take(messageSentId)->getAnswerType() == messageSentType) {
        this->expectedAnswersMap.remove(messageSentId);
        return true;
    }
    return false;
}
