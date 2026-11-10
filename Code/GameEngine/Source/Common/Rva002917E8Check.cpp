// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002917E8@Rva002917E8@@QAE_NXZ @ 0x002917E8 (79B) unlock: Object 6-bit plus command-button 0x10 flag scan over 32 slots via rowed Object name plus rowed Rva0031D5F8 lookup plus pinned getCommandButton. Evidence: rva0028ADF7 row plus g_bfmeWorldRV plus 0x20 loop with +0x1c test 0x10; caller 0x0030F019.
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../GameLogic/Object/object.h"

#include "../../Include/Common/Rva0031D5F8.h"

#include "../../Include/GameClient/CommandButton.h"
#include "../../Include/GameClient/CommandSet.h"

class Rva002917E8
{
public:
	bool rva002917E8(void);
};

bool Rva002917E8::rva002917E8(void)
{
	unsigned char first = (unsigned char)((const Object *)this)->rva0028ADF7(6);
	if (first)
		return true;
	const AsciiString *name = ((const Object *)this)->rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
	if (cmdSet) {
		for (int i = 0; i < 0x20; ++i) {
			const CommandButton *btn = cmdSet->getCommandButton(i);
			if (btn && (btn->getOptions() & 0x10))
				return true;
		}
	}
	return false;
}
