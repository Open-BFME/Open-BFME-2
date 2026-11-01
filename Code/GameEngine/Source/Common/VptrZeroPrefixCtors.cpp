// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// __thiscall constructors that open with the vftable-plus-zeroed-dword head and
// then store their arguments straight into the members that follow it.
//
// The head is the one FunctorBindInvokers.cpp measured and
// FunctorBindWrapperCtors.cpp landed constructors for: a vftable slot at +0x00
// and one unmodelled dword at +0x04, split into a base whose own constructor
// zeroes that dword.  Every body here begins
//
//     mov eax,ecx / ... / mov [eax+4],0 / mov [eax],<vftable>
//
// -- `mov eax,ecx` with no other use of eax is a constructor returning `this`,
// and the +0x04 store landing BEFORE the +0x00 store is the base's dead vftable
// write being dropped, which a single class cannot produce (probed: it emits
// the vftable first).  What differs between the two shapes here is only what
// is stored after that, so they are grouped by argument shape and each body is
// named for its own address; no class name has been recovered for either.
//
// Dedicated TU: only the two placed bodies are defined; the donor's other
// twelve definitions are omitted.

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroAnchor();

	unsigned int m_unmodelled_04;
};

// mov dl,[esp+8] / mov eax,ecx / mov cl,[esp+4] / <head> /
// mov [eax+8],cl / mov [eax+9],dl / ret 8
#include "../../Include/Common/BfmeAccessorMacros.h"

// mov edx,[esp+8] / mov eax,ecx / mov ecx,[esp+4] / mov [eax+8],ecx /
// mov ecx,[esp+0xC] / <head> / mov [eax+0xC],dl / mov [eax+0x10],ecx / ret 0xC

BFME_VPTR_ZERO_BYTE_BYTE_CTOR( Rva00149F20VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( Rva002ED5C0VptrZeroObject )
// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?vptrZeroAnchor@VptrZeroHead@@UAEXXZ=?rva00395A19@Rva00395A19@@QAEPAXI@Z")
