#include "qutextbox.h"

#include <QJsonObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
QuTextBox::QuTextBox()
{
    QString path=QString(":/resources/sprites/ui/textbox.png");
    sprite=QImage(path);
    text="";
    setFlags(ItemIsFocusable);
    setFocus();

}

QuTextBox::QuTextBox(QString default_text):QuTextBox()
{
    text=default_text;
}

QString QuTextBox::getText()
{
    return text;
}

QRectF QuTextBox::boundingRect() const
{
    QSize sprite_size=sprite.size();
    return QRectF(-sprite_size.width()*QuObject::PIXEL_SIZE/2,
                  -sprite_size.height()*QuObject::PIXEL_SIZE/2,
                  sprite_size.width()*QuObject::PIXEL_SIZE,
                  sprite_size.height()*QuObject::PIXEL_SIZE);
}

void QuTextBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSize sprite_size=sprite.size();

    painter->drawImage(boundingRect(),sprite,sprite.rect());

    painter->setFont(QFont("Sans Serif", 42));
    painter->drawText(boundingRect().bottomLeft(),text);
}

QJsonObject QuTextBox::toJSON()
{
    return QJsonObject(); //nothing to do
}
void QuTextBox::fromJSON(QJsonObject qJsonObject)
{
    //nothing to do
}

void QuTextBox::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    if (key>=Qt::Key_A && key<=Qt::Key_Z && text.size()< MAX_TEXT_SIZE){
        text.append(event->text());
    }
    else if (key>=Qt::Key_0 && key<=Qt::Key_9 && text.size()< MAX_TEXT_SIZE){
        text.append(event->text());
    }
    else if(key==Qt::Key_Space && text.size()>0){
         text.append(" ");
    }
    else if(key==Qt::Key_Period && text.size()>0){
         text.append(".");
    }
    else if (key==Qt::Key_Colon && text.size()>0){
        text.append(":");
    }
    else if(key==Qt::Key_Backspace && text.size()>0){
        text.chop(1);
    }
    update(boundingRect());
}
