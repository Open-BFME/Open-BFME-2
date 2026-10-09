// ?rva0052E914@Pathfinder@@QAEXHHPAVPathfindCell@@PAVBridge@@_N0M@Z
// partial score=0.91 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0052E914@Pathfinder@@QAEXHHPAVPathfindCell@@PAVBridge@@_N1M@Z
// @0x0052E914 1120B, BFME2's bridge-cell classification (Zero Hour
// PathfindLayer::classifyLayerMapCell moved onto the Pathfinder: the
// zone manager +0x460 MarkDirty 0x00531431, the map +0x10 and extent
// +0x14..+0x20 are the Pathfinder's). Called once from 0x0052F13D.
// Target evidence: the four corner tests through Bridge::isPointOnBridge
// 0x0027EEAD; with the flag set an obstacle cell (type 4) hands its
// obstacle object (GameLogic::findObjectByID) to the rowed 0x0052DFB1, the
// bit-17 setter 0x0052E001, then a full bridge cell or a far bridge height
// becomes a clear layer-0x10 cell (setters 0x0052E0A1 0x00366500
// 0x0036652D SetType_Dirty 0x0052DA1C, pinched bit cleared), the bridge
// end (isCellOnEnd 0x0027C79C) connects to the given ground cell when the
// bridge height (0x0027FD2A) is within 15 of the given height and keeps
// the wall height (GetWallHeight 0x002EF68C) test otherwise, and a side
// cell is marked type 5; with the flag clear the bridge layer is graded by
// the count of neighbouring cells above layer 0x10. Name unknown.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

enum ObjectID { INVALID_ID = 0 };
enum PathfindLayerEnum { LAYER_INVALID = 0 };

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct Region2D
{
	struct { Real x, y; } lo, hi;
};

class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *loc);
	Real getBridgeHeight(const Coord3D *loc, Coord3D *normal);
	Bool isCellOnEnd(const Region2D *cell);
};

struct PathfindCellInfo
{
	unsigned char m_pad[0x28];
	ObjectID m_obstacleID; // +0x28
};

struct Rva0052DFB1Arg;

class PathfindCell
{
public:
	Int getType() const { return m_bits & 0xF; }
	Int getLayer() const { return (m_bits >> 4) & 0x3F; }
	ObjectID getObstacleID() const { return m_info ? m_info->m_obstacleID : INVALID_ID; }
	void setPinched(Bool pinch) { m_pinched = pinch; }
	Bool rva0052DFB1(const Rva0052DFB1Arg *arg);
	Bool SetType_Dirty(Int type);

	PathfindCellInfo *m_info; // +0x00
	unsigned char m_pad04[0x8];
	union
	{
		struct
		{
			unsigned int m_low : 16;
			unsigned int m_pinched : 1;
			unsigned int m_high : 15;
		};
		unsigned int m_bits; // +0x0C
	};
};

class Rva0052E001
{
public:
	Bool rva0052E001(Bool value);
};

class Rva0052E0A1
{
public:
	Bool rva0052E0A1(Int value);
};

class Rva00366500
{
public:
	Bool rva00366500(Int v);
	Bool rva0036652D(Int v);
};

class PathfindZoneManager
{
public:
	void MarkDirty(Int x, Int y);
};

class Pathfinder
{
public:
	Real GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
	void rva0052E914(Int i, Int j, PathfindCell *cell, Bridge *theBridge, Bool flag, PathfindCell *otherCell, Real height);

private:
	unsigned char m_pad00[0x10];
	PathfindCell **m_map; // +0x10
	struct { Int x, y; } m_lo, m_hi; // +0x14 extent
	unsigned char m_pad24[0x460 - 0x24];
	PathfindZoneManager m_zoneManager; // +0x460
};

#define SET_LAYER(c, v) ((Rva00366500 *)(c))->rva00366500(v)
#define SET_CONNECT_LAYER(c, v) ((Rva00366500 *)(c))->rva0036652D(v)
#define SET_E0A1(c, v) ((Rva0052E0A1 *)(c))->rva0052E0A1(v)
#define SET_E001(c, v) ((Rva0052E001 *)(c))->rva0052E001(v)

void Pathfinder::rva0052E914(Int i, Int j, PathfindCell *cell, Bridge *theBridge, Bool flag, PathfindCell *otherCell, Real height)
{
	Coord3D topLeftCorner, bottomRightCorner;

	topLeftCorner.y = (Real)(j * PATHFIND_CELL_SIZE);
	bottomRightCorner.y = topLeftCorner.y + PATHFIND_CELL_SIZE_F;

	topLeftCorner.x = (Real)(i * PATHFIND_CELL_SIZE);
	bottomRightCorner.x = topLeftCorner.x + PATHFIND_CELL_SIZE_F;

	topLeftCorner.z = 0;
	bottomRightCorner.z = 0;

	Int bridgeCount = 0;
	Coord3D pt;
	if (theBridge->isPointOnBridge(&topLeftCorner))
		bridgeCount++;
	pt = topLeftCorner;
	pt.y = bottomRightCorner.y;
	if (theBridge->isPointOnBridge(&pt))
		bridgeCount++;
	if (theBridge->isPointOnBridge(&bottomRightCorner))
		bridgeCount++;
	pt = topLeftCorner;
	pt.x = bottomRightCorner.x;
	if (theBridge->isPointOnBridge(&pt))
		bridgeCount++;

	if (flag)
	{
		if (bridgeCount != 0 && cell->getType() == 4)
		{
			Object *obj = TheGameLogic->findObjectByID(cell->getObstacleID());
			if (obj)
			{
				cell->rva0052DFB1((const Rva0052DFB1Arg *)obj);
				m_zoneManager.MarkDirty(i, j);
			}
		}
		if (bridgeCount > 0)
		{
			if (SET_E001(cell, true))
				m_zoneManager.MarkDirty(i, j);
		}
		if (bridgeCount == 4)
		{
			Bool changed = SET_E0A1(cell, 0);
			changed |= SET_LAYER(cell, 0x10);
			changed |= SET_CONNECT_LAYER(cell, 0);
			changed |= cell->SetType_Dirty(0);
			if (changed)
				m_zoneManager.MarkDirty(i, j);
			cell->setPinched(false);
			return;
		}
		if (bridgeCount == 0)
			return;

		Region2D cellBounds;
		cellBounds.lo.x = topLeftCorner.x;
		cellBounds.lo.y = topLeftCorner.y;
		cellBounds.hi.x = bottomRightCorner.x;
		cellBounds.hi.y = bottomRightCorner.y;

		Real wallHeight = GetWallHeight((PathfindLayerEnum)cell->getLayer(), &topLeftCorner, 0);
		Real bridgeHeight = theBridge->getBridgeHeight(&topLeftCorner, 0);
		if (theBridge->isCellOnEnd(&cellBounds))
		{
			if (otherCell && fabs(bridgeHeight - height) < 15.0f)
			{
				if (SET_CONNECT_LAYER(cell, otherCell->getLayer()) | SET_E0A1(cell, 0) | SET_LAYER(cell, 0x10) | cell->SetType_Dirty(0))
					m_zoneManager.MarkDirty(i, j);
				SET_CONNECT_LAYER(otherCell, cell->getLayer());
				otherCell->SetType_Dirty(0);
				return;
			}
			if (fabs(wallHeight - bridgeHeight) < 15.0f)
			{
				Bool changed = SET_E0A1(cell, 0);
				changed |= SET_CONNECT_LAYER(cell, 0x10);
				changed |= cell->SetType_Dirty(0);
				if (changed)
					m_zoneManager.MarkDirty(i, j);
			}
			else
			{
				Bool changed = SET_E0A1(cell, 0);
				changed |= SET_LAYER(cell, 0x10);
				changed |= SET_CONNECT_LAYER(cell, 0);
				changed |= cell->SetType_Dirty(0);
				if (changed)
					m_zoneManager.MarkDirty(i, j);
				cell->setPinched(false);
			}
		}
		else
		{
			Bool changed = SET_LAYER(cell, 0x10);
			changed |= cell->SetType_Dirty(5);
			changed |= SET_CONNECT_LAYER(cell, 0);
			if (changed)
				m_zoneManager.MarkDirty(i, j);
		}
		return;
	}

	if (bridgeCount != 0)
	{
		if (SET_E001(cell, false))
			m_zoneManager.MarkDirty(i, j);
		Int count = 0;
		Int maxLayer = 1;
		for (Int x = i - 1; x < i + 2; x++)
		{
			if (x < m_lo.x || x > m_hi.x)
				continue;
			for (Int y = j - 1; y < j + 2; y++)
			{
				if (y < m_lo.y || y > m_hi.y)
					continue;
				if (x == i && j == y)
					continue;
				Int layer = m_map[x][y].getLayer();
				if (layer > 0x10)
				{
					count++;
					maxLayer = layer;
				}
			}
		}
		Int layer = cell->getLayer();
		if (layer == 0x10)
		{
			if (bridgeCount != 4 && count >= 3)
			{
				SET_LAYER(cell, maxLayer);
			}
			else
			{
				SET_LAYER(cell, 1);
				cell->SetType_Dirty(0);
			}
			m_zoneManager.MarkDirty(i, j);
		}
		else if (layer != 1)
		{
			if (cell->SetType_Dirty(5))
				m_zoneManager.MarkDirty(i, j);
		}
		if (SET_CONNECT_LAYER(cell, 0))
			m_zoneManager.MarkDirty(i, j);
	}
	else if (cell->getType() == 2)
	{
		cell->SetType_Dirty(0);
		m_zoneManager.MarkDirty(i, j);
	}
}
