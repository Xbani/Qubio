#ifndef QUINFOCLIENT_H
#define QUINFOCLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QVector3D>
#include "network/MessageType.h"
class QuExpectedAnswer;

/**
 * @brief The QuInfoClient class saves the client information
 */
class QuInfoClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief QuInfoClient a constructor
     * @param parent
     */
    explicit QuInfoClient(QObject *parent = nullptr);

    /** Getters and setters **/
    inline int getPlayerId() const { return this->playerId; };
    inline void setPlayerId(int value) { this->playerId = value; };

    inline QString getNickname() const { return this->nickname; };
    inline void setNickname(const QString &value){ this->nickname = value; };

    inline int getSkin() const { return this->skin; };
    inline void setSkin(int value) { this->skin = value; };

    inline QHostAddress getIp() const { return this->ip; };
    inline void setIp(const QHostAddress &value) { this->ip = value; };

    inline int getPort() const { return this->port; };
    inline void setPort(int value) { this->port = value; }

    /**
     * @brief addExpectedAnswer adds an expected answer to a message sent
     * in the map of expected answers
     * @param messageSentId the id of message sent to which we have an expected answer
     * @param answerType the type of the exepected answer
     */
    void addExpectedAnswer(int messageSentId, MessageType answerType);
    /**
     * @brief checkAnswer checks if the answer received is good
     * @param messageSentId
     * @param messageSentType
     * @return true if the answer received is the right one and false if not
     */
    bool checkAnswer(int messageSentId, MessageType messageSentType);

private:
    int playerId;
    QString nickname;
    int skin;
    QHostAddress ip;
    int port;
    /**
     * @brief expectedAnswersMap a map.
     * Key : the message sent id.
     * Value : the expected answer of the message sent.
     */
    QMap<int, QuExpectedAnswer*> expectedAnswersMap;
signals:

};

#endif // QUINFOCLIENT_H
