#include "qubuttonsolo.h"

#include <QDebug>

#include <rooms/ui/quuimainmenu.h>

QuButtonSolo::QuButtonSolo():QuButton(3,4)
{

}

void QuButtonSolo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMainMenu * uiMainMenu=dynamic_cast<QuUIMainMenu *>(scene());
    uiMainMenu->toUISolo();
}
