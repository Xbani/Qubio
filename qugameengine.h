#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

#include <rooms/ui/quuimainmenu.h>
#include <rooms/ui/quuimultiplayer.h>

#include <QGraphicsView>



class QuGameEngine: public QObject
{
private:
    QuUIMainMenu * uiMainMenu;
    QuUIMultiplayer * uiMultiplayer;
    QGraphicsView * view;
public:
    QuGameEngine();
    ~QuGameEngine();

    void toUIMultiplayer();
    void toUIMainMenu();

    void create();

};

#endif // QUGAMEENGINE_H
