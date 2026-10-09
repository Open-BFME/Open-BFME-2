// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?allocateCells@PathfindLayer@@QAEXPBUIRegion2D@@@Z, retail
// 0x0036683D..0x00366AE3 (678B), thiscall ret 4.
//
// Donor: Zero Hour AIPathfind.cpp PathfindLayer::allocateCells (bounds to
// cell origin and extent via REAL_TO_INT_FLOOR / REAL_TO_INT_CEIL with one
// cell of padding, clipped to the map extent, then the cell block and the
// per-column pointers). BFME 2 differences read from retail:
//   * nothing is done when the cells already exist (+0x00);
//   * without a bridge (+0x34, bounds at +0xB4) the bounds are the union of
//     the polygon trigger chain at +0x38 (pinned
//     PolygonTrigger::getBounds 0x002E3978 into an IRegion2D, next at +0x3C;
//     min/max by reference), and with neither nothing is done;
//   * REAL_TO_INT_FLOOR / CEIL go through the CRT floor / ceil imports and
//     the x87 fistp round (as reference/shims/pathfind documents);
//   * every new cell takes the layer's 16-bit +0x2C value at its +0x08.
// Callees: operator new[] 0x0002FDE0 and the CRT eh vector constructor
// iterator 0x00629512 with the cell constructor 0x0052DFF2 and destructor
// 0x0052DD64. WorldBuilder twin 0xF280C0 is PathfindLayer::AllocateCells
// (pathfinder_layer.cpp). Callers 0x002E8F2F 0x0052F746 0x0052F774.
#include <math.h>

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

struct ICoord2D
{
	Int x, y;
};
struct IRegion2D
{
	ICoord2D lo, hi;
};
struct Coord2DView
{
	Real x, y;
};
struct Region2D
{
	Coord2DView lo, hi;
};

#define PATHFIND_CELL_SIZE_F 10.0f

void *__cdecl operator new[](unsigned int size);

__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline Real fast_float_ceil(Real f)
{
	return (Real)ceil((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

template <class T> inline const T &pathfindMin(const T &a, const T &b) { return b < a ? b : a; }
template <class T> inline const T &pathfindMax(const T &a, const T &b) { return a < b ? b : a; }

class PathfindCell
{
public:
	PathfindCell();
	~PathfindCell();
	void setZone(UnsignedShort zone) { m_zone = zone; }
private:
	void *m_info;			// +0x00
	unsigned int m_04;		// +0x04
	UnsignedShort m_zone;		// +0x08
	UnsignedShort m_0A;
	unsigned int m_flags;		// +0x0C
};
typedef PathfindCell *PathfindCellP;

class Bridge
{
public:
	const Region2D *getBounds() const { return &m_bounds; }
private:
	unsigned char m_pad00[0xB4];
	Region2D m_bounds;		// +0xB4
};

class PolygonTrigger
{
public:
	void getBounds(IRegion2D *bounds);
	PolygonTrigger *getNext() { return m_next; }
private:
	unsigned char m_pad00[0x3C];
	PolygonTrigger *m_next;		// +0x3C
};

class PathfindLayer
{
public:
	void allocateCells(const IRegion2D *extent);

private:
	PathfindCell *m_blockOfMapCells;	// +0x00
	PathfindCellP *m_layerCells;		// +0x04
	Int m_width;				// +0x08
	Int m_height;				// +0x0C
	Int m_xOrigin;				// +0x10
	Int m_yOrigin;				// +0x14
	unsigned char m_pad18[0x2C - 0x18];
	UnsignedShort m_zone;			// +0x2C
	unsigned char m_pad2E[0x34 - 0x2E];
	Bridge *m_bridge;			// +0x34
	PolygonTrigger *m_triggers;		// +0x38
};

void PathfindLayer::allocateCells(const IRegion2D *extent)
{
	if (m_blockOfMapCells != 0)
		return;
	Region2D bridgeBounds;
	if (m_bridge)
	{
		bridgeBounds = *m_bridge->getBounds();
	}
	else if (m_triggers)
	{
		IRegion2D bounds;
		m_triggers->getBounds(&bounds);
		bridgeBounds.lo.x = bounds.lo.x;
		bridgeBounds.hi.x = bounds.hi.x;
		bridgeBounds.lo.y = bounds.lo.y;
		bridgeBounds.hi.y = bounds.hi.y;
		for (PolygonTrigger *trig = m_triggers->getNext(); trig; trig = trig->getNext())
		{
			trig->getBounds(&bounds);
			bridgeBounds.lo.x = pathfindMin((Real)bounds.lo.x, bridgeBounds.lo.x);
			bridgeBounds.hi.x = pathfindMax((Real)bounds.hi.x, bridgeBounds.hi.x);
			bridgeBounds.lo.y = pathfindMin((Real)bounds.lo.y, bridgeBounds.lo.y);
			bridgeBounds.hi.y = pathfindMax((Real)bounds.hi.y, bridgeBounds.hi.y);
		}
	}
	else
	{
		return;
	}
	Int maxX, maxY;
	m_xOrigin = REAL_TO_INT_FLOOR((bridgeBounds.lo.x - PATHFIND_CELL_SIZE_F / 100) / PATHFIND_CELL_SIZE_F);
	m_yOrigin = REAL_TO_INT_FLOOR((bridgeBounds.lo.y - PATHFIND_CELL_SIZE_F / 100) / PATHFIND_CELL_SIZE_F);
	m_width = 0;
	m_height = 0;
	maxX = REAL_TO_INT_CEIL((bridgeBounds.hi.x + PATHFIND_CELL_SIZE_F / 100) / PATHFIND_CELL_SIZE_F);
	maxY = REAL_TO_INT_CEIL((bridgeBounds.hi.y + PATHFIND_CELL_SIZE_F / 100) / PATHFIND_CELL_SIZE_F);
	// Pad with 1 extra;
	m_xOrigin--;
	m_yOrigin--;
	maxX++;
	maxY++;

	if (m_xOrigin < extent->lo.x) m_xOrigin = extent->lo.x;
	if (m_yOrigin < extent->lo.y) m_yOrigin = extent->lo.y;
	if (maxX > extent->hi.x) maxX = extent->hi.x;
	if (maxY > extent->hi.y) maxY = extent->hi.y;
	if (maxX <= m_xOrigin) return;
	if (maxY <= m_yOrigin) return;
	m_width = maxX - m_xOrigin;
	m_height = maxY - m_yOrigin;

	m_blockOfMapCells = new PathfindCell[m_width * m_height];
	m_layerCells = new PathfindCellP[m_width];
	Int i;
	for (i = 0; i < m_width; i++)
	{
		m_layerCells[i] = &m_blockOfMapCells[i * m_height];
		for (Int j = 0; j < m_height; j++)
			m_layerCells[i][j].setZone(m_zone);
	}
}
