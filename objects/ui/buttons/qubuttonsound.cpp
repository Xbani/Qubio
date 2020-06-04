#include "qubuttonsound.h"

#include <rooms/ui/quuimainmenu.h>

QuButtonSound::QuButtonSound():QuButton(17,18)
{

    is_on=true;

    tex_id_on       = 17;
    tex_id_on_hover = 18;
    tex_id_off      = 19;
    tex_id_off_hover= 20;

    setSprite(tex_id_on);
    setSpriteHover(tex_id_on_hover);
}

void QuButtonSound::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMainMenu * uiMainMenu=dynamic_cast<QuUIMainMenu *>(scene());

    if(is_on){
        is_on= false;

        setSprite(tex_id_off);
        setSpriteHover(tex_id_off_hover);

        uiMainMenu->getSoundPlayer()->setVolume(0);
    }

    else{
        is_on= true;

        setSprite(tex_id_on);
        setSpriteHover(tex_id_on_hover);
        uiMainMenu->getSoundPlayer()->setVolume(100);
    }
}
