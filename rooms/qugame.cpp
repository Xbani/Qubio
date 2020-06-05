#include "qugame.h"

#include <QJsonArray>
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

void QuGame::newMapFromJson(QJsonObject *mapJson)
{
    QJsonArray sizeArray = (*mapJson)["size"].toArray();
    QRectF qRectF;
    qRectF.setWidth(sizeArray[0].toInt()* QuObject::CELL_SIZE);
    qRectF.setHeight(sizeArray[1].toInt()* QuObject::CELL_SIZE);
    setSceneRect(qRectF);
    QJsonArray blocksArray = (*mapJson)["blocks"].toArray();
    int arrayPos = 0;
    for(arrayPos = 0; arrayPos < blocksArray.size(); arrayPos++) {
        QJsonObject jsonBlock = blocksArray[arrayPos].toObject();
        QJsonArray coordsArray = jsonBlock["coords"].toArray();
        int blockNumber = 0;
        for(blockNumber = 0; blockNumber < coordsArray.size(); blockNumber++) {
            QuSolidBlock* solidBlock = new QuSolidBlock(jsonBlock["blockType"].toInt());
            QJsonArray blockCoordsArray = coordsArray[blockNumber].toArray();
            int blockX = blockCoordsArray[0].toInt();
            int blockY = blockCoordsArray[1].toInt();
            solidBlock->setPos(blockX * QuObject::CELL_SIZE, blockY * QuObject::CELL_SIZE);
            addItem(solidBlock);
        }
    }
}

void QuGame::init()
{
    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuGame::createPlayers(QMap<int, QuPlayerInfo *> mapQuPlayerInfo)
{
    int nb = 1;
    foreach(QuPlayerInfo* quPlayerInfo, mapQuPlayerInfo){
        if (quGameEngine->getPlayerId() == quPlayerInfo->getPlayerId()){
            QuPlayableCharacter * mainCharacter = new QuPlayableCharacter(quPlayerInfo->getPlayerId(), quPlayerInfo->getPlayerHue());
            playable_character = mainCharacter;
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

QuPlayableCharacter *QuGame::getPlayableCharacter()
{
    return playable_character;
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
