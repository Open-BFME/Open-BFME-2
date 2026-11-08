// cl: /DNDEBUG /MD /EHsc

// ?SetDebugPath@Pathfinder@@QAEXPAURva002EDEABArg@@@Z, retail 0x002EDEAB, 153 bytes.
// Rebuilds the Path at +0x58 from an arg list: notifies GameInfo at 0x00E02EEC
// slot 0x4C then returns early when the GlobalData flag at TheWritableGlobalData (VA 0x00DFE758)+0x9B8 is
// clear else deletes the old Path news a fresh Path via 0x363DC8 and appends
// each source node via Path::appendNode with waypoint 0x7FFFFFFF.
// Target evidence: new(0x28) plus ctor 0x363DC8 plus append 0x2655E3 sequence
// shared with PathCtor.cpp note; dtor 0x364A89 plus delete 0x2FD60 plus new
// 0x2FDA0; callers at 0x2657B1 0x2658F6 0x265A83 0x265DA4 0x266E79 0x2F3B55
// 0x2FB1CE; GameInfo global precedent LANAPIReset plus GlobalData precedent
// TerrainLogic_setActiveBoundary.

typedef float Real;
typedef int Int;
typedef bool Bool;

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

#include "../../../Include/GameLogic/PathfindPath.h"

struct Rva002EDEABSrcNode
{
	char m_pad00[8];
	Rva002EDEABSrcNode *m_next;
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
};

struct Rva002EDEABArg
{
	char m_pad00[4];
	Rva002EDEABSrcNode *m_head;
};

class Rva00E02EECObj
{
public:
	virtual void virt00() = 0;
	virtual void virt01() = 0;
	virtual void virt02() = 0;
	virtual void virt03() = 0;
	virtual void virt04() = 0;
	virtual void virt05() = 0;
	virtual void virt06() = 0;
	virtual void virt07() = 0;
	virtual void virt08() = 0;
	virtual void virt09() = 0;
	virtual void virt10() = 0;
	virtual void virt11() = 0;
	virtual void virt12() = 0;
	virtual void virt13() = 0;
	virtual void virt14() = 0;
	virtual void virt15() = 0;
	virtual void virt16() = 0;
	virtual void virt17() = 0;
	virtual void virt18() = 0;
	virtual void virt19() = 0;
};

#include "../../../Include/Common/GlobalData.h"

extern class GameInfo *TheGameInfo;
extern GlobalData *TheWritableGlobalData;

#include "../../../Include/GameLogic/AIPathfind.h"

void Pathfinder::SetDebugPath(Rva002EDEABArg *nodeList)
{
	if (TheGameInfo != 0)
		(*(Rva00E02EECObj **)&TheGameInfo)->virt19();
	if (TheWritableGlobalData->field09B8 == 0)
		return;
	delete m_field58;
	m_field58 = new Path;
	for (Rva002EDEABSrcNode *node = nodeList->m_head; node != 0; node = node->m_next)
		m_field58->appendNode(&node->m_pos, node->m_layer, 0x7FFFFFFF);
}
