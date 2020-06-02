#include "mainwindow.h"
#include "qugameengine.h"

#include <QApplication>
#include <QGraphicsView>

#include <objects/quobject.h>

#include <rooms/ui/quuimainmenu.h>

#include <rooms/qubuildermapframe.h>
#include <rooms/qumapbuilder.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuGameEngine w;
    return a.exec();
}
