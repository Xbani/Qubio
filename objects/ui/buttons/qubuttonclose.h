#ifndef QUBUTTONCLOSE_H
#define QUBUTTONCLOSE_H

#include <objects/ui/qubutton.h>



class QuButtonClose : public QuButton
{
public:
    QuButtonClose();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONCLOSE_H
