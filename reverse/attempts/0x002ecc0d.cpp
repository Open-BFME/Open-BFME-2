// ?rva002ECC0D@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.9317013464 date=2026-10-09
// ?rva002ECC0D@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.93 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR draft for Code/GameEngine/Source/GameLogic/AI/PathfinderRva002ECC0D.cpp
// (relative include assumes that path).
// ?rva002ECC0D@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z retail 0x002ECC0D
// (342 bytes ret 8). Can the object stand at the point: TCheckMovementInfo
// cleared (0x002E6FDF) radius/center (0x002EBCA7) cell (0x002E7875) layer
// (Object 0x0028B511) every cell of the footprint passes getCell 0x002E6D62
// and the locomotor check 0x002E6DC4 then checkForMovement 0x002EA34A and
// CalcCollisionFreeExtraCosts 0x002EC0A2 == 0.
// Remaining diff: retail keeps the outer offset i in ebx and the inner j in
// the dead obj argument slot with the outer loop entered by jmp-to-test;
// cl here swaps the two (i in memory j in ebx) and guards the outer loop.
#include "Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

struct ICoord2D
{
	Int x;
	Int y;
};

// The converter's out buffer is a compiler temporary (it shares its slot
// with the later locomotor view).
struct Rva002ECC0DCell : ICoord2D
{
	Rva002ECC0DCell() {}
};

struct TCheckMovementInfo
{
	ICoord2D cell; // +0x00
	PathfindLayerEnum layer; // +0x08
	Int radius; // +0x0C
	Bool centerInCell; // +0x10
	Bool m_11; // +0x11
	unsigned char m_pad12[2];
	UnsignedInt m_14; // +0x14 acceptable surfaces
	ObjectID m_18; // +0x18 an object to ignore
	unsigned char m_1C[0x10]; // +0x1C
	Int m_2C;
	Bool m_30;
	Bool m_31;
	Bool m_32;
	unsigned char m_pad33;
	Int m_34; // +0x34
};

class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
};

struct Rva002E8BCFSrc;
class Rva002E8BCF
{
public:
	Rva002E8BCF(Rva002E8BCFSrc const *src, bool a, int b, bool c);
	int m0;
	bool m4;
	bool m5;
	int m8;
	bool mC;
};

class Rva002E6DC4
{
public:
	Bool rva002E6DC4(void *data, void *cell);
};

void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd);
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class AIUpdateInterface
{
public:
	ObjectID getIgnoredObstacleID() const;
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x110];
	UnsignedInt m_kindOf110; // +0x110
	unsigned char m_pad114[0x56C - 0x114];
	Int m_56C; // +0x56C
	unsigned char m_pad570[0x634 - 0x570];
	Bool m_634; // +0x634
};

class Object
{
public:
	Int rva0028B511() const;
	Bool rva0028AFBB() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x258 - 0x08];
	AIUpdateInterface *m_ai; // +0x258
};

class PathfindCell;
struct Rva002EBC7FPair;

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool checkForMovement(Object *obj, TCheckMovementInfo &info);
	Int CalcCollisionFreeExtraCosts(Object *obj, PathfindCell *cell, Rva002EBC7FPair *info,
		PathfindLayerEnum layer, Int radius, Int extent, bool flag);
	Bool rva002ECC0D(Object *obj, const Coord3D *pos);
};

Bool Pathfinder::rva002ECC0D(Object *obj, const Coord3D *pos)
{
	TCheckMovementInfo info;
	reinterpret_cast<Rva002E6FDF *>(&info)->rva002E6FDF();
	Rva002EBCA7Split(obj, &info.radius, reinterpret_cast<unsigned char *>(&info.centerInCell));
	{
		ICoord2D cell;
		const ICoord2D *result = Rva002E7875WorldToCell(&cell, info.centerInCell, pos);
		Int cx = result->x;
		Int cy = result->y;
		info.cell.y = cy;
		info.cell.x = cx;
	}
	info.layer = (PathfindLayerEnum)obj->rva0028B511();

	{
		Int extent = obj->getTemplate()->m_56C;
		Bool flag = obj->getTemplate()->m_634;
		Rva002E8BCF loco(reinterpret_cast<const Rva002E8BCFSrc *>((char *)obj->getAI() + 0x1CC),
			!flag, extent - 1, obj->rva0028AFBB());

		Int start = -info.radius;
		for (Int i = start; i < info.radius; i++)
		{
			volatile Int j = start;
			if (j < info.radius)
			{
				Int x = info.cell.x + i;
				do
				{
					PathfindCell *c = getCell(info.layer, x, info.cell.y + j);
					if (c == 0)
						return false;
					if (!reinterpret_cast<Rva002E6DC4 *>(this)->rva002E6DC4(&loco, c))
						return false;
					j++;
				} while (j < info.radius);
			}
		}
	}

	info.m_14 = (obj->getTemplate()->m_kindOf110 & 0x4000000) ? 1 : 0x10;
	info.m_11 = false;
	info.m_18 = obj->getAI() ? obj->getAI()->getIgnoredObstacleID() : INVALID_ID;
	if (!checkForMovement(obj, info))
		return false;
	return CalcCollisionFreeExtraCosts(obj, 0, reinterpret_cast<Rva002EBC7FPair *>(&info), info.layer,
		info.radius, info.radius + (info.centerInCell ? 1 : 0), false) == 0;
}
