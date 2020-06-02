#include "qubuttonmapbuilder.h"

#include <rooms/ui/quuimainmenu.h>

QuButtonMapBuilder::QuButtonMapBuilder():QuButton(15,16)
{

}

void QuButtonMapBuilder::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QuUIMainMenu * uiMainMenu=dynamic_cast<QuUIMainMenu *>(scene());
    uiMainMenu->toBuilderMainFrame();
}
