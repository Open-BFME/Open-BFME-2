// ?AdjustToNearestGroundCell@Pathfinder@@QAE_NPAUCoord3D@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// wb-lead 2.000 callgraph: Pathfinder::SetBridgeStateRepaired at 0x002E7205.
// Identity evidence: the GeneralsMD AIPathfind.cpp implementation
// Pathfinder::changeBridgeState checks the selected layer, sets its destroyed
// state to the inverse of repaired, then dirties zones with the repaired flag.
// GeneralsMD BridgeBehavior calls that method on bridge damage and repair.
// Target call sites resolve to rowed Rva0036666B at 0x0036666B, unrowed callee
// 0x0036736E and rowed PathfindZoneManager::rva00531481 at 0x00531481. The unrowed
// callee pin is supported by its selected-layer callsite and the GeneralsMD
// PathfindLayer::setDestroyed(Bool) donor. Target arithmetic gives 64-byte
// layers at +0x60 and the final manager-like subobject at +0x460.
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;

class LocomotorSet
{
public:
	LocomotorSurfaceTypeMask getValidSurfaces() const
	{
		return m_validLocomotorSurfaces;
	}
private:
	char m_pad[0x10];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
	Bool m_downhillOnly;
	Bool m_scalesWalls;
};

class Object;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct Rva002E7ED6Info;
class Pathfinder;
struct Rva002E93A7Info
{
	Pathfinder *m_00;
	Int m_04;
};
class PathfindCell;
class Path;

class PathfindCell
{
public:
	// The packed cell word at +0x0C: type in bits 0-3, layer in bits 4-9.
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_OBSTACLE = 4,
		CELL_IMPASSABLE = 5
	};
	enum { LAYER_GROUND = 1 };

	void rva0052DAE9(Bool open);
	CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }

private:
	char m_pad00[0xc];
	unsigned int m_info;			// +0x0C
};

// A locomotor's legal surfaces live in its template (+0x04) at +0x14.
struct LocomotorTemplate
{
	char m_pad00[0x14];
	LocomotorSurfaceTypeMask m_surfaces;	// +0x14
};

class Locomotor
{
public:
	LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
	void *m_vtbl;
	const LocomotorTemplate *m_template;	// +0x04
};

// The surfaces each cell type allows, indexed by type (VA 0x00DBD33C,
// defined in Rva002E6DC4Check.cpp).
extern unsigned int g_00DBD33C[16];

extern "C" __declspec(dllimport) double __cdecl floor(double);

// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline Int realToIntFloor(float f)
{
	float floored = (float)floor((double)f);
	long i;
	__asm {
		fld [floored]
		fistp [i]
	}
	return i;
}

class Rva002F3738
{
public:
	void rva002F3738(void **entry);
};

struct _Rva002E7B02Cell
{
	Int x;
	Int y;
	Int z;
};

class Rva002E7B02
{
public:
	Rva002E7B02(Int a, Int b, const _Rva002E7B02Cell &cell);
private:
	Int m_00;
	Int m_04;
	Int m_08;
	Int m_0C;
	Int m_10;
};

struct Rva002E7B29Info;

struct ICoord2D
{
	Int x;
	Int y;
};

// The bounded world-to-cell conversion (pinned at 0x002E7964): the cell
// under pos, x = -1 outside the map rectangle at Pathfinder+0x14.
class Rva002E7964
{
public:
	void rva002E7964(ICoord2D *out, unsigned char center, const Coord3D *pos);
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip);
};
extern TerrainLogic *TheTerrainLogic;

// TheWritableGlobalData: +0x1204 is the search radius (in cells) the
// nearest-cell adjustments pass on.
class GlobalData
{
public:
	char m_pad0000[0x1204];
	Int m_1204;
};
extern GlobalData *TheWritableGlobalData;

class Rva0036666B
{
public:
	bool rva0036666B();
};

class PathfindLayer
{
public:
	bool setDestroyed(bool destroyed);
private:
	char m_pad[0x40];
};

class PathfindZoneManager
{
public:
	void rva00531481();
};

class Pathfinder
{
public:
	void SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired);
	void ForceMapRecalculation();
	void Rva0052F2EC();
	int rva002EADE1(const Coord3D *a, const Coord3D *b,
		PathfindLayerEnum layer, Rva002E7ED6Info *info);
	int rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E93A7Info *info);
	int rva002EB3D7(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E7B29Info *info);
	Bool IsGroundLineOnly(const Coord3D *startWorld,
		const Coord3D *endWorld);
	Bool IsGroundPathPassable(const Coord3D *startWorld,
		PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter);
	void AddToOpenList(PathfindCell *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);	// 0x002E6D62
	Bool IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos);
	Int AdjustGroundPathPosition(const Coord3D &source, Coord3D &destination);
	Bool AdjustToNearestGroundCell(Coord3D *pos);
	// 0x002EAE5F (unrowed): searches up to `radius` cells around `cell` for
	// one the callback context accepts, storing it in `out` (unnamed).
	Bool rva002EAE5F(const ICoord2D *cell, Int radius, ICoord2D *out, void *context);
protected:
	Path *FindHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher);
	Path *FindClosestHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher, Coord3D *adjustedTo);
	Path *internal_findHierarchicalPath(Bool isHuman,
		LocomotorSurfaceTypeMask locomotorSurface, Object *obj,
		const Coord3D *from, const Coord3D *to, Bool crusher, Bool closestOK,
		Coord3D *adjustedTo);
private:
	char m_pad000[0x10];
	int m_unknown10;
	char m_pad014[0x4c];
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
};

void Pathfinder::SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired)
{
	if (((Rva0036666B *)&m_layers[layer])->rva0036666B()) {
		if (m_layers[layer].setDestroyed(!repaired)) {
			m_zoneManager.rva00531481();
		}
	}
}

void Pathfinder::ForceMapRecalculation()
{
	if (m_unknown10 != 0) {
		Rva0052F2EC();
	}
}

// WB 0xD3EA20 dispatches the ground-layer line test to the rowed helper.
// The retail ABI reuses endWorld's dead parameter slot for callback context.
#pragma optimize("y", off)
Bool Pathfinder::IsGroundLineOnly(const Coord3D *startWorld,
	const Coord3D *endWorld)
{
	return !rva002EADE1(startWorld, endWorld, PATHFIND_LAYER_GROUND,
		(Rva002E7ED6Info *)&endWorld);
}
#pragma optimize("y", on)

// WB 0xD60940 identifies AddToOpenList; retail marks the cell open, then
// appends its pointer through the thiscall helper at 0x002F3738. The queue
// receiver is Pathfinder+0x1D1F0 in the target body.
void Pathfinder::AddToOpenList(PathfindCell *cell)
{
	((PathfindCell *)cell)->rva0052DAE9(true);
	((Rva002F3738 *)((char *)this + 0x1d1f0))->rva002F3738((void **)&cell);
}

// WB 0xD3E820 identifies IsGroundPathPassable. Retail builds callback context
// from this and pathDiameter, then delegates the cell walk to 0x002EED41.
Bool Pathfinder::IsGroundPathPassable(const Coord3D *startWorld,
	PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter)
{
	Rva002E93A7Info info;
	info.m_04 = pathDiameter;
	info.m_00 = this;
	return !rva002EED41(startWorld, endWorld, layer, &info);
}

// WB 0xD4F090 builds the 0x002E7B02 callback context from source and copies
// its adjusted Coord3D back only when the rowed 0x002EB3D7 walk succeeds.
Int Pathfinder::AdjustGroundPathPosition(const Coord3D &source,
	Coord3D &destination)
{
	Rva002E7B02 context((Int)this, 4,
		*(const _Rva002E7B02Cell *)&source);
	Int adjusted = rva002EB3D7(&source, &destination, PATHFIND_LAYER_GROUND,
		(Rva002E7B29Info *)&context);
	if (adjusted != 0) {
		destination = *(Coord3D *)((char *)&context + 8);
	}
	return adjusted;
}

// WB 0xD58AF0: after its two debug-only initialization assertions, the wrapper
// forwards isHuman, the LocomotorSet surface mask, obj, from, to, crusher,
// closestOK=true, and adjustedTo to internal_findHierarchicalPath.
Path *Pathfinder::FindClosestHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher, Coord3D *adjustedTo)
{
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, true, adjustedTo);
}

// WB 0xD588A0 maps this six-argument wrapper to internal_findHierarchicalPath;
// its local Coord3D receives the optional adjusted destination.
Path *Pathfinder::FindHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher)
{
	Coord3D adjustedTo;
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, false, &adjustedTo);
}

// Pathfinder::IsValidMovementTerrain, retail 0x002E7296 (158 bytes): WB's
// name for Zero Hour's Pathfinder::validMovementTerrain (AIPathfind.cpp),
// whose body this is; the per-type surfaces come from the table instead of
// validLocomotorSurfacesForCellType.
Bool Pathfinder::IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos)
{
	Int x = realToIntFloor(pos->x * 0.1f);
	Int y = realToIntFloor(pos->y * 0.1f);

	PathfindCell *toCell = getCell(layer, x, y);
	if (toCell == 0)
		return false;
	if (toCell->getType() == PathfindCell::CELL_OBSTACLE) return true;
	if (toCell->getType() == PathfindCell::CELL_IMPASSABLE) return true;
	if (toCell->getLayer() != PathfindCell::LAYER_GROUND && toCell->getType() == PathfindCell::CELL_CLEAR)
		return true;
	// check validity of destination cell
	LocomotorSurfaceTypeMask acceptableSurfaces = g_00DBD33C[toCell->getType()];
	if ((locomotor->getLegalSurfaces() & acceptableSurfaces) == 0)
		return false;
	return true;
}

// Pathfinder::AdjustToNearestGroundCell, retail 0x002EDCF7 (178 bytes). Name
// from WorldBuilder (pathfinder.cpp line 4978, wb-name-unverified). Moves
// pos to the centre of the nearest acceptable ground cell within the global
// radius (+0x1204), dropping it onto the ground layer's height.
Bool Pathfinder::AdjustToNearestGroundCell(Coord3D *pos)
{
	ICoord2D found;
	{
		ICoord2D cell;
		((Rva002E7964 *)this)->rva002E7964(&cell, 1, pos);
		if (cell.x < 0)
			return false;
		found.x = 0;
		found.y = 0;
		Pathfinder *context = this;
		if (!rva002EAE5F(&cell, TheWritableGlobalData->m_1204, &found, &context))
			return false;
	}
	pos->x = (float)(found.x * 10) + 1.0f;
	pos->y = (float)(found.y * 10) + 1.0f;
	pos->z = TheTerrainLogic->getLayerHeight(pos->x, pos->y, PATHFIND_LAYER_GROUND, 0, true);
	return true;
}
