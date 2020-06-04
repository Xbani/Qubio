#ifndef QUBUTTONSOUND_H
#define QUBUTTONSOUND_H

#include <objects/ui/qubutton.h>



class QuButtonSound : public QuButton
{
protected:
    bool is_on;
    int tex_id_on;
    int tex_id_off;
    int tex_id_on_hover;
    int tex_id_off_hover;
public:
    QuButtonSound();

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONSOUND_H
