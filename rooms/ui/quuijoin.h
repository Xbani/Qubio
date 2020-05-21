#ifndef QUUIJOIN_H
#define QUUIJOIN_H

#include <rooms/quui.h>

#include <objects/ui/qutextbox.h>

#include <objects/ui/buttons/qubuttonclose.h>
#include <objects/ui/buttons/qubuttongojoin.h>



class QuUIJoin : public QuUI
{
private:
    QuTextBox * text_box_ip;
    QuButtonGoJoin * button_go;
    QuButtonClose * button_close;
public:
    QuUIJoin();
    QuUIJoin(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void toUIWaitingRoom();
    void back() override;

    void init();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIJOIN_H
