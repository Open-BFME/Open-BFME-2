// cl: /MD
// ?SetPageSize@Impl@AptScrollBar@@QAEXM@Z @0x005D4AD0 79B: float page-size setter via rowed Fire 0x00527925 with SetPageSize plus EmptyString fallback. Evidence: ucomiss float at +0x18 plus rowed Fire callees plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetPageSize literal plus unblocks 0x005D4BAE caller 0x005D4BB9 sibling 0x005D4B1F.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

#include "../../Include/GameClient/AptScrollBar.h"

// AptScrollBar::Impl::SetPageSize (WorldBuilder name): it fires the same "SetPageSize"
// literal on a change, as the rowed AptScrollBar::Impl::SetVisible does.
void AptScrollBar::Impl::SetPageSize(float v)
{
	if (v != field18) {
		const char *team = field08.str();
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)field04, team, "SetPageSize", &v);
		field18 = v;
	}
}
