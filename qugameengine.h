#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

#include <rooms/ui/quuihost.h>
#include <rooms/ui/quuimainmenu.h>
#include <rooms/ui/quuimultiplayer.h>

#include <QGraphicsView>



class QuGameEngine: public QObject
{
private:
    QuUIMainMenu * uiMainMenu;
    QuUIMultiplayer * uiMultiplayer;
    QuUIHost * uiHost;

    QGraphicsView * view;
public:
    QuGameEngine();
    ~QuGameEngine();

    void toUIMultiplayer();
    void toUIMainMenu();
    void toUIHost();

    void create();

};

#endif // QUGAMEENGINE_H
