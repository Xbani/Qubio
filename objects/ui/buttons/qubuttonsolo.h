#ifndef QUBUTTONSOLO_H
#define QUBUTTONSOLO_H

#include <objects/ui/qubutton.h>


/**
 * @brief The QuButtonSolo class
 * @details The solo button present in QuUIMainMenu.
 */
class QuButtonSolo : public QuButton
{
public:
    QuButtonSolo();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONSOLO_H
