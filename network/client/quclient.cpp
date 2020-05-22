#include "quclient.h"
#include <QNetworkDatagram>
#include <QJsonDocument>
#include "network/client/qusocketclient.h"
#include "network/MessageType.h"


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

void QuClient::sendEntity(QJsonObject *jsonEntity)
{
    lastIdMessageSend++;
    (*jsonEntity)["messageId"] = lastIdMessageSend;
    (*jsonEntity)["messageType"] = MessageType::sendEntity;
    QJsonDocument jsonDoc(*jsonEntity);
    serverDatagram->setData(jsonDoc.toBinaryData());
    quSocketClient->send(serverDatagram);
}

void QuClient::run(){
    quSocketClient = new QuSocketClient(this,this);
    quSocketClient->init(ipClient,portClient);
}
