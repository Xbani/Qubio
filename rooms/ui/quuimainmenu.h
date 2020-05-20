#ifndef QUUIMAINMENU_H
#define QUUIMAINMENU_H

#include <rooms/quui.h>

#include <objects/ui/buttons/qubuttonmulti.h>
#include <objects/ui/buttons/qubuttonsolo.h>
#include <objects/ui/buttons/qubuttontitle.h>


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
public:
    QuUIMainMenu();
    QuUIMainMenu(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void init();

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIMAINMENU_H
