#ifndef QUBUTTONJOIN_H
#define QUBUTTONJOIN_H

#include <objects/ui/qubutton.h>



class QuButtonJoin : public QuButton
{
public:
    QuButtonJoin();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONJOIN_H
