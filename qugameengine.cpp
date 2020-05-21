#include "qugameengine.h"

#include <QFontDatabase>
#include <QDebug>

QuGameEngine::QuGameEngine()
{
    create();
}

void QuGameEngine::create()
{
    uiMainMenu = new QuUIMainMenu(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE);
    view = new QGraphicsView();
    view->setScene(uiMainMenu);
    view->show();
}
