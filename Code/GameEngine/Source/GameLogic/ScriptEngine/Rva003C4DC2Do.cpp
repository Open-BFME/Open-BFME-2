// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C4DC2Do@ScriptActions@@QAEXABVAsciiString@@@Z @0x003C4DC2 102B.
// Script free function walking TerrainLogic list at 0xDFEC50 comparing
// name at +8 via rowed StringBase compare then calling holder at 0xDFEA3C
// slot 0x98 with position at +0xC. Evidence: manual loop with next at +0x1C
// plus movss x y z plus single AsciiString stdcall shape ret 4.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/Waypoint.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
class Rva003C4DC2Holder
{
public:
	virtual void _0() = 0;
	virtual void _1() = 0;
	virtual void _2() = 0;
	virtual void _3() = 0;
	virtual void _4() = 0;
	virtual void _5() = 0;
	virtual void _6() = 0;
	virtual void _7() = 0;
	virtual void _8() = 0;
	virtual void _9() = 0;
	virtual void _10() = 0;
	virtual void _11() = 0;
	virtual void _12() = 0;
	virtual void _13() = 0;
	virtual void _14() = 0;
	virtual void _15() = 0;
	virtual void _16() = 0;
	virtual void _17() = 0;
	virtual void _18() = 0;
	virtual void _19() = 0;
	virtual void _20() = 0;
	virtual void _21() = 0;
	virtual void _22() = 0;
	virtual void _23() = 0;
	virtual void _24() = 0;
	virtual void _25() = 0;
	virtual void _26() = 0;
	virtual void _27() = 0;
	virtual void _28() = 0;
	virtual void _29() = 0;
	virtual void _30() = 0;
	virtual void _31() = 0;
	virtual void _32() = 0;
	virtual void _33() = 0;
	virtual void _34() = 0;
	virtual void _35() = 0;
	virtual void _36() = 0;
	virtual void _37() = 0;
	virtual void rva0098(const Coord3D *pos) = 0;
};
extern class View *TheTacticalView;
void ScriptActions::Rva003C4DC2Do(const AsciiString &name)
{
	TerrainLogic *logic = TheTerrainLogic;
	Waypoint *cur = logic->getFirstWaypoint();
	while (cur) {
		if (((const StringBase<char> *)&cur->m_name)->compare(*(const StringBase<char> *)&name) == 0)
			goto found;
		cur = cur->m_pNext;
	}
	return;
found:
	{
		float x = cur->m_location.x;
		Rva003C4DC2Holder *holder = (*(Rva003C4DC2Holder **)&TheTacticalView);
		Coord3D pos;
		pos.x = x;
		pos.y = cur->m_location.y;
		pos.z = cur->m_location.z;
		holder->rva0098(&pos);
	}
}
