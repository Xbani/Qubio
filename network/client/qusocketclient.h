#ifndef QUSOCKETCLIENT_H
#define QUSOCKETCLIENT_H

#include "network/qusocket.h"

#include "network/client/qugameclient.h"

//#include "quclient.h"
//#include "network/client/quclient.h"

class QuSocketClient : public QuSocket
{

private:
    QuGameClient *quClient;

public:
    QuSocketClient(QuGameClient *testquClient/*, QObject *parent = nullptr*/);

    void receive() override;

};

#endif // QUSOCKETCLIENT_H
