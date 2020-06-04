﻿#include "qumapbuilder.h"

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
    blockSelected = 0;
    mousePressed = false;
    mouseMoved = false;
    initMapBuilder();
}

void QuMapBuilder::selectBlock(int block)
{
    qDebug()<<block;
    blockSelected = block;
}

void QuMapBuilder::mapFromJson(QJsonObject *mapJson)
{

}

QJsonObject *QuMapBuilder::mapToJson()
{
    return new QJsonObject();
}

void QuMapBuilder::createNewMap(QString mapName, QSize mapSize)
{
    this->mapName = mapName;
    clearScene();
    resizeScene(mapSize);
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
        //if in the map
        if (pos.rx() >= 0 && pos.rx() <= mapSize.width()*QuBlock::CELL_SIZE &&
                pos.ry() >= 0 && pos.ry() <= mapSize.height()*QuBlock::CELL_SIZE){
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
        }
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

QSize QuMapBuilder::getMapSize() const
{
    return mapSize;
}

QString QuMapBuilder::getMapName() const
{
    return mapName;
}

void QuMapBuilder::initMapBuilder()
{
    resizeScene(QSize(20,10));
}

void QuMapBuilder::clearScene()
{
    QList<QGraphicsItem*> listItem = items();
    for(int itemI = 0; itemI < listItem.size(); ++itemI){
        QGraphicsItem *myItem = listItem.at(itemI);
        removeItem(myItem);
        delete(myItem);
    }
}

void QuMapBuilder::resizeScene(QSize mapSize)
{
    this->mapSize = mapSize;
    setSceneRect(0,0,QuObject::CELL_SIZE*mapSize.width(),QuObject::CELL_SIZE*mapSize.height());

    for (int i = 0; i <= mapSize.height(); ++i){
        addLine(0,i*QuObject::CELL_SIZE,mapSize.width()*QuObject::CELL_SIZE,i*QuObject::CELL_SIZE,QPen(QColor(0,255,255)));
    }

    for (int i = 0; i <= mapSize.width(); ++i){
        addLine(i*QuObject::CELL_SIZE,0,i*QuObject::CELL_SIZE,mapSize.height()*QuObject::CELL_SIZE,QPen(QColor(0,255,255)));
    }
}

/* QPushButton *buttonTest = new QPushButton("clickMe");
 QGraphicsProxyWidget *proxy =this->addWidget(buttonTest);
 proxy->setPos(0,0);
 proxy->setVisible(true);
 //proxy->resize(64.0,640.0);
 proxy->show();*/
