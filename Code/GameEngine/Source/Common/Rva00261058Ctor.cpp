// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00261058@@QAE@PAVObject@@_N@Z, retail 0x00261058, 69 bytes.
// Player-filter ctor: base clears +4, vtable 0x007F8FE4, +8 controlling player or 0, +0xC flag.
// Evidence: caller 0x002FDCBE lea temp plus push 0 push esi; vtable store; rowed getControllingPlayer 0x0028AFA9; neighbours 0x00261046/0x0026115D.
class Player;
#include "../GameLogic/Object/object.h"
// Partition filter base 0x00BC26E0 (rowed ~Rva000421C8 0x0049C38A, getPlayerMask 0x0036CC7A);
// retail vtable 0x007F8FE4 is [deleting dtor 0x00395A19, allow, getPlayerMask].
#include "../../Include/GameLogic/Rva00261058.h"
Rva00261058::Rva00261058(Object *obj, bool flag) : Rva000421C8()
{
	if (obj == 0)
		m_player = 0;
	else
		m_player = obj->getControllingPlayer();
	m_flag = flag;
}
// ?allow@Rva00261058@@UAE_NPAVObject@@@Z @ 0x0026109D (65B): slot 1 (allow)
// of partition filter vftable 0x00BF8FE4; fields from the constructor; calls
// and branches from target.
bool Rva00261058::allow(Object *obj)
{
	bool result = obj->rva00294471(m_player, 0);
	if (!result && m_player != 0 && *(int *)((char *)m_player + 0x5c) == 1 && obj->rva0028C1CC())
		++result;
	return m_flag != result;
}
