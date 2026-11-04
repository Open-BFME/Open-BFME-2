// cl: /MD
// ?SetPos@Impl@AptScrollBar@@QAEXM@Z @0x005D4B6E 64B: float pos firer via rowed Fire 0x00527925 with SetPos plus EmptyString fallback no store. Evidence: ucomiss float at +0x20 plus rowed Fire plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetPos literal plus unblocks 0x005D4BD4 caller 0x005D4BDF siblings 0x005D4B1F 0x005D4AD0.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

#include "../../Include/GameClient/AptScrollBar.h"

// AptScrollBar::Impl::SetPos (WorldBuilder name): it fires the same "SetPos"
// literal on a change, as the rowed AptScrollBar::Impl::SetVisible does.
void AptScrollBar::Impl::SetPos(float v)
{
	if (v != field20) {
		const char *team = field08.str();
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)field04, team, "SetPos", &v);
	}
}
