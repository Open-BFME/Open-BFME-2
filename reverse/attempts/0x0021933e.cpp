// ?GetRequiredButton@CreateAHeroManager@@QAEPBVCommandButton@@I@Z
// partial score=0.8 date=2026-10-08
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

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	// 0x0031D5F8 (pinned)
};

class CreateAHeroManager
{
public:
	int GetRequiredButtonCount();
	const CommandButton *GetRequiredButton(unsigned int index);
	char m_pad[0x1dc];
	AsciiString m_name;
};

int CreateAHeroManager::GetRequiredButtonCount()
{
	void *p = ((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(&m_name);
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

// ?GetRequiredButton@CreateAHeroManager@@QAEPBVCommandButton@@I@Z, retail
// 0x0021933E (50 B), right after GetRequiredButtonCount. Instructions and
// calls match; only the block order differs: retail places the shared
// `return 0` right after the first compare (cmp; jb ok; xor eax,eax; pop esi;
// ret 4) and the null-set test jumps back to it, while cl here (region flags
// and /O1 alike) puts it after the null test. Tried: early-return, nested
// if, set != 0 with trailing return 0, braces plus a button local.
const CommandButton *CreateAHeroManager::GetRequiredButton(unsigned int index)
{
	if (index >= (unsigned int)GetRequiredButtonCount())
		return 0;
	const CommandSet *set = TheControlBar->findCommandSet(m_name);
	if (set == 0)
		return 0;
	return set->getCommandButton(index);
}
