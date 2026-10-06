// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00567BFDGet@@YAPBVCommandButton@@H@Z @0x00567BFD 169B
// Evidence: static stance table (1 Battle, 2 Aggressive, 3 HoldGround) with guard at 0x00A062D4,
// ControlBar::findCommandButton row 0x0031BE3C via g_bfmeWorldRV, StringBase ctor 0x00037BA0 / releaseBuffer 0x00036410.
// Caller 0x00567CCD passes [eax+4] stance and stores result at +0x18; plain ret = __cdecl.
#include "ascii_string.h"

class CommandButton
{
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;

struct StanceEntry
{
	int id;
	const char *name;
};
extern StanceEntry g_00E062BC[3];
extern int g_00E062D4;

const CommandButton *Rva00567BFDGet(int stance)
{
	if ((g_00E062D4 & 1) == 0) {
		g_00E062D4 |= 1;
		g_00E062BC[0].id = 1;
		g_00E062BC[0].name = "Command_SetStanceBattle";
		g_00E062BC[1].id = 2;
		g_00E062BC[1].name = "Command_SetStanceAggressive";
		g_00E062BC[2].id = 3;
		g_00E062BC[2].name = "Command_SetStanceHoldGround";
	}
	unsigned int i;
	for (i = 0; i < 3; ++i) {
		if (g_00E062BC[i].id == stance)
			goto found;
	}
	return 0;
found:;
	AsciiString s(g_00E062BC[i].name);
	const CommandButton *btn = ((ControlBar *)(void *)g_bfmeWorldRV)->findCommandButton(s);
	return btn;
}
