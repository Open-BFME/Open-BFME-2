// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?classifyMapCell@Pathfinder@@SAXHHPAVPathfindCell@@@Z retail 0x0052E11A..0x0052E3E6 (716 bytes).
// BFME 2's Pathfinder::classifyMapCell (Zero Hour AIPathfind.cpp; Open-BFME-1
// PathfinderClassifyMapCell.cpp is BFME 1's 0x003F7630 twin): static cdecl
// (i j cell), called per cell from 0x0052F31C. Against BFME 1 the cell type
// is a 4-bit field, the pinched bit is bit 16 and the TerrainLogic +0x58
// query goes through the rowed bit-18 setter 0x0052E05D while +0x5C keeps the
// inline bit-21 store. The water test (TerrainLogic +0x4C with a fifth zero
// argument) grades depth against the two AI data limits at +0x98 (water, 1)
// and +0x9C (type 7) of the data at TheAI +0x18. The obstacle type wins and
// is stored through the rowed PathfindCell::SetType_Dirty 0x0052DA1C. The
// corner heights are still read (TerrainLogic +0x18) and the slope table's
// diagonal entry still initialised (guard 0x00E049EC bit 0 value
// 0x00DD1A38) but no slope grade survives: the slope field is cleared
// through the rowed 0x0052E0A1. Slot names beyond Zero Hour's keep offsets.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#define PATHFIND_CELL_SIZE_F 10.0f

#include "../../../Include/GameLogic/PathfindCell.h"

// Cell types 2 and 7 have no name in PathfindCell::CellType yet.
static const Int CELL_TYPE_CLIFF = 2;
static const Int CELL_TYPE_DEEP_WATER = 7;

// Bit layout of PathfindCell::m_0C as far as this unit uses it: type in
// bits 0..3, pinched in bit 16 (header target facts).
struct PathfindCellPackedBits
{
	unsigned int m_type : 4;
	unsigned int m_low : 12;
	unsigned int m_pinched : 1;
	unsigned int m_high : 15;
};

// PathfindCell::setPinched 0x0052E0FC: retail emits it as a COMDAT and calls
// it out of line; the store is MSVC's single-bit bitfield write.
inline void PathfindCell::setPinched(bool pinch)
{
	reinterpret_cast<PathfindCellPackedBits *>(&m_0C)->m_pinched = pinch;
}

// Retail inlines this packed-dword (+0x0C) write of bit 21.
static __forceinline void setCellBit21(PathfindCell *cell, Bool on)
{
	if (on)
		cell->m_0C |= 0x200000;
	else
		cell->m_0C &= ~0x200000;
}

class Rva0052E05D
{
public:
	bool rva0052E05D(bool value);
};

class Rva0052E0A1
{
public:
	bool rva0052E0A1(int value);
};

#include "../../../Include/GameLogic/TerrainLogic.h"

#include "../../../Include/GameLogic/TAiData.h"
#include "../../../Include/GameLogic/AI.h"

extern TerrainLogic *TheTerrainLogic;

enum PathfindLayerEnum {GROUND_LAYER=1};
#include "../../../../Libraries/Include/Lib/ICoord3D.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
class PolygonTrigger {public: void getBounds(IRegion2D*); bool pointInTrigger(const ICoord3D&);};
#include "../../../Include/GameLogic/PathfindZoneManager.h"
class Pathfinder
{
public:
	static void classifyMapCell(Int i, Int j, PathfindCell *cell);
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 void rva0052E3E6(PolygonTrigger*,bool);
 char m_prefix[0x460];
 PathfindZoneManager m_zones;
};

void Pathfinder::classifyMapCell(Int i, Int j, PathfindCell *cell)
{
	Coord3D bottomRightCorner, topLeftCorner;

	Bool hasObstacle = (cell->getType() == PathfindCell::CELL_OBSTACLE);

	topLeftCorner.y = (Real)j * PATHFIND_CELL_SIZE_F;
	bottomRightCorner.y = topLeftCorner.y + PATHFIND_CELL_SIZE_F;

	topLeftCorner.x = (Real)i * PATHFIND_CELL_SIZE_F;
	bottomRightCorner.x = topLeftCorner.x + PATHFIND_CELL_SIZE_F;

	cell->setPinched(false);

	Int type = PathfindCell::CELL_CLEAR;
	if (TheTerrainLogic->isCliffCell(topLeftCorner.x, topLeftCorner.y))
		type = CELL_TYPE_CLIFF;
	if (TheTerrainLogic->slot22(topLeftCorner.x, topLeftCorner.y))
		((Rva0052E05D *)cell)->rva0052E05D(true);
	else
		((Rva0052E05D *)cell)->rva0052E05D(false);
	setCellBit21(cell, TheTerrainLogic->slot23(topLeftCorner.x, topLeftCorner.y));

	if (type != CELL_TYPE_CLIFF)
	{
		Real waterDepth = TheAI->getAiData()->m_wadeWaterDepth;
		Real deepWaterDepth = TheAI->getAiData()->m_deepWaterDepth;
		Real waterZ, terrainZ;
		Bool underwater;
		underwater = TheTerrainLogic->isUnderwater(topLeftCorner.x, topLeftCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = CELL_TYPE_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(topLeftCorner.x, bottomRightCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = CELL_TYPE_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(bottomRightCorner.x, bottomRightCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = CELL_TYPE_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(bottomRightCorner.x, topLeftCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = CELL_TYPE_DEEP_WATER;
	}

	if (hasObstacle)
		type = PathfindCell::CELL_OBSTACLE;
	cell->SetType_Dirty(type);

	static const Real s_invDistance[3] =
	{
		1.0f / PATHFIND_CELL_SIZE_F,
		1.0f / PATHFIND_CELL_SIZE_F,
		1.0f / ((Real)sqrt(2.0) * PATHFIND_CELL_SIZE_F)
	};

	Real height[4];
	height[0] = TheTerrainLogic->getGroundHeight(topLeftCorner.x, topLeftCorner.y);
	height[1] = TheTerrainLogic->getGroundHeight(topLeftCorner.x, bottomRightCorner.y);
	height[2] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x, topLeftCorner.y);
	height[3] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x, bottomRightCorner.y);

	((Rva0052E0A1 *)cell)->rva0052E0A1(0);
}

// 0x0052E3E6..0x0052E4C2 (220B). Native/WB 0x12DEEA0 prove a polygon
// centre test over bounds divided by the established 10-unit cell size.
// Cell bit18 setter and zone dirty callbacks are existing verified providers.
// The target function name stays address-derived; the untouched Coord3D z
// member is not consumed by the independently verified planar test wrapper.
// getCell's layer enum and the zone manager at +0x460 follow existing rows.
void Pathfinder::rva0052E3E6(PolygonTrigger *area,bool value)
{
 IRegion2D bounds;
 area->getBounds(&bounds);
 bounds.lo.x/=10; bounds.lo.y/=10; bounds.hi.x/=10; bounds.hi.y/=10;
 for(int x=bounds.lo.x;x<=bounds.hi.x;++x) {
  ICoord3D point;
  point.x=x*10+5;
  for(int y=bounds.lo.y;y<=bounds.hi.y;++y) {
   point.y=y*10+5;
   if(area->pointInTrigger(point)) {
    PathfindCell *cell=getCell(GROUND_LAYER,x,y);
    if(cell && ((Rva0052E05D*)cell)->rva0052E05D(value)) m_zones.MarkDirty(x,y);
   }
  }
 }
}
