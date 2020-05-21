#include "quuimultiplayer.h"

#include <QPainter>
#include <qugameengine.h>

QuUIMultiplayer::QuUIMultiplayer()
{
    init();
}

QuUIMultiplayer::QuUIMultiplayer(qreal x, qreal y, qreal width, qreal height, QObject *parent):QuUI(x,y,width,height,parent)
{
    init();
}

void QuUIMultiplayer::back()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toUIMainMenu();
    }
}

void QuUIMultiplayer::init(){
    button_host= new QuButtonHost();
    button_join= new QuButtonJoin();
    button_close= new QuButtonClose();

    button_host->setX(width()/2);
    button_host->setY(2*height()/4);

    button_join->setX(width()/2);
    button_join->setY(3*height()/4);

    button_close->setX(7*width()/8);
    button_close->setY(height()/8);

    addItem(button_host);
    addItem(button_join);
    addItem(button_close);

    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuUIMultiplayer::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
