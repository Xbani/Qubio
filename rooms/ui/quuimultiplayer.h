#ifndef QUUIMULTIPLAYER_H
#define QUUIMULTIPLAYER_H

#include <rooms/quui.h>

#include <objects/ui/buttons/qubuttonclose.h>
#include <objects/ui/buttons/qubuttonhost.h>
#include <objects/ui/buttons/qubuttonjoin.h>
#include <objects/ui/buttons/qubuttonmulti.h>



class QuUIMultiplayer : public QuUI
{
private:
    QuButtonHost * button_host;
    QuButtonJoin * button_join;
    QuButtonClose * button_close;
public:
    QuUIMultiplayer();
    QuUIMultiplayer(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void back() override;
    void toUIHost();
    void toUIJoin();
    void init();

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIMULTIPLAYER_H
