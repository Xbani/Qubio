#include "qugameclient.h"
#include <QNetworkDatagram>
#include "network/client/qusocketclient.h"

QuGameClient::QuGameClient(QHostAddress ipServer, int port, QObject *parent)// : QThread(parent)
{
    serverDatagrm = new QNetworkDatagram();
    serverDatagrm->setDestination(ipServer, port);


    //quSocketClient = new QuSocketClient(this.);
}

/*void QuGameClient::run(){


}*/
