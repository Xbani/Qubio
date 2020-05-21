#include "qubuttongohost.h"

#include <QDebug>

QuButtonGoHost::QuButtonGoHost():QuButton(12,13)
{

}

void QuButtonGoHost::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "GoHost Clicked"; //TODO
}
