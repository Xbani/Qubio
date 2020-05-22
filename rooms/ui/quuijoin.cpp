#include "quuijoin.h"

#include <qugameengine.h>

QuUIJoin::QuUIJoin()
{
    init();
}

QuUIJoin::QuUIJoin(qreal x, qreal y, qreal width, qreal height, QObject *parent):QuUI(x,y,width,height,parent)
{
    init();
}

void QuUIJoin::back()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toUIMultiplayer();
    }
}

void QuUIJoin::init()
{
    button_go= new QuButtonGoJoin();
    button_close= new QuButtonClose();
    text_box_ip= new QuTextBox("localhost");

    button_go->setX(width()/2);
    button_go->setY(3*height()/4);

    button_close->setX(7*width()/8);
    button_close->setY(height()/8);

    text_box_ip->setX(width()/2);
    text_box_ip->setY(height()/2);

    addItem(button_go);
    addItem(button_close);
    addItem(text_box_ip);

    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuUIJoin::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
