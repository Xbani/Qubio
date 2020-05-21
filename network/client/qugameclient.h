#ifndef QUCLIENT_H
#define QUCLIENT_H

//#include <QObject>
#include "qusocketclient.h"

#include <QThread>
//#include <QHostAddress>
//#include <QNetworkDatagram>

//#include "network/client/qusocketclient.h"

class QuGameClient :QObject//: public QThread
{
    Q_OBJECT
private:
    QNetworkDatagram *serverDatagrm;
    //QuSocketClient *quSocketClient;
    //alouter qroom et quUiWaitingRomm.... + dans constructeur.

public:
    explicit QuGameClient(QHostAddress ipServer, int port, QObject *parent = nullptr);

private:
    //void run() override;

signals:

};

#endif // QUCLIENT_H
