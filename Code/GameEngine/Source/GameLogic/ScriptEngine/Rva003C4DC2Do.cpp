// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?Rva003C4DC2Do@@YGXABVAsciiString@@@Z @0x003C4DC2 102B.
// Script free function walking TerrainLogic list at 0xDFEC50 comparing
// name at +8 via rowed StringBase compare then calling holder at 0xDFEA3C
// slot 0x98 with position at +0xC. Evidence: manual loop with next at +0x1C
// plus movss x y z plus single AsciiString stdcall shape ret 4.
#include "ascii_string.h"
struct Coord3D
{
	float x;
	float y;
	float z;
};
struct Rva003C4DC2Node
{
	char m_pad0[8];
	AsciiString m_name;
	float m_x;
	float m_y;
	float m_z;
	char m_pad18[4];
	Rva003C4DC2Node *m_next;
};
class TerrainLogic
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
	virtual Rva003C4DC2Node *getHead() = 0;
};
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
extern TerrainLogic *TheTerrainLogic;
extern class View *TheTacticalView;
void __stdcall Rva003C4DC2Do(const AsciiString &name)
{
	TerrainLogic *logic = TheTerrainLogic;
	Rva003C4DC2Node *cur = logic->getHead();
	while (cur) {
		if (((const StringBase<char> *)&cur->m_name)->compare(*(const StringBase<char> *)&name) == 0)
			goto found;
		cur = cur->m_next;
	}
	return;
found:
	{
		float x = cur->m_x;
		Rva003C4DC2Holder *holder = (*(Rva003C4DC2Holder **)&TheTacticalView);
		Coord3D pos;
		pos.x = x;
		pos.y = cur->m_y;
		pos.z = cur->m_z;
		holder->rva0098(&pos);
	}
}
