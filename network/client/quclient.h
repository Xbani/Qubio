#ifndef QUCLIENT_H
#define QUCLIENT_H

//#include <QObject>
//#include "qusocketclient.h"

#include <QObject>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QJsonObject>

//#include "network/client/qusocketclient.h"
class QuSocketClient;
class QuGameEngine;
class QuClient : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief serverDatagram :  the datagram sent to the server
     */
    QNetworkDatagram *serverDatagram;
    /**
     * @brief quSocketClient : the object use to communicate with the server
     */
    QuSocketClient *quSocketClient;
    QuGameEngine *quGameEngine;
    QHostAddress ipServer;
    int portServer;
    QHostAddress ipClient;
    int portClient;
    /**
     * @brief lastIdMessageSend : the id of the last message send
     */
    int lastIdMessageSend;
    /**
     * @brief lastIdMessageReceive : the id of the last med=ssage reiceive
     */
    int lastIdMessageReceive;

public:
    explicit QuClient(QHostAddress ipClient, int portClient,
                      QuGameEngine *quGameEngine, QObject *parent = nullptr);
    ~QuClient();

    /**
     * @brief connectToServer
     * @param ipServer the ip of server
     * @param portServer port of connetction to the server
     */
    void connectToServer(QHostAddress ipServer, int portServer);
    /**
     * @brief receiveEntities receive the entities from the server
     * @param jsonEntities the json that containe the entities
     */
    void receiveEntities(QJsonObject *jsonEntities);
    /**
     * @brief startGame : receive a message from the server when the game start
     */
    void startGame();

    void askStartGame();
    void endGame();
    /**
     * @brief sendEntity send one entity tothe server
     * @param jsonEntity the json that containe the entity
     */
    void sendEntity(QJsonObject *jsonEntity);
    /**
     * @brief receiveMap : call when the client receive the game map from the server
     * @param jsonMap the json that containe the game map
     */
    void receiveMap(QJsonObject *jsonMap);
    /**
     * @brief receivePlayerId : when the server send the player id of the palyer to the player.
     * the server send the playerId when it accept the connection
     * @param jsonPlayerId the json that containe the playerId
     */
    void receivePlayerId(QJsonObject *jsonPlayerId);
    /**
     * @brief receivePlayerList receive from the server the player list
     * @param jsonPlayerList the json that containe the playersList
     */
    void receivePlayersList(QJsonObject *jsonPlayersList);
private:

signals:

};

#endif // QUCLIENT_H
