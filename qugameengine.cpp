#include "qugameengine.h"

QuGameEngine::QuGameEngine()
{
    create();
}

void QuGameEngine::create()
{
    scene = new QuUIMainMenu(0,0,64*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE);
    view = new QGraphicsView();
    view->setScene(scene);
    view->show();

    //Add roomMenu
    scene->init();

}
