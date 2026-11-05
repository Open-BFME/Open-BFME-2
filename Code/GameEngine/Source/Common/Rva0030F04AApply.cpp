// cl: /DNDEBUG /MD
// ?Rva0030F04AApply@@YAXHPAURva0030F04AOut@@@Z @0x0030F04A 79B: flag-gated bit sets plus InGameUI slot48 check. Evidence: packet disasm with rowed TheInGameUI; caller 0x0030F0E2 pushes prove __cdecl (int, ptr) with ret; virtual at 0xC0 is slot48.
#include "../../Include/GameClient/CommandButton.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

struct Rva0030F04AOut
{
	unsigned int m_00;
	unsigned char m_04;
	unsigned char m_05;
	unsigned char m_06;
	unsigned char m_07;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned char m_10;
	unsigned char m_11;
};

void Rva0030F04AApply(int flags, Rva0030F04AOut *out)
{
	if (flags & 4) {
		out->m_00 |= 2;
		const CommandButton *command = TheInGameUI->getGUICommand();
		if (command && command->getCommandType() == (GUICommandType)0x18)
			out->m_07 |= 0x10;
	}
	if (flags & 8)
		out->m_00 |= 0x40;
	if (flags & 0x200) {
		out->m_0C |= 2;
		out->m_11 |= 1;
	}
	if (flags & 0x20)
		out->m_08 |= 0x10;
}
