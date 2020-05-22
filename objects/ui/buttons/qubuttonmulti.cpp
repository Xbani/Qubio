#include "qubuttonmulti.h"

#include <QDebug>

#include <rooms/ui/quuimainmenu.h>

QuButtonMulti::QuButtonMulti():QuButton(1,2)
{

}

void QuButtonMulti::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMainMenu * uiMainMenu=dynamic_cast<QuUIMainMenu *>(scene());
    uiMainMenu->toUIMultiplayer();
}
