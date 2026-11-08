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

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003C4D5CDo(const AsciiString *name)
{
	Rva003C4D5CNode *node = (Rva003C4D5CNode *)TheTerrainLogic->getFirstWaypoint();
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
