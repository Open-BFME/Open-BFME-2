// cl: /MD
// ?SetLineSize@Impl@AptScrollBar@@QAEXM@Z @0x005D4B1F 79B: float line-size setter via rowed Fire 0x00527925 with SetLineSize plus EmptyString fallback. Evidence: ucomiss float at +0x1C plus rowed Fire callees plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetLineSize literal plus unblocks 0x005D4BC1 caller 0x005D4BCC.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

#include "../../Include/GameClient/AptScrollBar.h"

// AptScrollBar::Impl::SetLineSize (WorldBuilder name): it fires the same "SetLineSize"
// literal on a change, as the rowed AptScrollBar::Impl::SetVisible does.
void AptScrollBar::Impl::SetLineSize(float v)
{
	if (v != field1C) {
		const char *team = field08.str();
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)field04, team, "SetLineSize", &v);
		field1C = v;
	}
}
