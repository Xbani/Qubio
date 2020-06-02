#include "quuiwaitingroom.h"

#include <qugameengine.h>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


QuUIWaitingRoom::QuUIWaitingRoom()
{
    init();
}

QuUIWaitingRoom::QuUIWaitingRoom(qreal x, qreal y, qreal width, qreal height, bool is_host, QObject *parent):QuUI(x,y,width,height,parent)
{
    this->is_host=is_host;
    init();
}

void QuUIWaitingRoom::toGame()
{
    qDebug() << "toGame !";
}

void QuUIWaitingRoom::init()
{
    button_close= new QuButtonClose();

    button_close->setX(7*width()/8);
    button_close->setY(height()/8);

    addItem(button_close);

    setBackgroundBrush(QBrush(QColor(39,39,68)));

    connect(this,&QuUIWaitingRoom::newPlayerList,this,&QuUIWaitingRoom::updatePlayerInfo);
}

void QuUIWaitingRoom::setPlayersJSON(QJsonArray *players_json)
{
    this->players_json=players_json;
    emit newPlayerList();
}


void QuUIWaitingRoom::updatePlayerInfo()
{
    player_info_map.clear();
    int i;
    for(i=0 ; i < players_json->size() ; ++i){
        QJsonObject playerJson = QJsonValue(players_json[i]).toObject();
        QuPlayerInfo* player_info= new QuPlayerInfo(playerJson["nickname"].toString(),playerJson["skin"].toDouble());
        player_info_map.insert(playerJson["playerId"].toInt(),player_info);
    }

}

void QuUIWaitingRoom::back()
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