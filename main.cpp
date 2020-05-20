#include "mainwindow.h"
#include "qugameengine.h"

#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuGameEngine w;
    return a.exec();
}
