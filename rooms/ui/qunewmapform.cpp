#include "qunewmapform.h"
#include "ui_qunewmapform.h"

QuNewMapForm::QuNewMapForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuNewMapForm)
{
    ui->setupUi(this);
}

QuNewMapForm::~QuNewMapForm()
{
    delete ui;
}

QString QuNewMapForm::getMapName()
{
    return ui->mapName->text();
}

QSize QuNewMapForm::getMapSize()
{
    QSize size;
    size.setHeight(ui->height->text().toInt());
    size.setWidth(ui->width->text().toUInt());
    return size;
}
