//#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDateTime>

#include <objects/quentity.h>

#include <objects/enumblock/qulistblock.h>

#include <objects/blocks/quspawnblock.h>

#include <objects/entities/qucrown.h>
//#include <QJsonValue>
#include <QTimer>
#include <QFile>
#include "quserver.h"
#include "quinfoclient.h"
#include "qusocketserver.h"
#include "network/messagetype.h"
#include "quexpectedanswer.h"

QuServer::QuServer(QHostAddress ipServer, int portServer, QObject *parent):QObject(parent)
{
    lastMessageIdSent = 0;
    lastPlayerIdGiven = 0;
    jsonMap = new QJsonObject();
    QRandomGenerator rand = QRandomGenerator::securelySeeded();
    int num = rand.bounded(0,3);
    QString nameFile = ":/resources/devSaves/world";
            nameFile.append(QString::number(num));
            nameFile += ".qumap";
    QFile file(nameFile);
    qDebug()<<nameFile;
    file.open(QFile::ReadOnly);

    QTextStream in(&file);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    file.close();
    jsonMap = new QJsonObject(jsonDoc.object());

    quSocketServer = new QuSocketServer(this);
    quSocketServer->init(ipServer,portServer);
    timer = new QTimer(this);
    timer->setInterval(INTERVAL_TIME_CHECK_CONNECTION);
    connect(timer, SIGNAL(timeout()), this, SLOT(handlePlayersConnection()));
    timer->start();
    qDebug()<<"server créer";
}

void QuServer::startGame()
{
    //if at least one client hasn't received the map or the players list, we do nothing
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        if(quInfoClient->getMapReception() == false || quInfoClient->getPlayersListReception() == false) {
            return;
        }
    }
    //We send the start game message to all the clients
    lastMessageIdSent ++;
    QJsonObject qJsonObject;
    qJsonObject["messageId"] = lastMessageIdSent;
    qJsonObject["messageType"] = MessageType::startGameByServer;
    QRandomGenerator rand = QRandomGenerator::securelySeeded();
    int randValue = rand.bounded(0,100);
    qJsonObject["rand"] = randValue;
    QJsonDocument qJsonDocument(qJsonObject);
    (this->quSocketServer)->sendToAll(qJsonDocument.toJson(QJsonDocument::Compact));

    QJsonArray blocksArray = (*jsonMap)["blocks"].toArray();
    int arrayPos = 0;
    for(arrayPos = 0; arrayPos < blocksArray.size(); arrayPos++) {
        QJsonObject jsonBlock = blocksArray[arrayPos].toObject();
        QJsonArray coordsArray = jsonBlock["coords"].toArray();
        int blockNumber = 0;
        for(blockNumber = 0; blockNumber < coordsArray.size(); blockNumber++) {
            switch (jsonBlock["blockType"].toInt()) {
                case QuListBlock::Flag:{
                    QuSpawnBlock *spawn = new QuSpawnBlock();
                    QJsonArray blockCoordsArray = coordsArray[blockNumber].toArray();
                    QPoint point(blockCoordsArray[0].toInt() * QuObject::CELL_SIZE, blockCoordsArray[1].toInt() * QuObject::CELL_SIZE);
                    spawn->setPos(point);
                    spawBlocks.append(spawn);
                    break;
                }
            }
        }
    }

    QuCrown quCrown(jsonEntitiesMap.size()+1);
    quCrown.setPos(spawBlocks.at(randValue % spawBlocks.size())->getPos());
    jsonEntitiesMap.insert(quCrown.getClassId(), quCrown.toJSON());

    disconnect(timer, SIGNAL(timeout()), this, SLOT(handlePlayersConnection()));
    //We send the info too the players every x ms
    timer->setInterval(INTERVAL_TIME_ENTITIES);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendEntitiesToAll()));
}

void QuServer::endGame()
{
    this->timer->stop();
}

void QuServer::sendEntitiesToAll()
{
    QJsonArray jsonArrayEntities;
    lastMessageIdSent ++;
    foreach(QJsonObject *jsonEntity, jsonEntitiesMap) {
        //qDebug()<<"foreach";
        QJsonValue jsonValueEntity(*jsonEntity);
        jsonArrayEntities.append(jsonValueEntity);
     }
    QJsonObject jsonEntitiesList;
    jsonEntitiesList["entities"] = jsonArrayEntities;
    jsonEntitiesList["messageId"] = lastMessageIdSent;
    jsonEntitiesList["messageType"] = MessageType::sendEntity;
    QJsonDocument qJsonDocument(jsonEntitiesList);
    (this->quSocketServer)->sendToAll(qJsonDocument.toJson(QJsonDocument::Compact));
}

void QuServer::newPlayerConnect(QJsonObject *jsonConnection, QHostAddress ip, int port)
{
    //Save the player info in a new object
    QuInfoClient* quInfoClient = new QuInfoClient();
    quInfoClient->setIp(ip);
    quInfoClient->setPort(port);
    quInfoClient->setNickname((*jsonConnection)["nickname"].toString());
    quInfoClient->setSkin((*jsonConnection)["skin"].toDouble());
    quInfoClient->setIsHost((*jsonConnection)["isHost"].toBool());
    //give an id to the player
    ++lastPlayerIdGiven;
    quInfoClient->setPlayerId(lastPlayerIdGiven);
    clientsInfoMap.insert(lastPlayerIdGiven, quInfoClient);
    //we add the datagrams to the datagram list & send the id to the new player
    QNetworkDatagram *datagram = new QNetworkDatagram();
    datagram->setDestination(ip, port);
    quSocketServer->addDatagram(datagram);
    QJsonObject qJsonObject;
    ++lastMessageIdSent;
    qJsonObject["messageId"] = lastMessageIdSent;
    qJsonObject["messageType"] = MessageType::idPlayer;
    qJsonObject["playerId"] = quInfoClient->getPlayerId();
    QJsonDocument qJsonDocument(qJsonObject);
    datagram->setData(qJsonDocument.toJson(QJsonDocument::Compact));
    this->quSocketServer->send(datagram);
    //We expect an answer to the msg sent
    quInfoClient->addExpectedAnswer(lastMessageIdSent, MessageType::idPlayer);
    //A new player is connected so all the clients hasn't received the updated players list yet
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        quInfoClient->setPlayersListReception(false);
    }
    handlePlayersConnection();
}

void QuServer::sendMap(QuInfoClient * quInfoClient)
{
    lastMessageIdSent ++;
    QNetworkDatagram* datagram = new QNetworkDatagram();
    (*jsonMap)["messageId"] = lastMessageIdSent;
    (*jsonMap)["messageType"] = MessageType::sendMap;
    QJsonDocument qJsonDocument(*jsonMap);
    datagram->setDestination(quInfoClient->getIp(), quInfoClient->getPort());
    datagram->setData(qJsonDocument.toJson(QJsonDocument::Compact));
    (this->quSocketServer)->send(datagram);
    quInfoClient->addExpectedAnswer(lastMessageIdSent, MessageType::sendMap);
}

void QuServer::sendMapToAll() {
    lastMessageIdSent ++;
    (*jsonMap)["messageId"] = lastMessageIdSent;
    (*jsonMap)["messageType"] = MessageType::sendMap;
    QJsonDocument qJsonDocument(*jsonMap);
    (this->quSocketServer)->sendToAll(qJsonDocument.toJson(QJsonDocument::Compact));
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        quInfoClient->addExpectedAnswer(lastMessageIdSent, MessageType::sendMap);
    }
}

void QuServer::sendPlayersListToAll()
{
    QJsonArray jsonArrayPlayers;
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        QJsonObject jsonPlayer;
        jsonPlayer["playerId"] = quInfoClient->getPlayerId();
        jsonPlayer["nickname"] = quInfoClient->getNickname();
        jsonPlayer["skin"] = quInfoClient->getSkin();
        jsonPlayer["ready"] = quInfoClient->getMapReception() && quInfoClient->getPlayersListReception();
        QJsonValue jsonValuePlayer(jsonPlayer);
        jsonArrayPlayers.append(jsonValuePlayer);
     }
    QJsonObject jsonPlayerList;
    jsonPlayerList["playerList"] = jsonArrayPlayers;
    jsonPlayerList["messageId"] = lastMessageIdSent;
    jsonPlayerList["messageType"] = MessageType::listPlayers;
    QJsonDocument qJsonDocument(jsonPlayerList);
    (this->quSocketServer)->sendToAll(qJsonDocument.toJson(QJsonDocument::Compact));
}

void QuServer::aPlayerWon(QJsonObject *)
{

}

void QuServer::handleClientAnswer(QJsonObject * jsonClientAnswer)
{
    bool answerChecked;
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        if((*jsonClientAnswer)["playerId"].toInt() == quInfoClient->getPlayerId()) {
            answerChecked = quInfoClient->checkAnswer((*jsonClientAnswer)["answerMessageId"].toInt(), (MessageType)(*jsonClientAnswer)["answerMessageType"].toInt());
            if(answerChecked == true) {
                switch ((*jsonClientAnswer)["answerMessageType"].toInt()) {
                    case MessageType::idPlayer:
                        sendMap(quInfoClient);
                        break;
                    case MessageType::sendMap:
                        quInfoClient->setMapReception(true);
                        break;
                    case MessageType::listPlayers:
                        quInfoClient->setPlayersListReception(true);
                        break;
                }
            } else {
                return;
            }
        }
    }
}

void QuServer::receiveNewMap(QJsonObject * jsonMap)
{
    delete(this->jsonMap);
    //save the map in parameters in the jsonMap attribute
    this->jsonMap = jsonMap;
    //The updated map isn't sent to the clients yet
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        quInfoClient->setMapReception(false);
    }
    sendMapToAll();
}

void QuServer::receiveEntities(QJsonObject * jsonEntities)
{
    QJsonArray jsonEntitiesArray = (*jsonEntities)["entities"].toArray();
    for (int i = 0; i < jsonEntitiesArray.size() ; ++i)
    {
        QJsonObject* object = new QJsonObject();
        *object = jsonEntitiesArray[i].toObject();
        if ((*object)["messageId"].toInt() > lastMsgIdsOfEntitiesMap.take((*jsonEntities)["entities"].toInt())) {
            lastMsgIdsOfEntitiesMap.insert((*object)["messageId"].toInt(), lastMsgIdsOfEntitiesMap.take((*jsonEntities)["entities"].toInt()));
            jsonEntitiesMap.insert((*object)["instanceId"].toInt(), object);
        }else if(!lastMsgIdsOfEntitiesMap.contains((*jsonEntities)["entities"].toInt()))
            jsonEntitiesMap.insert((*object)["instanceId"].toInt(), object);
    }
}

void QuServer::receiveDeathMessage(QJsonObject *jsonDeath)
{
    if ((*jsonDeath)["wasCrowned"].toBool()){

        foreach(QJsonObject *entity,jsonEntitiesMap){
            if((*entity)["classId"].toInt() == QuEntity::CROWN_ID){
                if ((*jsonDeath)["outOfBound"].toBool()){
                    (*entity)["position"] = (*jsonDeath)["deathPosition"];//TODO
                    (*entity)["owner"] = -1;
                }else{
                    (*entity)["position"] = (*jsonDeath)["deathPosition"];
                    (*entity)["owner"] = -1;
                }
            }
        }
    }
}

void QuServer::receiveGetCrown(QJsonObject *jsonGetCrown)
{
    foreach(QJsonObject *entity,jsonEntitiesMap){
        if((*entity)["classId"].toInt() == QuEntity::CROWN_ID){
            (*entity)["owner"] = (*jsonGetCrown)["playerId"];
        }
    }
}

void QuServer::handlePlayersConnection()
{
  ++lastMessageIdSent;
    foreach(QuInfoClient *quInfoClient, clientsInfoMap) {
        bool playersListAnswerWaiting = false;
        foreach(QuExpectedAnswer *quExpectedAnswer, quInfoClient->getIExpectedAnswersMap()) {
            quExpectedAnswer->incrementCounterForTimeOut();
            if(quExpectedAnswer->getCounterForTimeOut() > 2) {
                if(quExpectedAnswer->getAnswerType() == MessageType::sendMap) {
                    QNetworkDatagram* datagram = new QNetworkDatagram();
                    datagram->setDestination(quInfoClient->getIp(), quInfoClient->getPort());
                    (*jsonMap)["messageId"] = quExpectedAnswer->getMessageSentId();
                    (*jsonMap)["messageType"] = MessageType::sendMap;
                    QJsonDocument qJsonDocument(*jsonMap);
                    datagram->setData(qJsonDocument.toJson(QJsonDocument::Compact));
                    (this->quSocketServer)->send(datagram);
                }
                else if(quExpectedAnswer->getAnswerType() == MessageType::idPlayer) {
                    QNetworkDatagram *datagram = new QNetworkDatagram();
                    datagram->setDestination(quInfoClient->getIp(), quInfoClient->getPort());
                    QJsonObject qJsonObject;
                    qJsonObject["messageId"] = quExpectedAnswer->getMessageSentId();
                    qJsonObject["messageType"] = MessageType::idPlayer;
                    qJsonObject["playerId"] = quInfoClient->getPlayerId();
                    QJsonDocument qJsonDocument(qJsonObject);
                    datagram->setData(qJsonDocument.toJson(QJsonDocument::Compact));
                    this->quSocketServer->send(datagram);
                }
            }
            else if(quExpectedAnswer->getAnswerType() == MessageType::listPlayers) {
                playersListAnswerWaiting = true;
                quExpectedAnswer->setMessageSentId(lastMessageIdSent);
            }

        }
        if(playersListAnswerWaiting == false) {
            quInfoClient->addExpectedAnswer(lastMessageIdSent, MessageType::listPlayers);
        }
    }
    this->sendPlayersListToAll();
}
