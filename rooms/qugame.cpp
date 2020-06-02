#include "qugame.h"

#include <QPainter>

#include <objects/blocks/qusolidblock.h>

#include <objects/entities/quplayablecharacter.h>



QuGame::QuGame(qreal x, qreal y, qreal width, qreal height, QObject *parent):QGraphicsScene(x,y,width,height,parent)
{
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

    QuSolidBlock* block1 = new QuSolidBlock(1);
    block1->setPos(300,600);
    addItem(block1);

    QuSolidBlock* block2 = new QuSolidBlock(1);
    block2->setPos(380,600);
    addItem(block2);

    QuSolidBlock* block3 = new QuSolidBlock(1);
    block3->setPos(460,600);
    addItem(block3);

    QuSolidBlock* block4 = new QuSolidBlock(1);
    block4->setPos(540,600);
    addItem(block4);

    QuSolidBlock* block5 = new QuSolidBlock(1);
    block5->setPos(620,600);
    addItem(block5);

    QuSolidBlock* block6 = new QuSolidBlock(1);
    block6->setPos(700,600);
    addItem(block6);

    QuSolidBlock* block7 = new QuSolidBlock(1);
    block7->setPos(220,600);
    addItem(block7);

    QuSolidBlock* block8 = new QuSolidBlock(1);
    block8->setPos(140,600);
    addItem(block8);

    QuSolidBlock* block9 = new QuSolidBlock(1);
    block9->setPos(140,300);
    addItem(block9);

    QuSolidBlock* block10 = new QuSolidBlock(1);
    block10->setPos(140,520);
    addItem(block10);

    QuSolidBlock* block11 = new QuSolidBlock(1);
    block11->setPos(140,440);
    addItem(block11);

    QuSolidBlock* block12 = new QuSolidBlock(1);
    block12->setPos(140,200);
    addItem(block12);

    QuSolidBlock* block13 = new QuSolidBlock(1);
    block13->setPos(140,120);
    addItem(block13);

    QuSolidBlock* block14 = new QuSolidBlock(1);
    block14->setPos(140,360);
    addItem(block14);

    QuSolidBlock* block15 = new QuSolidBlock(1);
    block15->setPos(140,280);
    addItem(block15);

    QuSolidBlock* block16 = new QuSolidBlock(1);
    block16->setPos(780,600);
    addItem(block16);

    QuSolidBlock* block17 = new QuSolidBlock(1);
    block17->setPos(860,600);
    addItem(block17);

    QuSolidBlock* block18 = new QuSolidBlock(1);
    block18->setPos(940,600);
    addItem(block18);

    QuSolidBlock* block19 = new QuSolidBlock(1);
    block19->setPos(1020,600);
    addItem(block19);

    QuSolidBlock* block20 = new QuSolidBlock(1);
    block20->setPos(1100,600);
    addItem(block20);

    QuSolidBlock* block21  = new QuSolidBlock(1);
    block21->setPos(400,300);
    addItem(block21);

    QuSolidBlock* block22 = new QuSolidBlock(1);
    block22->setPos(500,520);
    addItem(block22);

    QuSolidBlock* block23 = new QuSolidBlock(1);
    block23->setPos(650,400);
    addItem(block23);

    QuSolidBlock* block24 = new QuSolidBlock(1);
    block24->setPos(1180,600);
    addItem(block24);

    QuSolidBlock* block25 = new QuSolidBlock(1);
    block25->setPos(1260,600);
    addItem(block25);

    QuSolidBlock* block26 = new QuSolidBlock(1);
    block26->setPos(1340,600);
    addItem(block26);

    QuSolidBlock* block27 = new QuSolidBlock(1);
    block27->setPos(1420,600);
    addItem(block27);

    QuSolidBlock* block28 = new QuSolidBlock(1);
    block28->setPos(1500,600);
    addItem(block28);

    QuSolidBlock* block29 = new QuSolidBlock(1);
    block29->setPos(1580,600);
    addItem(block29);

    QuSolidBlock* block30 = new QuSolidBlock(1);
    block30->setPos(1660,600);
    addItem(block30);

    QuSolidBlock* block31 = new QuSolidBlock(1);
    block31->setPos(1740,600);
    addItem(block31);

    QuSolidBlock* block32 = new QuSolidBlock(1);
    block32->setPos(1820,600);
    addItem(block32);

    QuSolidBlock* block33 = new QuSolidBlock(1);
    block33->setPos(1900,600);
    addItem(block33);

    QuSolidBlock* block34 = new QuSolidBlock(1);
    block34->setPos(1980,600);
    addItem(block34);

    QuSolidBlock* block35 = new QuSolidBlock(1);
    block35->setPos(2060,600);
    addItem(block35);

    QuSolidBlock* block36 = new QuSolidBlock(1);
    block36->setPos(2140,600);
    addItem(block36);

    QuSolidBlock* block37 = new QuSolidBlock(1);
    block37->setPos(2220,600);
    addItem(block37);

    QuSolidBlock* block38 = new QuSolidBlock(1);
    block38->setPos(2300,600);
    addItem(block38);
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
