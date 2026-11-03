// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Clean reconstruction of the conditional forwarding helper at retail RVA
// 0x00942BC0.  The owning type is not recovered; the callee is the rowed
// Render2DSentenceClass::Build_Sentence_Not_Centered at 0x00159700.
#include "../../../../reference/shims/wwmath/Vector2.h"

#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class Gen_00942BC0
{
public:
	void process(void *first, void *second, void *third);
};

void Gen_00942BC0::process(void *first, void *second, void *third)
{
	if (first != 0)
		((Render2DSentenceClass *)this)->Build_Sentence_Not_Centered(
			(const unsigned short *)first, (int *)second, (int *)third, false);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSet1042@BfmeSub1042@@QAEXPADHH@Z=?process@Gen_00942BC0@@QAEXPAX00@Z")
