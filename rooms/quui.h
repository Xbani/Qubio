#ifndef QUUI_H
#define QUUI_H

#include <QGraphicsScene>


/**
 * @brief The QuUI class
 * @details Basic UI Scene class
 */
class QuUI : public QGraphicsScene
{
public:
    QuUI();
    QuUI(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);
};

#endif // QUUI_H
