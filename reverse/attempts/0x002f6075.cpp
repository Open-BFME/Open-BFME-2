// ?GetHordeUnitPath@Pathfinder@@QAEPAVPath@@PAVObject@@PBUCoord3D@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// NEAR draft: place at Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderGetHordeUnitPath.cpp
// (the Coord3D include is relative to that path). 1128/1128 bytes, all
// calls and registers match; 45 of 367 instructions differ only in stack
// displacements: retail keeps startCellNdx/goalCellNdx at [ebp-0x20]/[ebp-0x28]
// overlapping the loop spill homes of i/newCostSoFar (frame 0x60), this
// draft puts them below objPos (frame 0x68).
// ?GetHordeUnitPath@Pathfinder@@QAEPAVPath@@PAVObject@@PBUCoord3D@@@Z
// Retail 0x002F6075..0x002F64DD (1128 bytes) thiscall RET 8.
// WorldBuilder twin Pathfinder::GetHordeUnitPath (pathfinder.cpp:11593-11641
// with the DEBUG text *** gethordeunitpath): a 200-cell bounded A* ground
// search from the object cell to the destination cell for a horde member.
// Same shape as the matched CheckPathCost (pathfinder.cpp): cell indices
// through Rva002E7917 and Rva002E7875WorldToCell; the movement check record
// Rva002E8BCF from the AI locomotor set (+0x1CC) and the template priority
// (+0x56C) and flag (+0x634); goal and start cells through getCell; the open
// list through AddToOpenList and rva002F36E5; neighbours through the delta
// tables (VA 0x00DBD3CC and 0x00DBD3AC) with layer connectivity, diagonal
// blocking and the movement check 0x002E6DC4; costs through CalcCostSoFar
// and the cost-to-goal 0x002F0A72 (+10 near flagged cells, +1000 on
// obstacles). The goal builds a Path (new 0x28, ctor 0x00363DC8) through
// PrependCells. Caller: AIUpdateInterface::micropathToPosition 0x0026412B.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};

struct PathfinderTemplateView
{
	char pad[0x56c];
	Int priority;		// +0x56C
	char pad570[0x634 - 0x570];
	Bool flag;		// +0x634
};

class Object
{
public:
	bool rva0028AFBB() const;
	int rva0028B511() const;
	const Coord3D *getPosition() const { return (const Coord3D *)m_position; }
	char *getAI() const { return m_258; }

	void *m_vtable;
	PathfinderTemplateView *m_template;	// +0x04
	char m_pad08[0x38 - 8];
	float m_position[3];			// +0x38
	char m_pad44[0x258 - 0x44];
	char *m_258;				// +0x258, the AI update
};

class Path
{
public:
	Path();					// 0x00363DC8
	void *word0;
	void *firstNode;
	Int word8;
	Bool m_0C;
	char padD[0x28 - 0xd];
};

struct ICoord2DBase { Int x, y; };
struct ICoord2D : ICoord2DBase
{
	bool operator==(const ICoord2DBase &) const;	// 0x00004CAD
};

bool Rva002EBBFBIsOdd(void *);
ICoord2D *Rva002E7875WorldToCell(ICoord2D *, bool, const Coord3D *);
extern "C" int __cdecl abs(int);

struct PathfinderGroundInfo
{
	Int x, y;
	Int parent;
	void *parentWaypoint;			// +0x0C
	unsigned short totalCost, costSoFar;	// +0x10 / +0x12
	char pad14[0x2c - 0x14];
	unsigned int flags;			// +0x2C
};
struct In002E6BA1 { Int x, y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **, Int, In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *, Bool, Int, Bool); Int surfaces; Bool field4, field5; Int maxLayer; Bool fieldC; };
class Rva002E6DC4 { public: Bool rva002E6DC4(void *, void *); };

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR = 0, CELL_OBSTACLE = 4 };

	Bool StartPathfind(Int);
	void ReleaseInfo();
	void SetParentCell(Int *);
	void PutOnClosedList(MixFileInfoBuffer **);
	Int CalcCostSoFar(const Rva002E6C79 *);
	__forceinline void allocateInfo(In002E6BA1 *pos)
	{
		if (!m_pathInfo)
		{
			if (!TheMixFileInfoPool)
				Rva0052DBCDInit();
			m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)this, pos);
		}
		else
			m_pathInfo->parentWaypoint = 0;
	}
	Int getXIndex() const { return m_pathInfo->x; }
	Int getYIndex() const { return m_pathInfo->y; }
	CellType getType() const { return (CellType)m_type; }
	Int getLayer() const { return m_layer; }
	Int getConnectLayer() const { return m_connectLayer; }

	PathfinderGroundInfo *m_pathInfo;
	void *waypoint;
	Int word8;
	unsigned int m_type : 4;		// +0x0C
	unsigned int m_layer : 6;
	unsigned int m_connectLayer : 6;
	unsigned int m_flag16 : 1;
	unsigned int m_rest : 15;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Path *GetHordeUnitPath(Object *obj, const Coord3D *destination);

	void Rva002E7917(ICoord2D *, bool, const Coord3D *);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);	// 0x002E6D62
	PathfindCell *rva002F36E5();
	Int rva002F40E7();
	void CheckChangeLayers(PathfindCell *, Object *);
	Int rva002F0A72(PathfindCell *, PathfindCell *);
	void AddToOpenList(PathfindCell *cell);
	void PrependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);

private:
	char m_pad000[0x34];
	MixFileInfoBuffer *m_closedList;	// +0x34
	char m_pad038[0x48 - 0x38];
	Int m_48;				// +0x48
};

Path *Pathfinder::GetHordeUnitPath(Object *obj, const Coord3D *destination)
{
	m_48 = 0;
	Bool centerInCell = Rva002EBBFBIsOdd(obj);
	const Coord3D *objPos = obj->getPosition();
	ICoord2D startCellNdx;
	{
		Coord3D from;
		from.x = objPos->x;
		from.y = objPos->y;
		from.z = objPos->z;
		Rva002E7917(&startCellNdx, centerInCell, &from);
	}
	ICoord2D goalCellNdx;
	Rva002E7875WorldToCell(&goalCellNdx, centerInCell, destination);
	if (startCellNdx == goalCellNdx)
		return 0;

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	char *ai = obj->getAI();
	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai + 0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(obj, destination);
	PathfindCell *goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);
	if (!goalCell)
		return 0;
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, goalCell))
		return 0;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = getCell(layer, startCellNdx.x, startCellNdx.y);
	if (!parentCell)
		return 0;

	goalCell->allocateInfo((In002E6BA1 *)&goalCellNdx);
	parentCell->allocateInfo((In002E6BA1 *)&startCellNdx);
	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	for (parentCell = rva002F36E5(); parentCell != 0; parentCell = rva002F36E5())
	{
		if (parentCell == goalCell)
		{
			Path *path = new Path;
			PrependCells(path, objPos, goalCell, centerInCell);
			path->m_0C = true;
			rva002F40E7();
			goalCell->ReleaseInfo();
			return path;
		}
		parentCell->PutOnClosedList(&m_closedList);
		if (cellCount > 200)
			break;
		CheckChangeLayers(parentCell, obj);

		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			Int newX = parentCell->getXIndex() + deltaX[i];
			Int newY = parentCell->getYIndex() + deltaY[i];
			ICoord2D newCellCoord;
			newCellCoord.x = newX;
			newCellCoord.y = newY;
			PathfindCell *newCell = getCell((PathfindLayerEnum)parentCell->getLayer(), newX, newY);
			if (!newCell)
				continue;
			if ((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)newCell)->get())
				continue;
			if (newCell->getLayer() != parentCell->getLayer()
				&& newCell->getLayer() != parentCell->getConnectLayer()
				&& newCell->getConnectLayer() != parentCell->getLayer()
				&& !(parentCell->getConnectLayer() == 16 && newCell->getConnectLayer() == parentCell->getConnectLayer()))
				continue;
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, newCell))
			{
				newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
				newCell->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!newCell->m_pathInfo)
				cellCount++;
			newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
			Int newCostSoFar = newCell->CalcCostSoFar((const Rva002E6C79 *)parentCell);
			Int dx = abs(newX - goalCell->getXIndex());
			Int dy = abs(newY - goalCell->getYIndex());
			if (newCell->m_flag16 && dx + dy > 3)
				newCostSoFar += 10;
			newCell->m_pathInfo->flags &= ~1U;
			Int costRemaining = rva002F0A72(newCell, goalCell);
			if (newCell->getType() == PathfindCell::CELL_OBSTACLE)
				newCostSoFar += 1000;
			newCell->m_pathInfo->costSoFar = (unsigned short)newCostSoFar;
			newCell->SetParentCell((Int *)parentCell);
			newCell->m_pathInfo->totalCost = newCell->m_pathInfo->costSoFar + costRemaining;
			AddToOpenList(newCell);
		}
	}
	rva002F40E7();
	goalCell->ReleaseInfo();
	return 0;
}
