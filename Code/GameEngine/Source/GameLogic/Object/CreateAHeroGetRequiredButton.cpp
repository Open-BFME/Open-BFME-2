// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?GetRequiredButton@CreateAHeroManager@@QAEPBVCommandButton@@I@Z
// Retail 0x0021933E..0x00219370 (50 bytes).
// WorldBuilder CreateAHeroManager::GetRequiredButton (CreateAHero.cpp asserts
// "buttonIndex >= GetRequiredButtonCount()" in the first branch and "button"
// on the result). Unsigned range guard against the count sibling
// GetRequiredButtonCount 0x00219309 then the CommandSet lookup keyed by the
// AsciiString at this+0x1DC on TheControlBar (rowed Rva0031D5F8 0x0031D5F8
// which ZH names ControlBar::findCommandSet) then a tail call into
// CommandSet::getCommandButton 0x00409EE8 with the incoming index.
// The if/else chain (rather than early returns) is what keeps retail's
// shared return-NULL block right after the count compare.
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

class CommandButton;
class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class CreateAHeroManager
{
public:
	int GetRequiredButtonCount();
	const CommandButton *GetRequiredButton(unsigned int buttonIndex);
	char m_pad[0x1dc];
	AsciiString m_name;
};

const CommandButton *CreateAHeroManager::GetRequiredButton(unsigned int buttonIndex)
{
	if (buttonIndex >= (unsigned int)GetRequiredButtonCount())
		return 0;
	else
	{
		CommandSet *set = (CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(&m_name);
		if (set == 0)
			return 0;
		else
			return set->getCommandButton((int)buttonIndex);
	}
}
