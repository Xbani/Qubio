#include "qusocketserver.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "network/messagetype.h"
#include "network/server/quserver.h"

QuSocketServer::QuSocketServer(QuServer* quServer,QObject *parent) : QuSocket(parent)
{
    this->quServer = quServer;

}

void QuSocketServer::sendToAll(QByteArray data)
{
    for(int datagramPos = 0; datagramPos < this->datagramList.size(); datagramPos++) {
        datagramList[datagramPos]->setData(data);
        send(datagramList[datagramPos]);
    }
}

void QuSocketServer::receive()
{
    while (getUdpSocket()->hasPendingDatagrams()) {
            QNetworkDatagram datagram = getUdpSocket()->receiveDatagram();
           QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram.data()); //transform binary data into a json doc
            QJsonObject *jsonObj = new QJsonObject();
            *jsonObj = jsonDoc.object();

            QJsonDocument debug(*jsonObj);
            qDebug()<<"serveur"<<debug.toJson(QJsonDocument::Compact);

            switch (jsonObj->value("messageType").toInt()) {
                case MessageType::sendEntity:
                    quServer->receiveEntities(jsonObj);
                break;
                case MessageType::death:
                    quServer->receiveDeathMessage(jsonObj);
                break;
                case MessageType::connection:
                    quServer->newPlayerConnect(jsonObj, datagram.senderAddress(), datagram.senderPort());
                break;
                case MessageType::answer:
                    quServer->handleClientAnswer(jsonObj);
                break;
                case MessageType::newMap:
                    quServer->receiveNewMap(jsonObj);
                break;
                case MessageType::gameWon:
                    quServer->aPlayerWon(jsonObj);
                break;
                case MessageType::startGameRequest:
                    quServer->startGame();
                break;
            }
        }
}

void QuSocketServer::addDatagram(QNetworkDatagram *datagram)
{
    this->datagramList.append(datagram);
}


