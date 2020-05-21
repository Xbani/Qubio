#ifndef QUBUTTONHOST_H
#define QUBUTTONHOST_H

#include <objects/ui/qubutton.h>



class QuButtonHost : public QuButton
{
public:
    QuButtonHost();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONHOST_H
