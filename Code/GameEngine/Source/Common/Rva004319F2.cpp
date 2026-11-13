// cl: /MD
// ?Rva004319F2Update@@YAXXZ @0x004319F2 66B.
// Evidence: chain via 0x0029AA3F; TheInGameUI virtuals 0xCC and 0xD8 plus byte 0x9B4;
// rowed Rva0029AA3F 0x0029AA3F and 0x0029A9FF; callers 0x00431E5A 0x00431E95;
// prev Rva004319D4 next Rva00431A34.
#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/Rva0029AA3F.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

void __cdecl Rva004319F2Update()
{
	if (TheInGameUI->slot51())
		TheInGameUI->rva0029DB61();
	if (TheInGameUI->m_9B4 != 0)
	{
		((Rva0029AA3F *)TheInGameUI)->rva0029AA3F();
		((Rva0029AA3F *)TheInGameUI)->rva0029A9FF(0);
	}
}
