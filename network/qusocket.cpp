#include "qusocket.h"
#include <QNetworkDatagram>

QuSocket::QuSocket(QObject *parent) : QObject(parent)
{

}

/**
 * @brief QuSocket::send sends a datagram
 * @param datagram
 */
void QuSocket::send(QNetworkDatagram* datagram) {
    udpSocket->writeDatagram(*datagram);
}

/**
 * @brief QuSocket::init initializes the communication socket
 * @param ip
 * @param port
 */
void QuSocket::init(QHostAddress ip, int port) {
    qDebug()<<"Création Socket";
    //créer un lien vers la carte rés
    udpSocket = new QUdpSocket(this);
    //écouter un port
    udpSocket->bind(ip, port);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &QuSocket::receive);
}


