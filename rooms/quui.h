#ifndef QUUI_H
#define QUUI_H

#include <QGraphicsScene>

class QuGameEngine;
/**
 * @brief The QuUI class
 * @details Basic UI Scene class
 */
class QuUI : public QGraphicsScene
{
public:
    QuUI();
    QuUI(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    virtual void back()=0;
};

#endif // QUUI_H
