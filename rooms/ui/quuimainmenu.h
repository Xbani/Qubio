#ifndef QUUIMAINMENU_H
#define QUUIMAINMENU_H

#include <rooms/quui.h>

#include <objects/ui/buttons/qubuttonclose.h>
#include <objects/ui/buttons/qubuttonmapbuilder.h>
#include <objects/ui/buttons/qubuttonmulti.h>
#include <objects/ui/buttons/qubuttonpersocolor.h>
#include <objects/ui/buttons/qubuttonsolo.h>
#include <objects/ui/buttons/qubuttontitle.h>

#include <objects/ui/qutextbox.h>

#include <objects/ui/buttons/qubuttonsound.h>


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
    QuButtonPersoColor * button_perso_color;
    QuButtonMapBuilder * button_map_builder;
    QuButtonSound * button_sound;

    QuTextBox * text_box;
public:
    QuUIMainMenu();
    QuUIMainMenu(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

    void toUIMultiplayer();
    void toUISolo();
    void toBuilderMainFrame();
    void back() override;
    int getColorHUE();
    QString getNickName();

    void init();

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUUIMAINMENU_H
