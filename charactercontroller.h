#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H
#include <QKeyEvent>
#include <QGraphicsView>

#include "objects/entities/quplayablecharacter.h"


class CharacterController : public QGraphicsView
{
    Q_OBJECT
private :
    QuPlayableCharacter playableCharacter;
public:
    CharacterController();
    void keyPressEvent(QKeyEvent* event);
};

#endif // CHARACTERCONTROLLER_H
