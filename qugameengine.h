#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

//#include <rooms/ui/quuihost.h>
//#include <rooms/ui/quuijoin.h>
//#include <rooms/ui/quuimainmenu.h>
//#include <rooms/ui/quuimultiplayer.h>

#include <QGraphicsView>

class QuUIMainMenu;
class QuUIMultiplayer;
class QuUIHost;
class QuUIJoin;
class QuGame;
class QuGameEngine: public QObject
{
    Q_OBJECT
private:
    QuUIMainMenu * uiMainMenu;
    QuUIMultiplayer * uiMultiplayer;
    QuUIHost * uiHost;
    QuUIJoin * uiJoin;
    QuGame *quGame;

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

    void create();

    inline QuGame* getQuGame() const {return quGame;};
    inline int getPlayerId() const {return playerId;};
    inline void setPlayerId(int playerId) {this->playerId = playerId;};
    inline bool getIsHost() const {return isHost;};
    inline void setIsHost(int isHost) {this->isHost = isHost;};

};

#endif // QUGAMEENGINE_H
