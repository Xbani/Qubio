#ifndef QUSOCKETSERVER_H
#define QUSOCKETSERVER_H
#include "network/qusocket.h"
#include <QNetworkDatagram>
#include <QString>

class QuSocketServer : public QuSocket
{
public:
    /**
     * @brief QuSocketServer constructor
     * @param parent
     */
    QuSocketServer(QObject *parent = nullptr);
    /**
     * @brief sendToAll sends the 'data' using datagrams of 'datagramList'
     * @param data
     */
    void sendToAll(QByteArray data);
    /**
     * @brief redirects the message to a function
     */
    void receive() override;
private:
    /**
     * @brief datagramList the list of datagrams of all clients
     */
    QVector<QNetworkDatagram*> datagramList;
    //QuServer *quServer; //à activer après avoir fait le QuServer + à ajouter au construc
};

#endif // QUSOCKETSERVER_H
