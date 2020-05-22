#include "qubuttonhost.h"

#include <QDebug>

#include <rooms/ui/quuimultiplayer.h>

QuButtonHost::QuButtonHost():QuButton(8,9)
{

}

void QuButtonHost::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMultiplayer *uiMultiplayer=dynamic_cast<QuUIMultiplayer *>(scene());
    uiMultiplayer->toUIHost();
}
