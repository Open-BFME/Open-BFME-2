// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// TooltipUpgrade::upgradeRemovalImplementation, retail 0x004B7ADB (69
// bytes): slot 8 of the +0x10 UpgradeMux vtable 0x00C58BC0 (slot 10 is the
// rowed 0x004B7A9D; the recipe of RemoveUpgradeUpgradeRemovalImplementation.cpp).
// Only when the upgrade is in effect (mux slot 0): the Object's Drawable, if
// any, drops the two tooltip strings it carries at +0x348 and +0x34C and
// TheControlBar is flagged (+0x28) to rebuild; then the executed flag is
// cleared (mux slot 9).
#include "ascii_string.h"


#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameClient/DrawableBFME2.h"
#include "../object.h"
#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
#include "../../../../Include/GameLogic/Module/ObjectModuleBase.h"
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"
class TooltipUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
};
void TooltipUpgrade::upgradeRemovalImplementation()
{
	if (isAlreadyUpgraded())
	{
		Drawable *draw = getObject()->getDrawable();
		if (draw)
		{
			((AsciiString *)((unsigned char *)draw + 0x348))->clear();
			((AsciiString *)((unsigned char *)draw + 0x34C))->clear();
			TheControlBar->field28 = true;
		}
		setUpgradeExecuted(false);
	}
}
