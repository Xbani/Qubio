#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

#include <rooms/ui/quuihost.h>
#include <rooms/ui/quuijoin.h>
#include <rooms/ui/quuimainmenu.h>
#include <rooms/ui/quuimultiplayer.h>

#include <QGraphicsView>



class QuGameEngine: public QObject
{
private:
    QuUIMainMenu * uiMainMenu;
    QuUIMultiplayer * uiMultiplayer;
    QuUIHost * uiHost;
    QuUIJoin * uiJoin;

    QGraphicsView * view;
public:
    QuGameEngine();
    ~QuGameEngine();

    void toUIMultiplayer();
    void toUIMainMenu();
    void toUIHost();
    void toUIJoin();

    void create();

};

#endif // QUGAMEENGINE_H
