#include "qubuttonsolo.h"

#include <QDebug>

QuButtonSolo::QuButtonSolo():QuButton(3,4)
{

}

void QuButtonSolo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Solo Clicked"; //TODO
}
