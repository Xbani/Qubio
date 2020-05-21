#ifndef QUUIMAINMENU_H
#define QUUIMAINMENU_H

#include <rooms/quui.h>

#include <objects/ui/buttons/qubuttonclose.h>
#include <objects/ui/buttons/qubuttonmulti.h>
#include <objects/ui/buttons/qubuttonsolo.h>
#include <objects/ui/buttons/qubuttontitle.h>

#include <objects/ui/qutextbox.h>


/**
 * @brief The QuUIMainMenu class
 * @details MainMenu UI class : first room of the game.
 */
class QuUIMainMenu : public QuUI
{
private:
    QuButtonSolo * button_solo;
    QuButtonMulti * button_multi;
    QuButtonTitle * button_title;
    QuButtonClose * button_close;
    QuTextBox * text_box;
public:
    QuUIMainMenu();
    QuUIMainMenu(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void toUIMultiplayer();
    void back() override;

    void init();

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIMAINMENU_H
