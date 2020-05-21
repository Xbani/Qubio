#include "qubuttonclose.h"

#include <rooms/quui.h>

QuButtonClose::QuButtonClose():QuButton(10,11)
{

}

void QuButtonClose::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUI * ui=dynamic_cast<QuUI *>(scene());
    ui->back();
}
