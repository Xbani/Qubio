#include "qugame.h"

#include <QPainter>
#include <qugameengine.h>

#include <objects/blocks/qusolidblock.h>

#include <objects/entities/quplayablecharacter.h>

#include <objects/entities/quunplayablecharacter.h>

#include <objects/ui/quplayerinfo.h>

#include <network/client/quclient.h>



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
    int nb = 0;
    foreach(QuPlayerInfo* quPlayerInfo, mapQuPlayerInfo){
        if (quGameEngine->getPlayerId() == quPlayerInfo->getPlayerId()){
            QuPlayableCharacter * mainCharacter = new QuPlayableCharacter(quPlayerInfo->getPlayerId(), quPlayerInfo->getPlayerHue());
            setFocusItem(mainCharacter);
            mainCharacter->setPos(nb*2*QuObject::CELL_SIZE, 3*QuObject::CELL_SIZE);
            addItem(mainCharacter);
            entities.insert(quPlayerInfo->getPlayerId(),mainCharacter);
        }else{
            QuUnplayableCharacter *character = new QuUnplayableCharacter(quPlayerInfo->getPlayerId(), quPlayerInfo->getPlayerHue());
            character->setPos(nb*2*QuObject::CELL_SIZE, 3*QuObject::CELL_SIZE);
            addItem(character);
            entities.insert(quPlayerInfo->getPlayerId(),character);
        }
        ++nb;
    }
}

void QuGame::sentToServer(QJsonObject *jsonToSent)
{
    quGameEngine->getQuClient()->sendEntity(jsonToSent);
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
