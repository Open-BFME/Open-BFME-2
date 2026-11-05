// cl: /DNDEBUG /MD
//
// ?rva002D34FE@Rva002D34FE@@QAEXH@Z @0x002D34FE 46B: guarded two-stage helper
// chain. Retail bails when the pinned thiscall check
// ?rva00401E2F@Rva002D34FE@@QAE_NXZ at 0x00401E2F is true; otherwise it calls
// the pinned ?rva0071BE3C@Rva002D34FEHelper@@QAEHPAX@Z at 0x0071BE3C with
// this=dword_0xE01CFC and arg=caller-this, bails on zero return, and calls
// the pinned ?rva00805DBC@Rva002D34FEHelper@@QAEXPAXH@Z at 0x00805DBC with
// this=dword_0xE01CFC and args (prev-return, 0). The single stack arg is dead
// (frameless this-use only) but required for the ret-4 shape. The helper
// class is an unproven call-shape view; the dword at 0x00E01CFC is read as a
// pointer per the two mov-ecx sites. Honest address-derived names.

// Row spellings of the three callees: 0x00401E2F is StringBase<char>::isEmpty
// on this, and 0x0071BE3C / 0x00805DBC are ControlBar::findCommandButton and
// ControlBar::rva004C1B60 on the control bar.
#include "../../Include/GameClient/ControlBar.h"

class Rva002D34FE
{
public:
	void rva002D34FE(int unused);
};

extern ControlBar *TheControlBar;

// ?rva002D34FE@Rva002D34FE@@QAEXH@Z
void Rva002D34FE::rva002D34FE(int)
{
	if (((const StringBase<char> *)this)->isEmpty())
		return;
	const CommandButton *commandButton = TheControlBar->findCommandButton(*(const AsciiString *)this);
	if (!commandButton)
		return;
	TheControlBar->rva004C1B60(0, (void *)commandButton);
}
