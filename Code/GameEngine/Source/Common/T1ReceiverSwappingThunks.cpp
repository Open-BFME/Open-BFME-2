// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Six bodies that make ONE call and hand the receiver over to something else.
// Two arities, both of them pure forwarding.
//
// SHAPE A -- 21 bytes, two rows, a FREE function returning its first argument:
//
//     mov eax,[esp+8] / push esi / mov esi,[esp+8] / push eax
//     mov ecx,esi / call <REL32> / mov eax,esi / pop esi / ret
//
// The trailing `ret` pops nothing, so the caller cleans the stack: __cdecl,
// two dword parameters, and ecx is never read on entry -- this is not a
// member.  The FIRST parameter is loaded into esi and becomes the callee's
// `this`; the SECOND is re-pushed unchanged as the callee's only argument; and
// esi is returned.  A free function that calls a member on its first argument
// and hands that argument back is the classic operator-style helper, and the
// bytes fix everything about it except the names.
//
// SHAPE B -- 18 bytes, four rows, a MEMBER that passes `this` to a method of
// its second argument:
//
//     mov eax,[esp+4] / push eax / push ecx / mov ecx,[esp+0x10]
//     call <REL32> / ret 8
//
// ecx is live on entry and `ret 8` pops two dwords: __thiscall with two
// parameters.  The pushes are the giveaway -- `push eax` then `push ecx` puts
// the FIRST parameter second and `this` FIRST in the callee's argument list,
// and the receiver for that call is then loaded from [esp+0x10], which after
// the two pushes is the SECOND parameter.  So the body is `return
// second->f( this, first );`, with the callee's return value left in eax and
// the callee popping its own arguments.  Nothing else is read or written.
//
// TWO CALLEES, FOUR ROWS, IN SHAPE B: 0x005C98A0 and 0x005CACC0 call one
// target, 0x005C98C0 and 0x005CACE0 the other, so the four rows are two pairs.
// Each pair shares its callee's class; the enclosing classes stay separate
// because four addresses are four COMDATs and nothing says any two of them are
// members of one type.  Same duplicate-translation-unit spacing as the cached
// accessor family: 0x005C98A0/0x005C98C0 and 0x005CACC0/0x005CACE0 are two
// copies of the same adjacent pair.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived, and the callee is
// unclaimed, so it enters as a declaration pinned by address.
//
// This TU holds the one shape-B row the BFME 1 donor sweep placed; the
// donor's other five definitions are omitted.

// ---------------------------------------------------- shape B, member forward

class T1Sink_005C8D40
{
public:
	void *accept( void *owner, void *a );
};

class T1Fwd_005C98A0
{
public:
	void *hand( void *a, T1Sink_005C8D40 *sink );
};

void *T1Fwd_005C98A0::hand( void *a, T1Sink_005C8D40 *sink )
{
	return sink->accept( this, a );
}
