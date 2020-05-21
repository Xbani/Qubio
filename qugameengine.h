#ifndef QUGAMEENGINE_H
#define QUGAMEENGINE_H

#include <rooms/ui/quuimainmenu.h>

#include <QGraphicsView>



class QuGameEngine
{
private:
    QuUIMainMenu * uiMainMenu;
    QGraphicsView * view;
public:
    QuGameEngine();

    void create();
};

#endif // QUGAMEENGINE_H
