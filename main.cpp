#include "mainwindow.h"
#include "qugameengine.h"

#include "objects\quobject.h"
#include "objects\quentity.h"
#include "objects\qublock.h"
#include "objects\\blocks\qusolidblock.h"
#include "objects\\entities\quplayablecharacter.h"
#include "objects\\entities\quunplayablecharacter.h"
#include "charactercontroller.h"

#include <QApplication>
#include <QtWidgets>
#include <QGraphicsView>

#include <objects/quobject.h>

#include <rooms/ui/quuimainmenu.h>

#include <rooms/qubuildermapframe.h>
#include <rooms/qumapbuilder.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QuGameEngine w;

    return app.exec();
}
