#include "charactercontroller.h"

#include <QDebug>

void CharacterController::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "LEFT";
    // Call functions on your character here.
       switch (event->key())
       {
       case Qt::Key_Right:
           //playableCharacter.moveLeft(); // For example
           qDebug() << "LEFT";
           break;
       case Qt::Key_Left:
           //playableCharacter.moveRight(); // For example
           qDebug() << "RIGHT";
           break;
       }

       // Otherwise pass to QGraphicsView.
       QGraphicsView::keyPressEvent(event);
}
