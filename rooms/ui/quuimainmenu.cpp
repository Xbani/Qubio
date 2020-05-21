#include "quuimainmenu.h"

#include <QDebug>
#include <QPainter>
#include <iostream>
QuUIMainMenu::QuUIMainMenu()
{
    init();
}

QuUIMainMenu::QuUIMainMenu(qreal x, qreal y, qreal width, qreal height, QObject *parent):QuUI(x,y,width,height)
{
    init();
}

void QuUIMainMenu::init()
{
    button_solo= new QuButtonSolo();
    button_multi= new QuButtonMulti();
    button_title= new QuButtonTitle();
    text_box= new QuTextBox();

    button_solo->setX(width()/3);
    button_solo->setY(height()/2);

    button_multi->setX(2*width()/3);
    button_multi->setY(height()/2);

    button_title->setX(width()/2);
    button_title->setY(height()/3);

    text_box->setX(width()/2);
    text_box->setY(4*height()/5);

    addItem(button_solo);
    addItem(button_multi);
    addItem(button_title);
    addItem(text_box);

    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuUIMainMenu::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
