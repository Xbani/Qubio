#ifndef QUUIHOST_H
#define QUUIHOST_H

#include <rooms/quui.h>

#include <objects/ui/qutextbox.h>

#include <objects/ui/buttons/qubuttonclose.h>
#include <objects/ui/buttons/qubuttongohost.h>



class QuUIHost : public QuUI
{
private:
    QuTextBox * text_box_ip;
    QuButtonGoHost * button_go;
    QuButtonClose * button_close;
public:
    QuUIHost();
    QuUIHost(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void toUIWaitingRoom();
    void back() override;

    QString getIp();
    QString getPort();

    void init();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIHOST_H
