#ifndef QUBUTTONGOHOST_H
#define QUBUTTONGOHOST_H

#include <objects/ui/qubutton.h>



class QuButtonGoHost : public QuButton
{
public:
    QuButtonGoHost();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONGOHOST_H
