#include "mainwindow.h"

#include "objects\quobject.h"
#include "objects\quentity.h"
#include "objects\qublock.h"
#include "objects\\blocks\qusolidblock.h"
#include "objects\\entities\quplayablecharacter.h"
#include "objects\\entities\quunplayablecharacter.h"

#include <QApplication>
#include <QtWidgets>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene(0 ,0 , 1000, 1000);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    // create scene objects (pointers), object-> setPos(x,y), scene.addItem(object);
    QuPlayableCharacter* mainCharacter = new QuPlayableCharacter();
    mainCharacter->setPos(300, 200);
    scene.addItem(mainCharacter);

    QuCharacter* character = new QuUnplayableCharacter();
    character->setPos(700, 200);
    scene.addItem(character);

    QuSolidBlock* block1 = new QuSolidBlock(1);
    block1->setPos(300,600);
    scene.addItem(block1);

    QuSolidBlock* block2 = new QuSolidBlock(1);
    block2->setPos(380,600);
    scene.addItem(block2);

    QuSolidBlock* block3 = new QuSolidBlock(1);
    block3->setPos(460,600);
    scene.addItem(block3);

    QuSolidBlock* block4 = new QuSolidBlock(1);
    block4->setPos(540,600);
    scene.addItem(block4);

    QuSolidBlock* block5 = new QuSolidBlock(1);
    block5->setPos(620,600);
    scene.addItem(block5);

    QuSolidBlock* block6 = new QuSolidBlock(1);
    block6->setPos(700,600);
    scene.addItem(block6);

    QuSolidBlock* block7 = new QuSolidBlock(1);
    block7->setPos(220,600);
    scene.addItem(block7);

    QuSolidBlock* block8 = new QuSolidBlock(1);
    block8->setPos(140,600);
    scene.addItem(block8);

    QuSolidBlock* block9 = new QuSolidBlock(1);
    block9->setPos(140,300);
    scene.addItem(block9);

    QuSolidBlock* block10 = new QuSolidBlock(1);
    block10->setPos(140,520);
    scene.addItem(block10);

    QuSolidBlock* block11 = new QuSolidBlock(1);
    block11->setPos(140,440);
    scene.addItem(block11);

    QuSolidBlock* block12 = new QuSolidBlock(1);
    block12->setPos(140,200);
    scene.addItem(block12);

    QuSolidBlock* block13 = new QuSolidBlock(1);
    block13->setPos(140,120);
    scene.addItem(block13);

    QuSolidBlock* block14 = new QuSolidBlock(1);
    block14->setPos(140,360);
    scene.addItem(block14);

    QuSolidBlock* block15 = new QuSolidBlock(1);
    block15->setPos(140,280);
    scene.addItem(block15);

    QuSolidBlock* block16 = new QuSolidBlock(1);
    block16->setPos(780,600);
    scene.addItem(block16);

    QuSolidBlock* block17 = new QuSolidBlock(1);
    block17->setPos(860,600);
    scene.addItem(block17);

    QuSolidBlock* block18 = new QuSolidBlock(1);
    block18->setPos(940,600);
    scene.addItem(block18);

    QuSolidBlock* block19 = new QuSolidBlock(1);
    block19->setPos(1020,600);
    scene.addItem(block19);

    QuSolidBlock* block20 = new QuSolidBlock(1);
    block20->setPos(1100,600);
    scene.addItem(block20);

    QuSolidBlock* block21  = new QuSolidBlock(1);
    block21->setPos(400,300);
    scene.addItem(block21);

    QuSolidBlock* block22 = new QuSolidBlock(1);
    block22->setPos(500,520);
    scene.addItem(block22);

    QuSolidBlock* block23 = new QuSolidBlock(1);
    block23->setPos(650,400);
    scene.addItem(block23);

    // create view
    QGraphicsView view(&scene);
    view.setBackgroundBrush(Qt::black);
    view.show();

    //boucle
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 60);

    return app.exec();
}
