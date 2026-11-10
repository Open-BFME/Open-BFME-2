// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z 0x0029725B 86B evidence: pin name; caller 0x0036E25E bfmeVisitABG; callees rowed rva00290E67 Rva0031D5F8 getCommandButton plus pinned doCommandButton; BFME1 donor ObjectBfmeApplyABG type 0x2c over 20 vs retail 0x2e over 32; Rva00391994 32-slot precedent
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../../Include/GameClient/CommandButton.h"

#include "../../../Include/GameClient/CommandSet.h"

#include "../../../Include/Common/Rva0031D5F8.h"

#include "object.h"

class BfmeK1094
{
public:
	void bfmeApplyABG(void *a, void *b);
};

void BfmeK1094::bfmeApplyABG(void *a, void *b)
{
	int commandIndex = (int)a;
	const AsciiString *name = ((const Object *)this)->rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
	if (!cmdSet)
		return;
	for (int i = 0; i < 0x20; ++i)
	{
		const CommandButton *btn = cmdSet->getCommandButton(i);
		if (btn->m_command == 0x2e)
		{
			if (commandIndex == 0)
			{
				((Object *)this)->doCommandButton(btn, (int)b, 0);
				return;
			}
			--commandIndex;
		}
	}
}
