#ifndef QUSOCKETCLIENT_H
#define QUSOCKETCLIENT_H

#include "network/qusocket.h"

class QuClient;
class QuSocketClient : public QuSocket
{

private:
    QuClient *quClient;

public:
    QuSocketClient(QuClient *testquClient, QObject *parent = nullptr);

    void receive() override;

};

#endif // QUSOCKETCLIENT_H
