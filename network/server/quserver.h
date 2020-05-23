#ifndef QUSERVER_H
#define QUSERVER_H

#include <QJsonObject>
#include <QMap>

class QuSocketServer;
class QuInfoClient;

/**
 * @brief The QuServer class handles the communication client-server
 */
class QuServer
{
public:
    QuServer();
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
     * @brief sendEntities sends the entities of the game
     * to everyone
     */
    void sendEntities();
    /**
     * @brief newPlayerConnect handles the connection of a new player
     */
    void newPlayerConnect(QJsonObject);
    /**
     * @brief sendMap sends the map to a player
     */
    void sendMap(); //param to add
    /**
     * @brief sendPlayersList sends the players list to everyone
     */
    void sendPlayersList(); //param to add
    /**
     * @brief aPlayerWon
     */
    void aPlayerWon(QJsonObject);
    /**
     * @brief answer handles the answers of the clients
     */
    void answer(QJsonObject);
    /**
     * @brief receiveNewMap receives the map from the client host
     */
    void receiveNewMap(QJsonObject*);
    /**
     * @brief receiveEntities receives the entities from the clients
     */
    void receiveEntities(QJsonObject*);
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
};

#endif // QUSERVER_H
