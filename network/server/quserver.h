#ifndef QUSERVER_H
#define QUSERVER_H

#include <QJsonObject>
#include <QMap>
#include <QHostAddress>
#include <QTimer>
#include <QObject>

class QuSocketServer;
class QuInfoClient;

/**
 * @brief The QuServer class handles the communication client-server
 */
class QuServer : public QObject
{
    Q_OBJECT
public:
    QuServer(QHostAddress ipServer, int portServer, QObject *parent = nullptr);
    /**
     * @brief startGame sends a message to everyone
     * to tell them that the game begins
     */
    void startGame();
    /**
     * @brief endGame
     */
    void endGame();
    /**
     * @brief newPlayerConnect handles the connection of a new player
     */
    void newPlayerConnect(QJsonObject* jsonConnection, QHostAddress ip, int port);
    /**
     * @brief sendMap sends the map to a player
     */
    void sendMap(QuInfoClient* quInfoClient); //param TODO
    /**
     * @brief sendMapToAll sends the new map to all the clients
     */
    void sendMapToAll();
    /**
     * @brief sendPlayersList sends the players list to everyone
     */
    void sendPlayersListToAll(); //param to add
    /**
     * @brief aPlayerWon
     */
    void aPlayerWon(QJsonObject*);
    /**
     * @brief handleClientAnswer handles the answers of the clients
     */
    void handleClientAnswer(QJsonObject*);
    /**
     * @brief receiveNewMap receives the map from the client host
     */
    void receiveNewMap(QJsonObject* jsonMap);
    /**
     * @brief receiveEntities receives the entities from the clients
     */
    void receiveEntities(QJsonObject* jsonEntities);

    void receiveDeathMessage(QJsonObject* jsonDeath);

public slots :
    /**
     * @brief sendEntities sends the entities of the game
     * to everyone
     */
    void sendEntitiesToAll();
    /**
     * @brief handlePlayersConnection
     */
    void handlePlayersConnection();

private:
    /**
     * @brief jsonEntities a map
     * keys : entities ids
     * values : jsonObjects with information about each entity
     * An entity may be a character of the game for example
     */
    QMap<int, QJsonObject*> jsonEntitiesMap;
    /**
     * @brief lastMessagesIdsOfEntities a map
     * keys : entities ids
     * values : last messages ids that contains those entities
     */
    QMap<int, int> lastMsgIdsOfEntitiesMap;
    /**
     * @brief jsonMap the map of the game
     */
    QJsonObject* jsonMap;
    /**
     * @brief socketServer
     */
    QuSocketServer* quSocketServer;
    /**
     * @brief clientsInfoMap a map that saves clients information.
     * Key : client id.
     * Value : client information.
     */
    QMap<int, QuInfoClient*> clientsInfoMap;
    int lastMessageIdSent;
    int lastPlayerIdGiven;
    QTimer* timer;
    const int INTERVAL_TIME_ENTITIES = 16;
    const int INTERVAL_TIME_CHECK_CONNECTION = 5000;
};
#endif // QUSERVER_H
