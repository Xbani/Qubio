#include "qubuildermapframe.h"
#include "qumapbuilder.h"
#include "ui_qubuildermapframe.h"

#include <objects/enumblock/qulistblock.h>

#include <objects/quobject.h>

#include <rooms/ui/qunewmapform.h>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

QuBuilderMapFrame::QuBuilderMapFrame(QGraphicsView *view, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuBuilderMapFrame)
{
    ui->setupUi(this);
    mapBuilder = new QuMapBuilder(0,0,128*QuObject::PIXEL_SIZE,64*QuObject::PIXEL_SIZE);
    ui->graphicsView->setScene(mapBuilder);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(39,39,68)));
    ui->graphicsView->show();
    init();

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

    QAction *action = new QAction("Nouvelle Map",qMenu);
    qMenu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(newMap()));

    action = new QAction("Ouvrire Map",qMenu);
    qMenu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(openMap()));

    qMenu->addSeparator();
    action = new QAction("Enregistrer",qMenu);
    qMenu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(save()));

    action = new QAction("Enregistrer sous",qMenu);
    qMenu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(saveUnder()));

    qMenu->addSeparator();
    action = new QAction("Renomer",qMenu);
    qMenu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(rename()));

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

    //use a signalMapper for call a slot whith a param
    connect(signalMapper, SIGNAL(mapped(int)), mapBuilder, SLOT(selectBlock(int)));

}

void QuBuilderMapFrame::openMap()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    //qDebug()<<in.readAll().toUtf8();
    //jsonDoc.fromJson();
    file.close();
    qDebug()<<jsonDoc.toJson(QJsonDocument::Compact);
    QJsonObject *jsonObj = new QJsonObject(jsonDoc.object());
    mapBuilder->mapFromJson(jsonObj);
    delete(jsonObj);
}

void QuBuilderMapFrame::newMap()
{
    QuNewMapForm *newMapForm = new QuNewMapForm();
    if (newMapForm->exec()){
        mapBuilder->createNewMap(newMapForm->getMapName(), newMapForm->getMapSize());
    }
    delete (newMapForm);
}

void QuBuilderMapFrame::save()
{
    QString fileName = mapBuilder->getMapName();
    fileName += ".qumap";
    QDir dirSaves(QCoreApplication::applicationDirPath() + "/saves");
    if(!dirSaves.exists()){
        dirSaves.mkdir(QCoreApplication::applicationDirPath() + "/saves");
    }
    QFile file(QCoreApplication::applicationDirPath() + "/saves/" + fileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QTextStream out(&file);
    QJsonObject *jsonMap = mapBuilder->mapToJson();
    QJsonDocument jsonDoc(*jsonMap);
    out << jsonDoc.toJson(QJsonDocument::Compact);
    delete(jsonMap);
}

void QuBuilderMapFrame::saveUnder()
{
    QMessageBox::information(this, tr("info"),
                         tr("not implement"));
}

void QuBuilderMapFrame::rename()
{
    QMessageBox::information(this, tr("info"),
                         tr("not implement"));
}

