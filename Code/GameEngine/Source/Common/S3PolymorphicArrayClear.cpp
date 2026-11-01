// Five __thiscall members that walk a counted array of polymorphic elements,
// call each element's FIRST virtual with a zero argument, hand the block back
// to an allocator fetched from a global getter, and clear both fields:
//
//     if [this+0] == 0            -> straight to the trailing count store
//     for ( edi = 0; edi < [this+4]; ++edi )
//         ecx = [this+0] + edi*STRIDE ; push 0 ; call [ [ecx] ]
//     ecx = <getter>() ; push 0 ; push [this+0] ; call [ [ecx] + 0xC ]
//     [this+0] = 0
//     [this+4] = 0
//
// WHAT THE BYTES SHOW.  The element address is formed by ADDING a running
// byte offset to the base, and the vptr is read at offset 0 of that address,
// so the elements are stored BY VALUE in the block and each carries a vptr at
// its own offset 0.  Both the base and the count are RE-READ from the object
// every iteration, which is source structure, not compiler waste: the loop
// condition compares against a freshly loaded [this+4].
//
// The early `je` lands PAST the base store and on the count store, so
// `m_count = 0` is outside the guard while `m_array = 0` is inside it.  That
// asymmetry is the whole reason the two stores are not adjacent.
//
// The allocator getter is a __cdecl call taking nothing and returning a pointer
// whose FOURTH vtable slot is entered __thiscall with two dwords, (block, 0).
//
// ONE AXIS: the element stride -- 28, 64, 48, 56 and 128 bytes.  Everything
// else, including both callees, is identical in all five rows.  The 128-byte
// row is three bytes longer only because `add ebx,0x80` needs an imm32.
//
// IDENTITY IS NOT RECOVERED.  A first-virtual-with-a-zero-flag call is what
// MSVC also emits for a destructor reached through a `??_G` slot, so the bytes
// do NOT decide whether this loop destroys the elements or merely resets them;
// the spelling here asserts only what is visible, an ordinary virtual call.
// Nothing here names the element types, the owner types, or the allocator.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

#include "../../Include/Common/BfmeAccessorMacros.h"

S3_ARRAY_CLEAR( Rva007F6BA0, 28 )
S3_ARRAY_CLEAR( Rva007F6C60, 64 )
S3_ARRAY_CLEAR( Rva00801570, 48 )
S3_ARRAY_CLEAR( Rva00801600, 56 )
// Rva00802A10 stride-128 has no BFME2 placement; omitted so the TU holds
// only claimed bodies (hook requires a ledger row per defined function).

// BFME1 donor accessors at 0x00801550 and 0x008029F0 transfer byte-for-byte
// to BFME2 0x0066D870 and 0x0066EB20. The array layout and returned element
// offset follow from those bytes; the address-derived class labels remain
// provisional because the target has no named direct callers.

S3_ARRAY_LOOKUP( Rva00801550, 48 )
S3_ARRAY_LOOKUP( Rva008029F0, 128 )

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDtorATYA@BfmeHeadTYA@@QAEXXZ=?clear@Rva00801600@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeClearAVHW@BfmeSubAVHW@@QAEXXZ=?clear@Rva00801570@@QAEXXZ")
