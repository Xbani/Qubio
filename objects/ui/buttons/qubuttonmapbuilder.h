#ifndef QUBUTTONMAPBUILDER_H
#define QUBUTTONMAPBUILDER_H

#include <objects/ui/qubutton.h>



class QuButtonMapBuilder : public QuButton
{
public:
    QuButtonMapBuilder();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONMAPBUILDER_H
