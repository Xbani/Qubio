#include "qubuttongogame.h"

#include <QDebug>

QuButtonGoGame::QuButtonGoGame():QuButtonGoGame(false)
{

}

QuButtonGoGame::QuButtonGoGame(bool is_host):QuButton(12,13)
{
    this->is_host=is_host;
    if(!is_host){
        sprite=sprite_hover;
    }
}

void QuButtonGoGame::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_host){
        qDebug() << "GoGame as Host"; //TODO
    }
    else{
       qDebug() << "GoGame as no host"; //TODO
    }
}
