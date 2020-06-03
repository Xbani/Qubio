#include "quunplayablecharacter.h"
#include "quphysicsconst.h"

#include "qucharacter.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGuiApplication>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <iostream>
#include <QtMath>

#include <QJsonObject>


QuUnplayableCharacter::QuUnplayableCharacter(int instance_id):QuCharacter(instance_id)
{

}

int QuUnplayableCharacter::getClassId()
{
    return QuEntity::UNPLAYABLE_CHARACTER_ID;
}

void QuUnplayableCharacter::advance(int step)
{
    if (!step)
        return;
}
