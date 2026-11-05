// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C4D5CDo@ScriptActions@@QAEXPBVAsciiString@@@Z @0x003C4D5C 102B (dump range 18).
// Terrain node float dispatch: walks the TerrainLogic slot-0x84 list via
// +0x1C links comparing each node's +8 AsciiString through the rowed
// compare, and on the first match copies its +0x0C Coord3D and fires the
// slot-0x94 member on the 0x00DFEA3C global. Node/layout identities
// unproven beyond byte roles.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003C4D5CDo(const AsciiString *name)
{
	Rva003C4D5CNode *node = (Rva003C4D5CNode *)TheTerrainLogic->s33();
	while (node != 0) {
		if ((node->m_name.compare(*name)) == 0)
			goto found;
		node = node->m_next;
	}
	return;
found:
	Coord3D pos;
	pos.x = node->m_pos.x;
	pos.y = node->m_pos.y;
	pos.z = node->m_pos.z;
	TheTacticalView->cameraModLookToward(&pos);
}
