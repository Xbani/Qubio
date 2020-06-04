#include "qugameengine.h"
#include <rooms/ui/quuihost.h>
#include <rooms/ui/quuijoin.h>
#include <rooms/ui/quuimainmenu.h>
#include <rooms/ui/quuimultiplayer.h>

#include <QFontDatabase>
#include <QDebug>
#include <QTimer>

#include <network/client/quclient.h>

#include <rooms/ui/quuiwaitingroom.h>

#include <rooms/qugame.h>

#include <network/server/quserver.h>

QuGameEngine::QuGameEngine()
{
    create();
}

QuGameEngine::~QuGameEngine()
{
    view->close();
}

void QuGameEngine::toUIMultiplayer()
{
    view->setScene(uiMultiplayer);
}

void QuGameEngine::toUIMainMenu()
{
    view->setScene(uiMainMenu);
}

void QuGameEngine::toUIHost()
{
    view->setScene(uiHost);
}

void QuGameEngine::toUIJoin()
{
    view->setScene(uiJoin);
}

void QuGameEngine::toQuGame()
{
    quGame = new QuGame(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    view->setScene(quGame);
    timer->start(1000 / 60);
    connect(timer, SIGNAL(timeout()), quGame, SLOT(advance()));
}

void QuGameEngine::toQuGameMultiPlayers()
{
    quGame = new QuGame(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    if (isHost)
        quGame->createPlayers(uiWaitingRoomHost->getQuPlayerInfos());
    else
        quGame->createPlayers(uiWaitingRoomJoin->getQuPlayerInfos());
    view->setScene(quGame);
    timer->start(1000 / 60);
    connect(timer, SIGNAL(timeout()), quGame, SLOT(advance()));
}

void QuGameEngine::fromUIJoinToWaitingRoom()
{
    quClient = new QuClient(QHostAddress("127.0.0.0"),25667,this);
    quClient->connectToServer(getIpJoin(),getPortJoin());
    view->setScene(uiWaitingRoomJoin);

}

void QuGameEngine::fromUIHostToWaitingRoom()
{
    quServer = new QuServer(getIpHost(),getPortHost(),this);
    if (getPortHost() == 25667)
        quClient = new QuClient(getIpHost(),25668,this);
    else
        quClient = new QuClient(getIpHost(),25667,this);
    quClient->connectToServer(getIpHost(), getPortHost());
    view->setScene(uiWaitingRoomHost);
}

void QuGameEngine::toBuilderMapFrame()
{
    quBuilderMapFrame->show();
}

void QuGameEngine::askStartGame()
{
    quClient->askStartGame();
}

QHostAddress QuGameEngine::getIpJoin()
{
    if(uiJoin->getIp()=="localhost"){
        return QHostAddress("127.0.0.1");
    }
    return QHostAddress(uiJoin->getIp());
}

int QuGameEngine::getPortJoin()
{
    return uiJoin->getPort().toInt();
}

QHostAddress QuGameEngine::getIpHost()
{
    if(uiHost->getIp()=="localhost"){
        return QHostAddress("127.0.0.1");
    }
    return QHostAddress(uiHost->getIp());
}

int QuGameEngine::getPortHost()
{
    return uiHost->getPort().toInt();
}

void QuGameEngine::create()
{
    uiMainMenu = new QuUIMainMenu(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,this);
    uiMultiplayer = new QuUIMultiplayer(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,this);
    uiHost = new QuUIHost(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,this);
    uiJoin = new QuUIJoin(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,this);
    uiWaitingRoomHost = new QuUIWaitingRoom(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,true,this);
    uiWaitingRoomJoin = new QuUIWaitingRoom(0,0,16*QuObject::CELL_SIZE,8*QuObject::CELL_SIZE,false,this);
    quBuilderMapFrame = new QuBuilderMapFrame(new QGraphicsView());

    view = new QGraphicsView();
    view->setScene(uiMainMenu);
    view->show();
    timer = new QTimer;
    timer->stop();
}
