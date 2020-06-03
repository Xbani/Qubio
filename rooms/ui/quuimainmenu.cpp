#include "quuimainmenu.h"

#include <QDebug>
#include <QPainter>
#include <iostream>
#include <qugameengine.h>
QuUIMainMenu::QuUIMainMenu()
{
    init();
}

QuUIMainMenu::QuUIMainMenu(qreal x, qreal y, qreal width, qreal height, QObject *parent):QuUI(x,y,width,height,parent)
{
    init();
}

void QuUIMainMenu::toUIMultiplayer()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toUIMultiplayer();
    }
}

void QuUIMainMenu::toUISolo()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toQuGame();
    }
}

void QuUIMainMenu::toBuilderMainFrame()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        game_engine->toBuilderMapFrame();
    }
}
void QuUIMainMenu::back()
{
    if(parent()!=nullptr){
        QuGameEngine * game_engine =dynamic_cast<QuGameEngine *>(parent());
        delete game_engine;
    }
}

QString QuUIMainMenu::getNickName()
{
    return text_box->getText();
}

int QuUIMainMenu::getColorHUE()
{
    return button_perso_color->getHUE();
}

void QuUIMainMenu::init()
{
    button_solo= new QuButtonSolo();
    button_multi= new QuButtonMulti();
    button_title= new QuButtonTitle();
    button_close= new QuButtonClose();
    button_perso_color= new QuButtonPersoColor();
    button_map_builder= new QuButtonMapBuilder();

    text_box= new QuTextBox();

    button_solo->setX(width()/3);
    button_solo->setY(height()/2);

    button_multi->setX(2*width()/3);
    button_multi->setY(height()/2);

    button_title->setX(width()/2);
    button_title->setY(height()/3);

    button_close->setX(7*width()/8);
    button_close->setY(height()/8);

    button_map_builder->setX(7*width()/8);
    button_map_builder->setY(7*height()/8);

    text_box->setX(width()/2);
    text_box->setY(4*height()/5);

    button_perso_color->setX(width()/2);
    button_perso_color->setY(height()/2);

    addItem(button_solo);
    addItem(button_multi);
    addItem(button_title);
    addItem(button_close);
    addItem(button_perso_color);
    addItem(button_map_builder);

    addItem(text_box);


    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuUIMainMenu::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
