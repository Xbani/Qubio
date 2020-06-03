#include "qugame.h"

#include <QPainter>
#include <qugameengine.h>

#include <objects/blocks/qusolidblock.h>

#include <objects/entities/quplayablecharacter.h>

#include <objects/entities/quunplayablecharacter.h>

#include <objects/ui/quplayerinfo.h>



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
    int nbUnplayble = 0;
    foreach(QuPlayerInfo* quPlayerInfo, mapQuPlayerInfo){
        if (quGameEngine->getPlayerId() == quPlayerInfo->getPlayerId()){
            QuPlayableCharacter * mainCharacter = new QuPlayableCharacter(quPlayerInfo->getPlayerId());
            setFocusItem(mainCharacter);
            mainCharacter->setPos(300, 200);
            addItem(mainCharacter);
        }else{
            ++nbUnplayble;
            QuUnplayableCharacter *character = new QuUnplayableCharacter(quPlayerInfo->getPlayerId());
            character->setPos(300, 200);
            addItem(character);
        }

    }
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
