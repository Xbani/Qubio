#include "qubuttongohost.h"

#include <QDebug>

#include <rooms/ui/quuihost.h>

QuButtonGoHost::QuButtonGoHost():QuButton(12,13)
{

}

void QuButtonGoHost::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIHost *uiHost=dynamic_cast<QuUIHost *>(scene());
    uiHost->toUIWaitingRoom();
}
