#include "qugame.h"

#include <QPainter>
#include <QuGameEngine.h>

#include <objects/blocks/qusolidblock.h>

#include <objects/entities/quplayablecharacter.h>



QuGame::QuGame(qreal x, qreal y, qreal width, qreal height, QObject *parent):QGraphicsScene(x,y,width,height,parent)
{
    if(parent!=nullptr){
        quGameEngine = dynamic_cast<QuGameEngine *>(parent);
    }

    init();
}

void QuGame::newMapFromJson(QJsonObject *jsonMap)
{

}

void QuGame::init()
{
    setBackgroundBrush(QBrush(QColor(39,39,68)));

    // create scene objects (pointers), object-> setPos(x,y), addItem(object);
    QuPlayableCharacter * mainCharacter = new QuPlayableCharacter(0);
    setFocusItem(mainCharacter);
    mainCharacter->setPos(300, 200);
    addItem(mainCharacter);

    QuSolidBlock* block;
    for(int i = 0 ; i < 16 ; ++i){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,7*QuObject::CELL_SIZE);
        addItem(block);
    }
    for(int i = 0 ; i < 16 ; i+=2){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,6*QuObject::CELL_SIZE);
        addItem(block);
    }
    for(int i = 0 ; i < 16 ; i+=4){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,5*QuObject::CELL_SIZE);
        addItem(block);
    }
    //top
    for(int i = 0 ; i < 16 ; ++i){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,0*QuObject::CELL_SIZE);
        addItem(block);
    }
    for(int i = 0 ; i < 16 ; i+=2){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,1*QuObject::CELL_SIZE);
        addItem(block);
    }
    for(int i = 0 ; i < 16 ; i+=4){
        block = new QuSolidBlock(1);
        block->setPos(i*QuObject::CELL_SIZE,2*QuObject::CELL_SIZE);
        addItem(block);
    }

}

void QuGame::createPlayers(QMap<int, QuPlayerInfo *> mapQuPlayerInfo)
{
    foreach(QuPlayerInfo* quPlayerInfo, mapQuPlayerInfo){
        //if (quGameEngine->getPlayerId() == )

    }
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
