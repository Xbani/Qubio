#include "qubuttongojoin.h"

#include <QDebug>

#include <rooms/ui/quuijoin.h>

QuButtonGoJoin::QuButtonGoJoin():QuButton(12,13)
{

}

void QuButtonGoJoin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIJoin *uiJoin=dynamic_cast<QuUIJoin *>(scene());
    uiJoin->toUIWaitingRoom();
}
