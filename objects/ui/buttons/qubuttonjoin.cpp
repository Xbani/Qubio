#include "qubuttonjoin.h"

#include <QDebug>

QuButtonJoin::QuButtonJoin():QuButton(6,7)
{

}

void QuButtonJoin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Join Clicked"; //TODO
}
