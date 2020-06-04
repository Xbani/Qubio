#include "qubuildermapframe.h"
#include "qumapbuilder.h"
#include "ui_qubuildermapframe.h"

#include <objects/enumblock/qulistblock.h>

#include <objects/quobject.h>

QuBuilderMapFrame::QuBuilderMapFrame(QGraphicsView *view, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuBuilderMapFrame)
{
    ui->setupUi(this);
    //ui->graphicsView = view;
    mapBuilder = new QuMapBuilder(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE);
   /* view->setScene(mapBuilder);
    view->show();*/
    ui->graphicsView->setScene(mapBuilder);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(39,39,68)));
    ui->graphicsView->show();
    init();
    mapBuilder->initMapBuilder();

}

QuBuilderMapFrame::~QuBuilderMapFrame()
{
    delete ui;
}

void QuBuilderMapFrame::init()
{
    QMenu *qMenu = new QMenu("Fichier",ui->menubar);
    QuListBlock quListBlock;
    signalMapper = new QSignalMapper(this);

    qMenu->addAction("Nouvelle Map");
    qMenu->addAction("Ouvrire Map");
    qMenu->addSeparator();
    qMenu->addAction("Enregistrer");
    qMenu->addAction("Enregistrer sous");
    qMenu->addSeparator();
    qMenu->addAction("Renomer");
    ui->menubar->addMenu(qMenu);


    qMenu = new QMenu("Block",ui->menubar);
    for(int numBlock = 0; numBlock < quListBlock.getNumberOfSolidBlock(); ++numBlock){
        QPixmap qPixmap(quListBlock.getBlockFile((QuListBlock::SolidBlock)numBlock));
        QAction *action = new QAction(QIcon(qPixmap.scaled(20,20)),
                        quListBlock.getBlockName((QuListBlock::SolidBlock)numBlock),this);
        action->connect(action,SIGNAL(triggered()),signalMapper,SLOT(map()));

        signalMapper->setMapping(action, numBlock);
        qMenu->addAction(action);
    }
    ui->menubar->addMenu(qMenu);
    connect(signalMapper, SIGNAL(mapped(int)),
                mapBuilder, SLOT(selectBlock(int)));

}

