#include "qubuttongojoin.h"

#include <QDebug>

QuButtonGoJoin::QuButtonGoJoin():QuButton(12,13)
{

}

void QuButtonGoJoin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "GoJoin Clicked"; //TODO
}
