#include "qubuttonjoin.h"

#include <QDebug>

#include <rooms/ui/quuimultiplayer.h>

QuButtonJoin::QuButtonJoin():QuButton(6,7)
{

}

void QuButtonJoin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMultiplayer *uiMultiplayer=dynamic_cast<QuUIMultiplayer *>(scene());
    uiMultiplayer->toUIJoin();
}
