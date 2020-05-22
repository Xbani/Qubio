#include "quclient.h"
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonArray>
#include "network/client/qusocketclient.h"
#include "network/MessageType.h"
#include "qugameengine.h"
#include "rooms/qugame.h"
#include "objects/quentity.h"


QuClient::QuClient(QHostAddress &ipServer, int &portServer,
                   QHostAddress &ipClient, int &portClient,
                   QuGameEngine *quGameEngine, QObject *parent): QThread(parent)
{
    serverDatagram = new QNetworkDatagram();
    serverDatagram->setDestination(ipServer, portServer);
    this->ipServer = ipServer;
    this->portServer = portServer;
    this->ipClient = ipClient;
    this->portClient = portClient;
    this->quGameEngine = quGameEngine;
    lastIdMessageSend = 0;
    lastIdMessageReceive = 0;
}

QuClient::~QuClient()
{
    delete(serverDatagram);
}

void QuClient::receiveEntities(QJsonObject *jsonEntities)
{
    if((*jsonEntities)["messageId"].toInt() > lastIdMessageReceive){
        lastIdMessageReceive = (*jsonEntities)["messageId"].toInt();
        QJsonArray jsonPlayerArray = (*jsonEntities)["entities"].toArray();

        for (int entityId = 0; entityId < jsonPlayerArray.count(); entityId++){
            QJsonValue entityValue = jsonPlayerArray.at(entityId);
            quGameEngine->getQuGame()->getEntities().take(entityValue["instanceId"].toInt())->fromJSON(entityValue.toObject());
        }
    }
}

void QuClient::startGame()
{

}

void QuClient::endGame()
{

}

void QuClient::sendEntity(QJsonObject *jsonEntity)
{
    lastIdMessageSend++;
    (*jsonEntity)["messageId"] = lastIdMessageSend;
    (*jsonEntity)["messageType"] = MessageType::sendEntity;
    QJsonDocument jsonDoc(*jsonEntity);
    serverDatagram->setData(jsonDoc.toBinaryData());
    quSocketClient->send(serverDatagram);
}

void QuClient::receiveMap(QJsonObject *jsonMap)
{

}

void QuClient::receivePlayerId(QJsonObject *jsonPlayerId)
{
    quGameEngine->setPlayerId((*jsonPlayerId)["playerId"].toInt());
    lastIdMessageReceive = (*jsonPlayerId)["messageId"].toInt();
}

void QuClient::receivePlayerList(QJsonObject *jsonPlayerList)
{
    if((*jsonPlayerList)["messageId"].toInt() > lastIdMessageReceive){
        lastIdMessageReceive = (*jsonPlayerList)["messageId"].toInt();
        QJsonArray *jsonPlayerArray = new QJsonArray();
        *jsonPlayerArray = (*jsonPlayerList)["playerList"].toArray();
        //fonction a oscar
        //TODO
    }

}

void QuClient::run(){
    quSocketClient = new QuSocketClient(this,this);
    quSocketClient->init(ipClient,portClient);
}
