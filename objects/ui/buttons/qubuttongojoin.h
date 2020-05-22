#ifndef QUBUTTONGOJOIN_H
#define QUBUTTONGOJOIN_H

#include <objects/ui/qubutton.h>



class QuButtonGoJoin : public QuButton
{
public:
    QuButtonGoJoin();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONGOJOIN_H
