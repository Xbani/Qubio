#include "qumapbuilder.h"

#include <QGraphicsProxyWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>


QuMapBuilder::QuMapBuilder(qreal x, qreal y, qreal width, qreal height, QObject *parent) : QGraphicsScene(x,y,width,height,parent)
{
    init();
}

void QuMapBuilder::init()
{
    QMenuBar *qMenuBar = new QMenuBar();
    QMenu *menuBlock = new QMenu("test",qMenuBar);
    menuBlock->addAction("block1");
    menuBlock->addAction("block2");
    qMenuBar->addMenu(menuBlock);
    qMenuBar->addAction("enregistrer");
    //qMainWindow->addDockWidget(Qt::DockWidgetAreas(),qMenuBar);

    QPushButton *buttonTest = new QPushButton("clickMe");
    QGraphicsProxyWidget *proxy =this->addWidget(buttonTest);
    proxy->setPos(0,0);
    proxy->setVisible(true);
    //proxy->resize(64.0,640.0);
    proxy->show();
    //QMainWindow *qMainWindow = new QMainWindow();
    addWidget(qMenuBar);
}
