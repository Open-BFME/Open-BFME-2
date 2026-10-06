// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// A guarded dispatcher whose whole content is a null test around one call:
//
//     mov ecx,[esp+0x10] / test ecx,ecx / je OUT
//     push [esp+8] / push [esp+8] / call <REL32> / OUT: ret
//
// The guard's pointer is what lands in ecx, so the call is a member of
// whatever the fourth argument names, not a free function, and it receives
// the first two arguments pushed in that order.  The bare ret makes this
// __cdecl: the caller pops all four dwords.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the row's address and
// the call target is pinned in reverse/symbols.csv by the address its REL32
// resolves to.
//
// This TU holds the one row the BFME 1 donor sweep placed; the donor's other
// four definitions are omitted.

class Gen_0064C6A0Target
{
public:
	void bfmeInvoke(void *first, void *second);
};

// ?bfmeDispatch_0064C6A0@@YAXPAX00PAVGen_0064C6A0Target@@@Z	22B @0x0038D494
void bfmeDispatch_0064C6A0(void *first, void *second, void *third, Gen_0064C6A0Target *target)
{
	if (target)
		target->bfmeInvoke(first, second);
}