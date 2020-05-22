#ifndef QUCLIENT_H
#define QUCLIENT_H

//#include <QObject>
//#include "qusocketclient.h"

#include <QThread>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QJsonObject>

//#include "network/client/qusocketclient.h"
class QuSocketClient;
class QuGameEngine;
class QuClient : public QThread
{
    Q_OBJECT
private:
    QNetworkDatagram *serverDatagram;
    QuSocketClient *quSocketClient;
    QuGameEngine *quGameEngine;
    QHostAddress ipServer;
    int portServer;
    QHostAddress ipClient;
    int portClient;

    int lastIdMessageSend;
    int lastIdMessageReceive;

public:
    explicit QuClient(QHostAddress &ipServer, int &portServer,
                      QHostAddress &ipClient, int &portClient,
                      QuGameEngine *quGameEngine, QObject *parent = nullptr);
    ~QuClient();

    void connectToServer(QHostAddress &ipServer, int &portServer);
    void recieveEntities(QJsonObject *jsonEntities);
    void startGame();
    void endGame();
    void sendEntity(QJsonObject *jsonEntity);
    void receiveMap(QJsonObject *jsonMap);
    void receivePlayerId(QJsonObject *jsonPlayerId);
    void receivePlayerList(QJsonObject *jsonPlayerList);
private:
    void run() override;

signals:

};

#endif // QUCLIENT_H
