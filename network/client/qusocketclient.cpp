#include "qusocketclient.h"
#include "network/messagetype.h"
#include "network/client/quclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkDatagram>

QuSocketClient::QuSocketClient(QuClient *quClient, QObject *parent):QuSocket(parent)
{
    this->quClient = quClient;
}

void QuSocketClient::receive(){
    while (getUdpSocket()->hasPendingDatagrams()) {
        QNetworkDatagram datagram = getUdpSocket()->receiveDatagram();
        QJsonDocument *jsonDoc = new QJsonDocument();
        jsonDoc->fromBinaryData(datagram.data());
        qDebug()<<datagram.data();
        QJsonObject *jsonObj = new QJsonObject();
        *jsonObj = jsonDoc->object();
        switch (jsonObj->value("messageType").toInt()) {
            case MessageType::sendEntity:
                quClient->receiveEntities(jsonObj);
            break;
            case MessageType::idPlayer :
                quClient->receivePlayerId(jsonObj);
            break;
            case MessageType::sendMap:
                quClient->receiveMap(jsonObj);
            break;
            case MessageType::listPlayers:
                quClient->receivePlayersList(jsonObj);
            break;
            case MessageType::startGameByServer:
                quClient->startGame();
            break;
            case MessageType::endGame:
                quClient->endGame();
            break;
        }
    }
}
