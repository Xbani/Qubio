#ifndef QUSOCKET_H
#define QUSOCKET_H

#include <QObject>
#include <QUdpSocket>

class QuSocket : public QObject
{
    Q_OBJECT

public:
    explicit QuSocket(QObject* parent = nullptr);
    void send(QNetworkDatagram* datagram);
    void init(QHostAddress ip, int port);
    virtual void receive() = 0;

    inline QUdpSocket* getUdpSocket() const { return udpSocket; };

private:
    QUdpSocket *udpSocket;

signals:
};

#endif // QUSOCKET_H
