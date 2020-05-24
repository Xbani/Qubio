#include "quuiwaitingroom.h"

#include <qugameengine.h>
#include <QDebug>


quUIWaitingRoom::quUIWaitingRoom()
{
    init();
}

quUIWaitingRoom::quUIWaitingRoom(qreal x, qreal y, qreal width, qreal height, bool is_host, QObject *parent):QuUI(x,y,width,height,parent)
{
    this->is_host=is_host;
    init();
}

void quUIWaitingRoom::toGame()
{
    qDebug() << "toGame !";
}

void quUIWaitingRoom::init()
{
    button_close= new QuButtonClose();

    button_close->setX(7*width()/8);
    button_close->setY(height()/8);

    addItem(button_close);

    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void quUIWaitingRoom::setPlayersJSON(QJsonArray *players_json)
{
    this->players_json=players_json;
}


void quUIWaitingRoom::updatePlayerInfo()
{
    player_info_map.clear();
    int i;
    for(i=0 ; i < players_json->size() ; ++i){
        QJsonArray player_json=players_json[i];
        QuPlayerInfo* player_info= new QuPlayerInfo(player_json[1].toString(),player_json[2].toDouble());
        player_info_map.insert(player_json[0].toInt(),player_info);
    }

}

void quUIWaitingRoom::back()
{
    if(is_host){
        if(parent()!=nullptr){
            QuGameEngine * game_engine = dynamic_cast<QuGameEngine *>(parent());
            game_engine->toUIHost();
        }
    }
    else{
        if(parent()!=nullptr){
            QuGameEngine * game_engine = dynamic_cast<QuGameEngine *>(parent());
            game_engine->toUIJoin();
        }
    }
}
