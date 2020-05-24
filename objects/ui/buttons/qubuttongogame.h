#ifndef QUBUTTONGOGAME_H
#define QUBUTTONGOGAME_H

#include <objects/ui/qubutton.h>



class QuButtonGoGame : public QuButton
{
private:
    bool is_host;
public:
    QuButtonGoGame();
    QuButtonGoGame(bool is_host);

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QUBUTTONGOGAME_H
