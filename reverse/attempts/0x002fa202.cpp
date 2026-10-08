// ?AdjustHordeMeleeDestination@Pathfinder@@QAE_NPAVObject@@PAXPAUCoord3D@@@Z
// partial score=0.93 date=2026-10-07
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
struct ICoord2D
{
	Int x;
	Int y;
};

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

class Player
{
public:
	char m_pad00[0x5c];
	Int m_playerType;		// +0x5C (1: computer)
};
// What Object +0x04 points at: a flag byte at +0x10B (bit 1 skips the
// melee-horde adjustment).
struct Rva002FA202Template
{
	char m_pad000[0x10B];
	unsigned char m_10B;
};
class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[4];
	const Rva002FA202Template *m_04;	// +0x04
};
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

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

// TheWritableGlobalData: +0x11F4 is the melee-horde search radius in cells.
class GlobalData
{
public:
	char m_pad0000[0x11F4];
	Int m_11F4;
};
extern GlobalData *TheWritableGlobalData;

bool Rva002EBBFBIsOdd(void *obj);
ICoord2D *Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
struct Rva002E8C23Pair
{
	int m00;
	int m04;
};
int __cdecl Rva002E8C4DCall(int out, unsigned char center, Rva002E8C23Pair *cell, int layer);
extern TerrainLogic *TheTerrainLogic;

// The per-object radius/centre split (rowed 0x002EBCA7).
void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;

// Coord3D::set(const Coord3D *) as Zero Hour's header defines it inline.
static __forceinline void zeroCoord3D(Coord3D *dst)
{
	dst->x = 0.0f;
	dst->y = 0.0f;
	dst->z = 0.0f;
}
static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

// Pathfinder_FuncTightenPath (0x34 bytes): WorldBuilder's functor for
// TightenPath's line walk, Zero Hour's TightenPathStruct plus the goal.
class Pathfinder_FuncTightenPath
{
public:
	Pathfinder_FuncTightenPath(Pathfinder *pathfinder, Object *obj,
		const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
		const Coord3D &goal);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	const LocomotorSet *m_locomotorSet;		// +0x08
	Int m_radius;							// +0x0C
	unsigned char m_center;					// +0x10
	PathfindLayerEnum m_layer;				// +0x14
	Bool m_foundDest;						// +0x18
	Coord3D m_goal;							// +0x1C
	Coord3D m_destPos;						// +0x28
};

// Pathfinder_IsCheckForAdjust (0x3C bytes): WorldBuilder's functor for the
// destination-adjust check; Zero Hour's checkForAdjust info plus the goal,
// an optional second position whose layer wins, a float and a word.
class Pathfinder_IsCheckForAdjust
{
public:
	Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, const Coord3D *layerPos, float range,
		Int arg6);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	void *m_08;								// +0x08
	Bool m_isHuman;							// +0x0C
	unsigned char m_center;					// +0x0D
	Int m_radius;							// +0x10
	const Coord3D *m_layerPos;				// +0x14
	PathfindLayerEnum m_layer;				// +0x18
	float m_range;							// +0x1C
	char m_pad20[0x28 - 0x20];
	Int m_28;								// +0x28
	Int m_2C;								// +0x2C
	Coord3D m_goal;							// +0x30
};

// Pathfinder_IsCheckForMeleeHordeAdjust (0x34 bytes): WorldBuilder's functor
// for the melee/horde destination check; Zero Hour's checkForAdjust info
// (isHuman, radius/centre, layer) plus a float and the goal.
class Pathfinder_IsCheckForMeleeHordeAdjust
{
public:
	Pathfinder_IsCheckForMeleeHordeAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, float range);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	void *m_08;								// +0x08
	Bool m_isHuman;							// +0x0C
	unsigned char m_center;					// +0x0D
	Int m_radius;							// +0x10
	PathfindLayerEnum m_layer;				// +0x14
	float m_range;							// +0x18
	Rva002E8C23Pair m_1C;					// +0x1C (a fallback cell)
	Int m_24;								// +0x24 (non-zero: m_1C is set)
	Coord3D m_goal;							// +0x28
};

// The rowed cell-centre helper 0x002EBC59 (returns its out Coord3D) and the
// pinned 0x002CB35C range probe (WorldBuilder: Weapon::isWithinAttackRange).
void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);
};

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
	unsigned char bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
	Bool CheckForTarget(void *obj, void *a2, void *a3, Rva002CB35CObj *weapon,
		void *a5, void *a6, void *a7, void *a8, Coord3D *out);
	Bool AdjustHordeMeleeDestination(Object *obj, void *arg, Coord3D *dest);
	// 0x002F92BC (unrowed): spiral search from `cell` within `radius` for a
	// cell the functor accepts, stored in `out` (unnamed).
	Bool rva002F92BC(const ICoord2D *cell, Int radius, ICoord2D *out, void *functor);
	void TightenPath(Object *obj, const LocomotorSet &locomotorSet, Coord3D *from, const Coord3D *to);
	int rva002F95B7(const Coord3D *from, const Coord3D *to, PathfindLayerEnum layer, Rva002F600CInfo *info);
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

// Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath, retail 0x002EE43A
// (97 bytes). Name from WorldBuilder (pathfinder.cpp line 11307,
// wb-name-unverified); fields follow Zero Hour's TightenPathStruct.
Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath(Pathfinder *pathfinder,
	Object *obj, const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
	const Coord3D &goal)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_locomotorSet = &locomotorSet;
	m_layer = layer;
	copyCoord3D(&m_goal, &goal);
	zeroCoord3D(&m_destPos);
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_foundDest = false;
}

// Pathfinder::TightenPath, retail 0x002FC95E (83 bytes). Name from
// WorldBuilder (pathfinder.cpp line 11334, wb-name-unverified); Zero Hour's
// Pathfinder::tightenPath with the struct turned into a functor: walks the
// cells from `from` to `to` and moves `from` to the last good position found.
void Pathfinder::TightenPath(Object *obj, const LocomotorSet &locomotorSet,
	Coord3D *from, const Coord3D *to)
{
	Pathfinder_FuncTightenPath info(this, obj, locomotorSet,
		TheTerrainLogic->getLayerForDestination(obj, from), *to);
	rva002F95B7(from, to, info.m_layer, (Rva002F600CInfo *)&info);
	if (info.m_foundDest)
		*from = info.m_destPos;
}

// Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust,
// retail 0x002ED72B (139 bytes). Name from WorldBuilder (pathfinder.cpp line
// 4570, wb-name-unverified); isHuman/radius/layer follow Zero Hour's
// checkForAdjust setup.
Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust(
	Pathfinder *pathfinder, Object *obj, void *arg, const Coord3D &goal,
	float range)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_range = range;
	m_24 = 0;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &goal);
}

// Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust, retail 0x002ED484
// (177 bytes). Name from WorldBuilder (pathfinder.cpp, wb-name-unverified);
// the sibling of Pathfinder_IsCheckForMeleeHordeAdjust, taking its layer
// from the optional second position when one is given.
Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder,
	Object *obj, void *arg, const Coord3D &goal, const Coord3D *layerPos,
	float range, Int arg6)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_layerPos = layerPos;
	m_range = range;
	m_28 = 0;
	m_2C = arg6;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &m_goal);
	if (m_layerPos)
		m_layer = TheTerrainLogic->getLayerForDestination(0, m_layerPos);
}

// Pathfinder::CheckForTarget, retail 0x002F2FA4 (123 bytes). Name from
// WorldBuilder (pathfinder.cpp line 9429, wb-name-unverified). When the
// rowed 0x002F1C25 test passes, takes the 0x002EBC59 cell position and keeps
// it in `out` if the weapon probe (range 10) accepts it.
Bool Pathfinder::CheckForTarget(void *obj, void *a2, void *a3,
	Rva002CB35CObj *weapon, void *a5, void *a6, void *a7, void *a8,
	Coord3D *out)
{
	if (bfmeWrapE6E90(obj, a2, a3, (void *)1, a7, a8))
	{
		Coord3D cell;
		Coord3D pos = *(Coord3D *)rva002EBC59(&cell, obj, (Int)a2, (Int)a3, 1);
		if (weapon->rva002CB35C((Int)obj, &pos, a5, a6, 10.0f, 1))
		{
			*out = pos;
			return true;
		}
	}
	return false;
}

static __forceinline void zeroICoord2D(ICoord2D *c)
{
	c->x = 0;
	c->y = 0;
}

// The centre of a cell (rowed 0x002E8C4D fills a Coord3D and returns it).
static __forceinline Coord3D cellCenter(bool center, Rva002E8C23Pair *cell, PathfindLayerEnum layer)
{
	Coord3D pos;
	return *(Coord3D *)Rva002E8C4DCall((int)&pos, center, cell, layer);
}

// Pathfinder::AdjustHordeMeleeDestination, retail 0x002FA202 (216 bytes).
// Name from WorldBuilder (pathfinder.cpp line 4599, wb-name-unverified).
// Searches around dest's cell for one the melee-horde functor accepts (else
// the functor's fallback cell) and moves dest there.
Bool Pathfinder::AdjustHordeMeleeDestination(Object *obj, void *arg, Coord3D *dest)
{
	if (obj->m_04->m_10B & 2)
		return true;
	bool center = Rva002EBBFBIsOdd(obj);
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, center, dest);
	Pathfinder_IsCheckForMeleeHordeAdjust functor(this, obj, arg, *dest,
		TheTerrainLogic->getLayerHeight(dest->x, dest->y,
			TheTerrainLogic->getLayerForDestination(obj, dest), 0, true));
	ICoord2D found;
	zeroICoord2D(&found);
	if (rva002F92BC(&cell, TheWritableGlobalData->m_11F4, &found, &functor))
	{
		*dest = cellCenter(center, (Rva002E8C23Pair *)&found, functor.m_layer);
		return true;
	}
	if (functor.m_24)
	{
		*dest = cellCenter(center, &functor.m_1C, functor.m_layer);
		return true;
	}
	return false;
}
