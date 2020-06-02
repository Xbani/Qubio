#include "qugame.h"

#include <QPainter>

QuGame::QuGame()
{
    init();
}

void QuGame::newMapFromJson(QJsonObject *jsonMap)
{

}

void QuGame::init()
{
    setBackgroundBrush(QBrush(QColor(39,39,68)));
}

void QuGame::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush=QBrush(backgroundBrush());
    painter->fillRect(rect,brush);
}
