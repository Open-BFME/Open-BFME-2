// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva004DD658@PathfinderPosGoalManager@@QAEXPAVXfer@@@Z
// Retail 0x004DD658 90 bytes RET4. PathfinderPosGoalManager (the 0x4C-byte
// object Object::DoXfer 0x00297684 allocates at Object+0x44 through ctor
// 0x004DD7E3 and serializes with this call; WB twin 0x01286B40). Version 1
// through the rowed Xfer::Version1 0x000053EE then for the position slot
// (+4) and the goal slot (+0x1C): the cell (ICoord2D) through Xfer slot 0x4C
// the footprint angle through the rowed Rva004DD619Footprint 0x004DD619 and
// the pathfind layer through the rowed XferPathfindLayerEnum 0x00305D0A.
// Each helper returns the Xfer for the next transfer: the goal slot is
// transferred through the layer helper's returned Xfer (WB keeps it too).
// Slot layout follows PathfinderPosGoalManager.cpp's Rva004DD843Slot.

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../Libraries/Include/Lib/ICoord3D.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

#include "../../../../Libraries/Include/Lib/Region2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../Include/Common/RealRange.h"

#include "../../../../Libraries/Include/Lib/RGBColor.h"

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

#include "../../../Include/Common/RGBAColorInt.h"

class Snapshot;

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

#include "../../../Include/Common/BfmeXfer.h"

Xfer * __cdecl Rva004DD619Footprint(Xfer *xfer, int *value);
Xfer * __cdecl XferPathfindLayerEnum(Xfer *xfer, int *value);

class Object;
class PathfindCell;

struct Rva004DD843Slot
{
	ICoord2D m_cell;
	int m_angle;
	int m_pathLayer;
	int m_listKind;
	PathfindCell *m_pathCell;
};

class PathfinderPosGoalManager
{
public:
	void rva004DD658(Xfer *xfer);

	Object *m_object;
	Rva004DD843Slot m_position;
	Rva004DD843Slot m_goal;
	Rva004DD843Slot m_other;
};

void PathfinderPosGoalManager::rva004DD658(Xfer *xfer)
{
	xfer->Version1();
	Xfer *next = XferPathfindLayerEnum(
		Rva004DD619Footprint(&(*xfer == m_position.m_cell), &m_position.m_angle),
		&m_position.m_pathLayer);
	XferPathfindLayerEnum(
		Rva004DD619Footprint(&(*next == m_goal.m_cell), &m_goal.m_angle),
		&m_goal.m_pathLayer);
}

// Retail 0x0028A818 (18B, cdecl): transfers the manager through the xfer
// member above (its only callee) and returns the Xfer, the stream-operator
// shape (twin skeleton of the STLport ostream operator<< at 0x001F65F4).
// The original spelling (operator or helper) is unknown; address-named.
Xfer *__cdecl rva0028A818(Xfer *xfer, PathfinderPosGoalManager *manager)
{
	manager->rva004DD658(xfer);
	return xfer;
}
