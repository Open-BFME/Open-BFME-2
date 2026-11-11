// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020F27E@Rva0020F27EHost@@QAE_NHH@Z @0x0020F27E 36B
// Index-then-forward via rowed 0xEAF6 and rowed 0xEA58 (GetRegionCenterPoint): passthrough this for both calls, nullNe->false else EA58 bool.
class Rva0020E89C;
#include "../../../../GameEngine/Include/GameLogic/Rva0020EAF6View.h"
class Coord2D;
#include "../../../../GameEngine/Include/GameLogic/LivingWorldRegionManager.h"
#include "../../../../GameEngine/Source/Common/RegionCenterPointDispatchView.h"
bool Rva0020F27EHost::rva0020F27E(int idx, int v)
{
	Rva0020E89C *p = ((Rva0020EAF6View *)this)->rva0020EAF6(idx);
	if (p == 0)
		return false;
	return ((LivingWorldRegionManager *)this)->GetRegionCenterPoint(p, (Coord2D *)v);
}