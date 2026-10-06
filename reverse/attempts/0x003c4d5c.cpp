// ?Rva003C4D5CDo@@YGXPBVAsciiString@@@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003C4D5CDo@@YGXPBVAsciiString@@@Z @0x003C4D5C 102B (dump range 18).
// Terrain node float dispatch: walks the TerrainLogic slot-0x84 list via
// +0x1C links comparing each node's +8 AsciiString through the rowed
// compare, and on the first match copies its +0xC Coord3D and fires the
// slot-0x94 member on the 0x00DFEA3C global. Node/layout identities
// unproven beyond byte roles.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva003C4D5CNode
{
	char m_pad[8];
	AsciiString m_name; // +0x08
	Coord3D m_pos; // +0x0C
	char m_pad18[4];
	struct Rva003C4D5CNode *m_next; // +0x1C
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32();
	virtual void *s33();
};
extern TerrainLogic *TheTerrainLogic;

class TacticalView
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
	virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
	virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15();
	virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
	virtual void t20(); virtual void t21(); virtual void t22(); virtual void t23();
	virtual void t24(); virtual void t25(); virtual void t26(); virtual void t27();
	virtual void t28(); virtual void t29(); virtual void t30(); virtual void t31();
	virtual void t32(); virtual void t33(); virtual void t34(); virtual void t35();
	virtual void t36();
	virtual void s37(const Coord3D *pos);
};
extern TacticalView *TheTacticalView;

void __stdcall Rva003C4D5CDo(const AsciiString *name)
{
	Rva003C4D5CNode *node = (Rva003C4D5CNode *)TheTerrainLogic->s33();
	while (node != 0) {
		if ((node->m_name.compare(*name)) == 0)
			break;
		node = node->m_next;
	}
	if (node == 0)
		return;
	Coord3D pos;
	pos.x = node->m_pos.x;
	pos.y = node->m_pos.y;
	pos.z = node->m_pos.z;
	TheTacticalView->s37(&pos);
}
