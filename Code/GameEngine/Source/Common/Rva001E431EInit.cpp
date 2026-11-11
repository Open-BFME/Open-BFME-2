// cl: /MD
// ?rva001E431E@Rva001E431E@@QAEXPBH@Z @0x001E431E 44B unlock via Object 0x0028CFB2.
// Zero 0x4C local via ji_006291ae then Object::rva0028CFB2 with buffer and arg.
// Evidence: 31 callers; rowed memset thunk 0x006291AE;
// rowed Object callee 0x0028CFB2 taking two const int star.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

#include "../GameLogic/Object/object.h"

#include "../../Include/GameLogic/Module/Rva001E431E.h"

void Rva001E431E::rva001E431E(const int *x)
{
	int buf[19];
	memset(buf, 0, 0x4C);
	((Object *)this)->rva0028CFB2(buf, x);
}

// Object callers (ObjectConditionAndPassengerWeaponSet.cpp) spell this body as Object::rva001E431E, pinned to the same address (thiscall, one mask pointer); bind that spelling here.
#pragma comment(linker, "/alternatename:?rva001E431E@Object@@QAEXPBH@Z=?rva001E431E@Rva001E431E@@QAEXPBH@Z")
