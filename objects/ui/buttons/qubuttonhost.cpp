#include "qubuttonhost.h"

#include <QDebug>

QuButtonHost::QuButtonHost():QuButton(8,9)
{

}

void QuButtonHost::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Host Clicked"; //TODO
}
