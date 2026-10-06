// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// A __stdcall free function whose whole content is a null test around one
// __thiscall call:
//
//     mov ecx,[esp+4] / test ecx,ecx / je OUT
//     push [esp+8] / call <REL32> / OUT: ret 8
//
// The receiver arrives as an ORDINARY STACK ARGUMENT and is moved into ecx,
// and the function pops its own two dwords, so it is __stdcall wrapping a
// __thiscall call.  The null test is on the receiver, so the source tests the
// pointer it was handed before calling through it.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the row's address and
// the call target is pinned in reverse/symbols.csv by the address its REL32
// resolves to.
//
// This TU holds the one row the BFME 1 donor sweep placed; the donor's other
// three definitions are omitted.

class U4Target0060C2C0
{
public:
	void hand( void *payload );
};

void __stdcall u4Guarded0060C2C0( U4Target0060C2C0 *target, void *payload )
{
	if ( target != 0 )
		target->hand( payload );
}
