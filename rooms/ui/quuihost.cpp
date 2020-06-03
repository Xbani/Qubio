#include "quuihost.h"

#include <qugameengine.h>

QuUIHost::QuUIHost()
{
    init();
}

QuUIHost::QuUIHost(qreal x, qreal y, qreal width, qreal height, QObject *parent):QuUI(x,y,width,height,parent)
{
    init();
}

void QuUIHost::toUIWaitingRoom()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->fromUIHostToWaitingRoom();
    }
}

void QuUIHost::back()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toUIMultiplayer();
    }
}

QString QuUIHost::getIp()
{
    QString full_text=text_box_ip->getText();
    if(full_text.contains(":")){
        QString ip= full_text;
        while (!ip.endsWith(":")) {
            ip.chop(1);
        }
        ip.chop(1);
    }
    return full_text;
}
QString QuUIHost::getPort(){
    qDebug() << "Host : getPort";
    QString full_text=text_box_ip->getText();
    if(full_text.contains(":")){
        QString ip= full_text;
        while (!ip.startsWith(":")) {
            ip.remove(0,1);
        }
        ip.remove(0,1);
        return ip;
    }
    return "26676";
}

void QuUIHost::init()
{
    button_go= new QuButtonGoHost();
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

void QuUIHost::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
