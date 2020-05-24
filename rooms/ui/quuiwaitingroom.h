#ifndef QUUIWAITINGROOM_H
#define QUUIWAITINGROOM_H

#include <QJsonArray>
#include <QMap>

#include <rooms/quui.h>

#include <objects/ui/buttons/qubuttonclose.h>

#include <objects/ui/quplayerinfo.h>



class quUIWaitingRoom : public QuUI
{
    Q_OBJECT
private:
    QJsonArray * players_json;
    QMap<int,QuPlayerInfo *> player_info_map;
    QuButtonClose * button_close;

    bool is_host;

public:
    quUIWaitingRoom();
    quUIWaitingRoom(qreal x, qreal y, qreal width, qreal height, bool is_host, QObject * parent = nullptr);

    void toGame();
    void init();
    void setPlayersJSON(QJsonArray * players_json);
    void updatePlayerInfo();

    // QuUI interface
public:
    void back();

signals:
    void newPlayerList();
};

#endif // QUUIWAITINGROOM_H
