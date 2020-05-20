#ifndef QUBUTTONMULTI_H
#define QUBUTTONMULTI_H

#include <objects/ui/qubutton.h>


/**
 * @brief The QuButtonMulti class
 * @details The multiplayer button present in QuUIMainMenu.
 */
class QuButtonMulti : public QuButton
{
public:
    QuButtonMulti();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONSOLO_H
