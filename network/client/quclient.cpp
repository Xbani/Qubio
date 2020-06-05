#include "quclient.h"
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QJsonValue>
#include "network/client/qusocketclient.h"
#include "network/messagetype.h"
#include "qugameengine.h"
#include "rooms/qugame.h"
#include "objects/quentity.h"
#include <rooms/ui/quuiwaitingroom.h>


QuClient::QuClient(QHostAddress ipClient, int portClient,
                   QuGameEngine *quGameEngine, QObject *parent): QObject(parent)
{
    serverDatagram = new QNetworkDatagram();
    this->ipClient = ipClient;
    this->portClient = portClient;
    this->quGameEngine = quGameEngine;
    lastIdMessageSend = 0;
    lastIdMessageReceive = 0;
    quSocketClient = new QuSocketClient(this, this);
    quSocketClient->init(ipClient,portClient);
    //qDebug()<<"client créer";
}

QuClient::~QuClient()
{
    delete(serverDatagram);
}

void QuClient::connectToServer(QHostAddress ipServer, int portServer)
{
    this->ipServer = ipServer;
    this->portServer = portServer;
    serverDatagram->setDestination(ipServer, portServer);
    QJsonObject jsonConnection;
    ++lastIdMessageSend;
    jsonConnection["messageId"] = lastIdMessageSend;
    jsonConnection["messageType"] = MessageType::connection;
    jsonConnection["nickname"] = quGameEngine->getNickname();
    jsonConnection["skin"] = quGameEngine->getSkinColor();
    jsonConnection["isHost"] = quGameEngine->getIsHost();
    QJsonDocument docConnection(jsonConnection);
    //qDebug()<<"connection";
    serverDatagram->setData(docConnection.toJson(QJsonDocument::Compact));
    quSocketClient->send(serverDatagram);
}

void QuClient::receiveEntities(QJsonObject *jsonEntities)
{
    if((*jsonEntities)["messageId"].toInt() > lastIdMessageReceive){
        lastIdMessageReceive = (*jsonEntities)["messageId"].toInt();
        QJsonArray jsonPlayerArray = (*jsonEntities)["entities"].toArray();

        for (int entityId = 0; entityId < jsonPlayerArray.count(); entityId++){
            QJsonValue entityValue = jsonPlayerArray.at(entityId);
            QJsonObject entityJson = entityValue.toObject();

            QuEntity *entity = quGameEngine->getQuGame()->getEntities().take(entityJson["instanceId"].toInt());
            if(entity->getInstanceId() != quGameEngine->getPlayerId()){
                    entity->fromJSON(entityJson);
            }
        }

    }
}

void QuClient::startGame(QJsonObject *jsonStart)
{
    quGameEngine->toQuGameMultiPlayers((*jsonStart)["rand"].toInt());
}

void QuClient::askStartGame()
{
    ++lastIdMessageSend;
    QJsonObject askStart;
    askStart["messageId"] = lastIdMessageSend;
    askStart["messageType"] = MessageType::startGameRequest;
    askStart["playerId"] = quGameEngine->getPlayerId();
    QJsonDocument jsonDoc(askStart);
    serverDatagram->setData(jsonDoc.toJson(QJsonDocument::Compact));
    quSocketClient->send(serverDatagram);
}

void QuClient::endGame()
{

}

void QuClient::sendEntity(QJsonObject *jsonEntity)
{
    lastIdMessageSend++;
    QJsonObject jsonToSend;
    jsonToSend["messageId"] = lastIdMessageSend;
    jsonToSend["messageType"] = MessageType::sendEntity;
    QJsonArray jsonArrayEntities;
    QJsonValue jsonValueEntity(*jsonEntity);
    jsonArrayEntities.append(jsonValueEntity);
    jsonToSend["entities"] = jsonArrayEntities;

    QJsonDocument jsonDoc(jsonToSend);
    serverDatagram->setData(jsonDoc.toJson(QJsonDocument::Compact));
    quSocketClient->send(serverDatagram);
}

void QuClient::receiveMap(QJsonObject *jsonMap)
{
    lastIdMessageReceive = (*jsonMap)["messageId"].toInt();

    quGameEngine->setJsonMap(jsonMap);
    ++lastIdMessageSend;
    QJsonObject answer;
    answer["messageId"] = lastIdMessageSend;
    answer["messageType"] = MessageType::answer;
    answer["playerId"] = quGameEngine->getPlayerId();
    answer["answerMessageId"] = (*jsonMap)["messageId"].toInt();
    answer["answerMessageType"] = (*jsonMap)["messageType"].toInt();
    QJsonDocument jsonDoc(answer);
    serverDatagram->setData(jsonDoc.toJson(QJsonDocument::Compact));
    quSocketClient->send(serverDatagram);
}

void QuClient::receivePlayerId(QJsonObject *jsonPlayerId)
{
    quGameEngine->setPlayerId((*jsonPlayerId)["playerId"].toInt());
    lastIdMessageReceive = (*jsonPlayerId)["messageId"].toInt();

    ++lastIdMessageSend;
    QJsonObject answer;
    answer["messageId"] = lastIdMessageSend;
    answer["messageType"] = MessageType::answer;
    answer["playerId"] = quGameEngine->getPlayerId();
    answer["answerMessageId"] = (*jsonPlayerId)["messageId"].toInt();
    answer["answerMessageType"] = (*jsonPlayerId)["messageType"].toInt();
    QJsonDocument jsonDoc(answer);
    serverDatagram->setData(jsonDoc.toJson(QJsonDocument::Compact));
    quSocketClient->send(serverDatagram);
}

void QuClient::receivePlayersList(QJsonObject *jsonPlayerList)
{
    if((*jsonPlayerList)["messageId"].toInt() > lastIdMessageReceive){
        lastIdMessageReceive = (*jsonPlayerList)["messageId"].toInt();
        QJsonArray *jsonPlayerArray = new QJsonArray();
        *jsonPlayerArray = (*jsonPlayerList)["playerList"].toArray();

        QuUIWaitingRoom *quUIWaitingRoom;
        if(quGameEngine->getIsHost()){
            quUIWaitingRoom = quGameEngine->getWaitingRoomHost();
        }
        else{
            quUIWaitingRoom = quGameEngine->getWaitingRoomJoin();
        }
        quUIWaitingRoom->setPlayersJSON(jsonPlayerArray);

        ++lastIdMessageSend;
        QJsonObject answer;
        answer["messageId"] = lastIdMessageSend;
        answer["messageType"] = MessageType::answer;
        answer["playerId"] = quGameEngine->getPlayerId();
        answer["answerMessageId"] = (*jsonPlayerList)["messageId"].toInt();
        answer["answerMessageType"] = (*jsonPlayerList)["messageType"].toInt();
        QJsonDocument jsonDoc(answer);
        serverDatagram->setData(jsonDoc.toJson(QJsonDocument::Compact));
        quSocketClient->send(serverDatagram);
    }
}


