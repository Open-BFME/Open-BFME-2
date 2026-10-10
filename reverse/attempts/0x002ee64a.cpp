// ?rva002EE64A@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1@Z
// partial score=0.8767381765 date=2026-10-10
// ?IsValidObjectMovement@Pathfinder@@QAE_NXZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva002EE64A@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1@Z retail 0x002EE64A..0x002EE7EE (420B)
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1,
	LAYER_WALL = 0x10
};

struct ICoord2DBase
{
	Int x, y;
};

struct ICoord2D : public ICoord2DBase
{
	Bool operator==(const ICoord2DBase &r) const;
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
bool __cdecl Rva002EBBFBIsOdd(void *obj);
bool __cdecl Rva001E3679(int layer);
int __cdecl Rva002E6E8AGet(int layer);

class PathfindCell
{
public:
	Int getType() const { return m_info & 0xf; }
	Int getLayer() const { return (m_info >> 4) & 0x3f; }
	char m_pad00[0x0C];
	unsigned int m_info;
};

class Object;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva002E8BCFSrc;

class Rva002E8BCF
{
public:
	Rva002E8BCF(const Rva002E8BCFSrc *src, Bool a, Int b, Bool c);
	Int m0;
	Bool m4, m5;
	Int m8;
	Bool mC;
};

class Rva002E6DC4
{
public:
	Bool rva002E6DC4(void *a, void *b);
};

enum ObjectID;

class Rva0006E009DwordField {public:int get()const;};
class AIUpdateInterface
{
public:
	ObjectID getIgnoredObstacleID() const;
	char m_pad00[0x1CC];
	Rva002E8BCFSrc *m_1cc_dummy;
};

struct ThingTemplate
{
	char m_pad00[0x108];
	unsigned char m_kindOf0;
	char m_pad109[0x56C - 0x109];
	Int m_56c;
	char m_pad570[0x634 - 0x570];
	Bool m_634;
};

class Object
{
public:
	Bool rva0028AFBB() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAI() const { return m_ai; }
	char m_pad00[4];
	const ThingTemplate *m_template;
	char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_flags438;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool rva002EE64A(Object *obj, const Coord3D *oldPos, const Coord3D *newPos);
	char m_pad00[0x08];
	Bool m_isMapReady;
	char m_pad09[0x48 - 0x09];
	ObjectID m_ignoreObstacleID;
};

Bool Pathfinder::rva002EE64A(Object *obj, const Coord3D *oldPos, const Coord3D *newPos)
{
	if (obj->m_flags438 & 1) { return true; } else {
	if (obj->getTemplate()->m_kindOf0 & 4)
		return true;
	if (!m_isMapReady)
		return true;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return true;

	PathfindLayerEnum oldLayer, newLayer;
	PathfindCell *oldC;
 union {ICoord2D oldCell; struct {int ignored;PathfindCell *newC;};};
	{
	Bool center = Rva002EBBFBIsOdd(obj);
	ICoord2D newCell;
	Rva002E7875WorldToCell(&oldCell, center, oldPos);
	Rva002E7875WorldToCell(&newCell, center, newPos);
	oldLayer = TheTerrainLogic->getLayerForDestination(obj, oldPos);
	newLayer = TheTerrainLogic->getLayerForDestination(obj, newPos);
	if (oldCell == newCell && oldLayer == newLayer)
		return true;

	oldC = getCell(oldLayer, oldCell.x, oldCell.y);
	newC = getCell(newLayer, newCell.x, newCell.y);
	}
	if (!oldC)
		return false;
	if (!newC)
		return false;
	if (oldC->getLayer() != oldLayer)
		return false;
	if (newC->getLayer() != newLayer)
		return false;

	if (oldLayer == newLayer)
	{
		if (oldC->getType() == newC->getType())
			return true;
	}
	else if (Rva001E3679(newLayer))
	{
		if (oldLayer != LAYER_WALL)
			return false;
	}
	else if (newLayer == LAYER_WALL)
	{
	}
	else if ((char)Rva002E6E8AGet(newLayer))
	{
		if (oldLayer != LAYER_WALL)
			return false;
	}
	else if (newLayer == LAYER_GROUND)
	{
		if (oldLayer != LAYER_WALL)
			return false;
	}
	else
	{
		return false;
	}

	ObjectID saved = m_ignoreObstacleID;
	m_ignoreObstacleID = (ObjectID)((Rva0006E009DwordField *)ai)->get();
	const ThingTemplate *tmpl = obj->getTemplate();
	Int maxLayer = tmpl->m_56c;
	Bool flag = tmpl->m_634;
	AIUpdateInterface *ai2 = obj->getAI();
	Bool extra = obj->rva0028AFBB();
	Bool ok;
	{
	Rva002E8BCF info((const Rva002E8BCFSrc *)((char *)ai2 + 0x1CC), !flag, maxLayer - 1, extra);
	ok = reinterpret_cast<Rva002E6DC4 *>(this)->rva002E6DC4(&info, newC);
	}
	m_ignoreObstacleID = saved;
	return ok?true:false;
 }
}
