#include "qubuttonmulti.h"

#include <QDebug>

QuButtonMulti::QuButtonMulti():QuButton(1,2)
{

}

void QuButtonMulti::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Multi Clicked"; //TODO
}
