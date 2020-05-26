#include "mainwindow.h"
#include "qugameengine.h"

#include <QApplication>
#include <QGraphicsView>

#include <objects/quobject.h>

#include <rooms/ui/quuimainmenu.h>

#include <rooms/qumapbuilder.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QuGameEngine w;
    QGraphicsView *view;
    QuMapBuilder *mapBuilder = new QuMapBuilder(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE);
    view = new QGraphicsView();
    view->setScene(mapBuilder);
    view->show();
    return a.exec();
}
