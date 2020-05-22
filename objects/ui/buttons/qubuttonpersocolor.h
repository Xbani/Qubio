#ifndef QUBUTTONPERSOCOLOR_H
#define QUBUTTONPERSOCOLOR_H

#include <objects/ui/qubutton.h>



class QuButtonPersoColor : public QuButton
{
private:
    int hue;
    QImage sprite_ref;
public:
    QuButtonPersoColor();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONPERSOCOLOR_H
