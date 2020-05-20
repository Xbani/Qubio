#ifndef QUBUTTONTITLE_H
#define QUBUTTONTITLE_H

#include <objects/ui/qubutton.h>


/**
 * @brief The QuButtonTitle class
 * @details The Qubio's Title, click on it, and it will be open the game website on your navigator
 */
class QuButtonTitle : public QuButton
{
public:
    QuButtonTitle();
    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONTITLE_H
