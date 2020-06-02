#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

//#include <rooms/ui/quuihost.h>
//#include <rooms/ui/quuijoin.h>
//#include <rooms/ui/quuimainmenu.h>
//#include <rooms/ui/quuimultiplayer.h>

#include <QGraphicsView>

#include <network/client/qusocketclient.h>

class QuUIMainMenu;
class QuUIMultiplayer;
class QuUIHost;
class QuUIJoin;
class QuUIWaitingRoom;
class QuGame;
class QuClient;
class QHostAddress;

class QuGameEngine: public QObject
{
    Q_OBJECT
private:
    QuUIMainMenu * uiMainMenu;
    QuUIMultiplayer * uiMultiplayer;
    QuUIHost * uiHost;
    QuUIJoin * uiJoin;
    QuUIWaitingRoom * uiWaitingRoomHost;
    QuUIWaitingRoom * uiWaitingRoomJoin;

    QuGame *quGame;

    QuClient *quClient;

    QGraphicsView * view;

    int playerId;
    bool isHost;

public:
    QuGameEngine();
    ~QuGameEngine();

    void toUIMultiplayer();
    void toUIMainMenu();
    void toUIHost();
    void toUIJoin();
    void toQuGame();
    void fromUIJoinToWaitingRoom();
    void fromUIHostToWaitingRoom();

    QHostAddress getIpJoin();
    int getPortJoin();

    QString getIpHost();
    QString getPortHost();

    void create();

    inline QuGame* getQuGame() const {return quGame;};
    inline int getPlayerId() const {return playerId;};
    inline void setPlayerId(int playerId) {this->playerId = playerId;};
    inline bool getIsHost() const {return isHost;};
    inline void setIsHost(int isHost) {this->isHost = isHost;};

    inline QString getNickname()const {return "todo getNickname in quGameEngine";};
    inline float getSkinColor() const {return 76.3;};
};

#endif // QUGAMEENGINE_H
