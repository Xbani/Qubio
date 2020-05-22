#include "qugameengine.h"

#include <QFontDatabase>
#include <QDebug>

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

void QuGameEngine::create()
{
    uiMainMenu = new QuUIMainMenu(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    uiMultiplayer = new QuUIMultiplayer(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    uiHost = new QuUIHost(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    uiJoin = new QuUIJoin(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE,this);
    view = new QGraphicsView();
    view->setScene(uiMainMenu);
    view->show();
}
