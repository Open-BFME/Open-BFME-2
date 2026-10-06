// cl: /DNDEBUG /MD /EHsc

// ?SetDebugPath@Pathfinder@@QAEXPAURva002EDEABArg@@@Z, retail 0x002EDEAB, 153 bytes.
// Rebuilds the Path at +0x58 from an arg list: notifies GameInfo at 0x00E02EEC
// slot 0x4C then returns early when the GlobalData flag at 0x00DFE758+0x9B8 is
// clear else deletes the old Path news a fresh Path via 0x363DC8 and appends
// each source node via Path::rva002655E3 with waypoint 0x7FFFFFFF.
// Target evidence: new(0x28) plus ctor 0x363DC8 plus append 0x2655E3 sequence
// shared with PathCtor.cpp note; dtor 0x364A89 plus delete 0x2FD60 plus new
// 0x2FDA0; callers at 0x2657B1 0x2658F6 0x265A83 0x265DA4 0x266E79 0x2F3B55
// 0x2FB1CE; GameInfo global precedent LANAPIReset plus GlobalData precedent
// TerrainLogic_setActiveBoundary.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct PathNode
{
	PathNode *m_next;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Path
{
public:
	Path();
	~Path();
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int waypointID);

private:
	void *m_unknown00;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	Bool m_unknown0D;
	Int m_unknown10;
	Real m_unknown14;
	Real m_unknown18;
	Real m_unknown1C;
	Real m_unknown20;
	Int m_unknown24;
};

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

struct Rva00DFE758Holder
{
	char m_pad[0x9B8];
	int m_flag9B8;
};

extern Rva00E02EECObj *g_00E02EEC;
extern Rva00DFE758Holder *g_00DFE758;

class Pathfinder
{
	char m_pad00[0x58];
	Path *m_path;
public:
	void SetDebugPath(Rva002EDEABArg *arg);
};

void Pathfinder::SetDebugPath(Rva002EDEABArg *arg)
{
	if (g_00E02EEC != 0)
		g_00E02EEC->virt19();
	if (g_00DFE758->m_flag9B8 == 0)
		return;
	delete m_path;
	m_path = new Path;
	for (Rva002EDEABSrcNode *node = arg->m_head; node != 0; node = node->m_next)
		m_path->rva002655E3(&node->m_pos, node->m_layer, 0x7FFFFFFF);
}
// ?g_00E02EEC@@3PAVRva00E02EECObj@@A: the global at VA 0xe02eec is ?TheGameInfo@@3PAVGameInfo@@A.
#pragma comment(linker, "/alternatename:?g_00E02EEC@@3PAVRva00E02EECObj@@A=?TheGameInfo@@3PAVGameInfo@@A")
// ?g_00DFE758@@3PAURva00DFE758Holder@@A: the global at VA 0xdfe758 is ?TheGlobalData@@3PAVGlobalData@@A.
#pragma comment(linker, "/alternatename:?g_00DFE758@@3PAURva00DFE758Holder@@A=?TheGlobalData@@3PAVGlobalData@@A")
