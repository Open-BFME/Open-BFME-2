// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?rva002E8DAA@Pathfinder@@QAEXXZ retail 0x002E8DAA..0x002E8FE5 (571B).
//
// Pathfinder::newMap. Identity: WorldBuilder twin 0xD376F0 Pathfinder::NewMap
// (pathfinder.cpp asserts 1698..1749) and GameLogic 0x002469A5 calling it at
// 0x00246E31 as BFME 1 startNewGame calls TheAI->pathfinder()->newMap().
// Donor shape: Zero Hour AIPathfind.cpp Pathfinder::newMap (bounds by
// REAL_TO_INT_FLOOR of the terrain's maximum pathfind extent; cells and
// column pointers allocated only when the extent changed). BFME 2 read from
// retail: no wall height or wall layer; the 15 layers allocate when
// rva0036666B says they are in use; the terrain's waypoint list (vtable
// +0x84) marks portal cells (WB SetPortal "portal waypoint off map"); the
// zone manager at +0x460 is marked dirty and updated after the objects are
// classified.
// Callees: TerrainLogic slots +0x30 / +0x84 and getLayerForDestination
// 0x002802FE; zone manager 0x005328E2 0x00531342 0x00533BEC; layers
// 0x0036666B 0x0036683D; waypoint test 0x002E6ECA; cell lookup 0x001E3647
// and portal set 0x0052DA63; classifyMap 0x0052F2EC; getFirstObject
// 0x0023CAD2 and object footprint 0x00530212; operator new[] 0x0002FDE0 and
// the eh vector constructor iterator with PathfindCell ctor 0x0052DFF2 and
// dtor 0x0052DD64.
// The waypoint test 0x002E6ECA is rowed with an int return but retail tests
// only al after the call (WB reads its result as a byte): the narrowing cast
// keeps the rowed name. The footprint call 0x00530212 is a thiscall member
// (ecx = this before the call); its only pin spells a stdcall free function.
#include <math.h>
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x, y;
};
struct IRegion2D
{
	ICoord2D lo, hi;
};
struct Region3D
{
	Coord3D lo, hi;
};

#define PATHFIND_CELL_SIZE_F 10.0f

void *__cdecl operator new[](unsigned int size);

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell
{
public:
	PathfindCell();
	~PathfindCell();
private:
	void *m_info;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_flags;
};
typedef PathfindCell *PathfindCellP;

class PathfindLayer
{
public:
	void allocateCells(const IRegion2D *extent);
private:
	char m_pad[0x40];
};

class Rva0036666B
{
public:
	bool rva0036666B();
};

struct Rva005312BERect;

class PathfindZoneManager
{
public:
	void rva005328E2(Rva005312BERect *extent);
	void MarkDirty(Rva005312BERect *extent);
private:
	char m_pad[1];
};

class Rva002E713F460
{
public:
	void rva00533BEC(void *map, void *layers, void *extent);
};

// The terrain's waypoint list: position at +0x0C, next at +0x1C.
class Waypoint
{
public:
	char m_pad00[0x0C];
	Coord3D m_location;
	char m_pad18[0x1C - 0x18];
	Waypoint *m_next;
};

struct Rva002E6ECA
{
	int get() const;
};

class Rva0052DA63
{
public:
	void rva0052DA63(void *waypoint);
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void getMaximumPathfindExtent(Region3D *extent);	// +0x30
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual Waypoint *getFirstWaypoint();	// +0x84
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

class ObjectNextView
{
public:
	char m_pad[0x8C];
	Object *m_next;		// +0x8C
};

class Pathfinder
{
public:
	void rva002E8DAA();
	void Rva0052F2EC();
	void *rva001E3647Pos(int layer, const Coord3D *pos);
	void rva00530212(Object *obj, int insert, int a2, int a3);
private:
	char m_pad00[0x08];
	bool m_isMapReady;			// +0x08
	char m_pad09[0x0C - 0x09];
	PathfindCell *m_blockOfMapCells;	// +0x0C
	PathfindCellP *m_map;			// +0x10
	IRegion2D m_extent;			// +0x14
	char m_pad24[0x60 - 0x24];
	PathfindLayer m_layers[16];		// +0x60
	PathfindZoneManager m_zoneManager;	// +0x460
};

void Pathfinder::rva002E8DAA()
{
	Region3D terrainExtent;
	TheTerrainLogic->getMaximumPathfindExtent(&terrainExtent);
	IRegion2D bounds;
	bounds.lo.x = REAL_TO_INT_FLOOR(terrainExtent.lo.x / PATHFIND_CELL_SIZE_F);
	bounds.hi.x = REAL_TO_INT_FLOOR(terrainExtent.hi.x / PATHFIND_CELL_SIZE_F);
	bounds.lo.y = REAL_TO_INT_FLOOR(terrainExtent.lo.y / PATHFIND_CELL_SIZE_F);
	bounds.hi.y = REAL_TO_INT_FLOOR(terrainExtent.hi.y / PATHFIND_CELL_SIZE_F);
	bounds.hi.x--;
	bounds.hi.y--;
	bool dataAllocated = false;
	if (m_extent.hi.x == bounds.hi.x && m_extent.hi.y == bounds.hi.y) {
		if (m_blockOfMapCells != 0 && m_map != 0) {
			dataAllocated = true;
		}
	}
	if (!dataAllocated) {
		m_extent = bounds;
		m_zoneManager.rva005328E2((Rva005312BERect *)&m_extent);
		m_blockOfMapCells = new PathfindCell[(bounds.hi.x + 1) * (bounds.hi.y + 1)];
		m_map = new PathfindCellP[bounds.hi.x + 1];
		Int i;
		for (i = 0; i <= bounds.hi.x; i++) {
			m_map[i] = &m_blockOfMapCells[i * (bounds.hi.y + 1)];
		}
		for (i = 0; i < 15; i++) {
			if (((Rva0036666B *)&m_layers[i])->rva0036666B()) {
				m_layers[i].allocateCells(&m_extent);
			}
		}
		for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->m_next) {
			if ((unsigned char)((Rva002E6ECA *)way)->get()) {
				void *cell = rva001E3647Pos(TheTerrainLogic->getLayerForDestination(0, &way->m_location), &way->m_location);
				if (cell) {
					((Rva0052DA63 *)cell)->rva0052DA63(way);
				}
			}
		}
	}
	Rva0052F2EC();
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = ((ObjectNextView *)obj)->m_next) {
		rva00530212(obj, 1, 0, 0);
	}
	m_zoneManager.MarkDirty((Rva005312BERect *)&m_extent);
	((Rva002E713F460 *)&m_zoneManager)->rva00533BEC(m_map, m_layers, &m_extent);
	m_isMapReady = true;
}
