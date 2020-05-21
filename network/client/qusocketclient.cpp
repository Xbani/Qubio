#include "qusocketclient.h"

QuSocketClient::QuSocketClient(QuGameClient *quClient/*, QObject *parent*/)//:QuSocket(parent)
{
    this->quClient = quClient;
}

void QuSocketClient::receive(){

}
