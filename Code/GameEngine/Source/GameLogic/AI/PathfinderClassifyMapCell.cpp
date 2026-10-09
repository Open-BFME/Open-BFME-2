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
#include "../../../../Libraries/Include/Lib/Coord3D.h"

extern "C" double __cdecl sqrt(double);

typedef bool Bool;
typedef int Int;
typedef float Real;

#define PATHFIND_CELL_SIZE_F 10.0f

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_WATER = 1,
		CELL_CLIFF = 2,
		CELL_OBSTACLE = 4,
		CELL_DEEP_WATER = 7
	};

	// Preserve the native four-bit type read without a competing getter.
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)m_type; }
	void setPinched(Bool pinch) { m_pinched = pinch; }
	bool SetType_Dirty(int type);
	void setBit21(Bool on)
	{
		if (on)
			m_bits |= 0x200000;
		else
			m_bits &= ~0x200000;
	}

private:
	char m_head[0x0C];
	union
	{
		struct
		{
			unsigned int m_type : 4;
			unsigned int m_low : 12;
			unsigned int m_pinched : 1;
			unsigned int m_high : 15;
		};
		unsigned int m_bits;
	};
};

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

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const; // +0x18
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C(); virtual void slot30();
	virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ, void *extra); // +0x4C
	virtual Bool isCliffCell(Real x, Real y) const; // +0x50
	virtual void slot54();
	virtual Bool slot58(Real x, Real y); // +0x58
	virtual Bool slot5C(Real x, Real y); // +0x5C
};

struct Rva0052E11AAiData
{
	char m_pad[0x98];
	Real m_waterDepth; // +0x98
	Real m_deepWaterDepth; // +0x9C
};

class AI
{
public:
	const Rva0052E11AAiData *getAiData() const { return m_aiData; }

private:
	char m_pad[0x18];
	Rva0052E11AAiData *m_aiData; // +0x18
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class Pathfinder
{
public:
	static void classifyMapCell(Int i, Int j, PathfindCell *cell);
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
		type = PathfindCell::CELL_CLIFF;
	if (TheTerrainLogic->slot58(topLeftCorner.x, topLeftCorner.y))
		((Rva0052E05D *)cell)->rva0052E05D(true);
	else
		((Rva0052E05D *)cell)->rva0052E05D(false);
	cell->setBit21(TheTerrainLogic->slot5C(topLeftCorner.x, topLeftCorner.y));

	if (type != PathfindCell::CELL_CLIFF)
	{
		Real waterDepth = TheAI->getAiData()->m_waterDepth;
		Real deepWaterDepth = TheAI->getAiData()->m_deepWaterDepth;
		Real waterZ, terrainZ;
		Bool underwater;
		underwater = TheTerrainLogic->isUnderwater(topLeftCorner.x, topLeftCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = PathfindCell::CELL_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(topLeftCorner.x, bottomRightCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = PathfindCell::CELL_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(bottomRightCorner.x, bottomRightCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = PathfindCell::CELL_DEEP_WATER;
		underwater = TheTerrainLogic->isUnderwater(bottomRightCorner.x, topLeftCorner.y, &waterZ, &terrainZ, 0);
		if (underwater && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (underwater && waterZ - terrainZ > deepWaterDepth)
			type = PathfindCell::CELL_DEEP_WATER;
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
