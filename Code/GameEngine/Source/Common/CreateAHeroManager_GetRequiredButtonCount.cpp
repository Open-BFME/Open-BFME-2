// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?GetRequiredButtonCount@CreateAHeroManager@@QAEHXZ @0x00219309 53B. The
// class is TheCreateAHeroManager's (AptCreateAHeroPowers calls it there), and
// WorldBuilder's CreateAHeroManager::GetRequiredButton asserts
// "buttonIndex >= GetRequiredButtonCount()" on the result of its call here.
// Honest-address count of leading non-null CommandButtons for the CommandSet
// looked up by the AsciiString at this+0x1dc via g_bfmeWorldRV.
// Evidence: retail add ecx,0x1dc plus rowed Rva0031D5F8 lookup 0x0031D5F8
// plus pin-only CommandSet::getCommandButton 0x00409EE8 looped over 0x20;
// callers at 0x00219341 0x005B27A1 0x005B2BF3 0x005B332A 0x005B36A4.
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../Include/Common/Rva0031D5F8.h"

class CommandButton;
#include "../../Include/GameClient/CommandSet.h"

#include "../../Include/GameLogic/CreateAHeroManager.h"

int CreateAHeroManager::GetRequiredButtonCount()
{
	void *p = ((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(&field1DC);
	if (p == 0)
		return 0;
	CommandSet *cmdSet = (CommandSet *)p;
	unsigned int i = 0;
	for (; i < 0x20; ++i)
	{
		if (cmdSet->getCommandButton((int)i) == 0)
			break;
	}
	return (int)i;
}
