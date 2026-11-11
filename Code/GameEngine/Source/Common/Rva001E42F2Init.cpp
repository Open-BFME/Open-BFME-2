// cl: /MD
// ?rva001E42F2@Rva001E42F2@@QAEXPBH@Z @0x001E42F2 44B unlock via Object 0x0028CFB2.
// Zero 0x4C local via ji_006291ae then Object::rva0028CFB2 with arg and buffer.
// Evidence: caller 0x002C8B9B and 37 callees; rowed memset thunk 0x006291AE;
// rowed Object callee 0x0028CFB2 taking two const int star.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

#include "../GameLogic/Object/object.h"

#include "../../Include/GameLogic/Module/Rva001E42F2.h"

void Rva001E42F2::rva001E42F2(const int *x)
{
	int buf[19];
	memset(buf, 0, 0x4C);
	((Object *)this)->rva0028CFB2(x, buf);
}

// Object callers (ObjectConditionAndPassengerWeaponSet.cpp) spell this body as Object::rva001E42F2, pinned to the same address (thiscall, one mask pointer); bind that spelling here.
#pragma comment(linker, "/alternatename:?rva001E42F2@Object@@QAEXPBH@Z=?rva001E42F2@Rva001E42F2@@QAEXPBH@Z")
