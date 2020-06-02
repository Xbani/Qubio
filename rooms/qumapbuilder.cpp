#include "qumapbuilder.h"

#include <QFrame>
#include <QGraphicsProxyWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QPointF>
#include <QPushButton>

#include <objects/blocks/qusolidblock.h>
#include <network/messagetype.h>
#include <objects/enumblock/qulistblock.h>
#include <QSignalMapper>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

QuMapBuilder::QuMapBuilder(qreal x, qreal y, qreal width, qreal height, QObject *parent) : QGraphicsScene(x,y,width,height,parent)
{
    //initMapBuilder();
    blockSelected = 0;
    mousePressed = false;
    mouseMoved = false;
    setSceneRect(0,0,QuObject::CELL_SIZE*25,QuObject::CELL_SIZE*20);
}

void QuMapBuilder::selectBlock(int block)
{
    qDebug()<<block;
    blockSelected = block;
}

void QuMapBuilder::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QPointF pos = event->pos();
    }
}

void QuMapBuilder::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void QuMapBuilder::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QPointF pos = event->scenePos();
        QList<QGraphicsItem*> listItem = items();
        int posBlockX = pos.rx()-((int)pos.rx()%QuObject::CELL_SIZE);
        int posBlockY = pos.ry()-((int)pos.ry()%QuObject::CELL_SIZE);
        /*if(posBlockX == 0 && posBlockY == 0){
            posBlockX = 1;
            posBlockY = 1;
        }*/
        for(int itemI = 0; itemI < listItem.size(); ++itemI){
            QGraphicsItem *myItem = listItem.at(itemI);
            QPointF posItem = myItem->pos();
            if (posItem.rx() == posBlockX && posItem.ry() == posBlockY){
                if(dynamic_cast<QuBlock*>(myItem)){
                    removeItem(myItem);
                    delete(myItem);
                }
            }
        }
        QuSolidBlock *quSolideBlock = new QuSolidBlock(blockSelected);
        quSolideBlock->setPos(posBlockX,posBlockY);
        addItem(quSolideBlock);

    }else if (event->button() == Qt::RightButton){
        QPointF pos = event->scenePos();
        QList<QGraphicsItem*> listItem = items();
        int posBlockX = pos.rx()-((int)pos.rx()%QuObject::CELL_SIZE);
        int posBlockY = pos.ry()-((int)pos.ry()%QuObject::CELL_SIZE);
        /*if(posBlockX == 0 && posBlockY == 0){
            posBlockX = 1;
            posBlockY = 1;
        }*/
        for(int itemI = 0; itemI < listItem.size(); ++itemI){
            QGraphicsItem *myItem = listItem.at(itemI);
            QPointF posItem = myItem->pos();
            if (posItem.rx() == posBlockX && posItem.ry() == posBlockY){
                if(dynamic_cast<QuBlock*>(myItem)){
                    removeItem(myItem);
                    delete(myItem);
                }
            }
        }
    }

}

void QuMapBuilder::initMapBuilder()
{

/* voir addLine */
    QRectF rect = sceneRect();

    for (int i = 1; i < rect.height()/QuObject::CELL_SIZE; ++i){
        addLine(0,i*QuObject::CELL_SIZE,rect.width(),i*QuObject::CELL_SIZE,QPen(QColor(0,255,255)));
    }


    for (int i = 1; i <  rect.width()/QuObject::CELL_SIZE; ++i){
        addLine(i*QuObject::CELL_SIZE,0,i*QuObject::CELL_SIZE,rect.height(),QPen(QColor(0,255,255)));
    }

    //QFrame *qFrame = new QFrame();
    //addWidget(qFrame);
   /* qFrame->set
            (0,qMenuBar->size().rheight());*/

   /* addWidget(qMenuBar);

    connect(signalMapper, SIGNAL(mapped(int)),
                this, SLOT(selectBlock(int)));*/
}
/*QuSolidBlock *quSolideBlock = new QuSolidBlock(1);
quSolideBlock->setPos(50,50);
addItem(quSolideBlock);*/

/* QPushButton *buttonTest = new QPushButton("clickMe");
 QGraphicsProxyWidget *proxy =this->addWidget(buttonTest);
 proxy->setPos(0,0);
 proxy->setVisible(true);
 //proxy->resize(64.0,640.0);
 proxy->show();*/
