// cl: /O1 /Oy- /arch:SSE /G7 /DNDEBUG /MD
// Native 002EE49B..002EE4DE, 67B, RET28. The body does not use its receiver.
// Caller 00471464 loads TheAI->pathfinder into ECX; WB D63210 saves this.
// Both establish a Pathfinder member despite the unused ECX in retail.
// Seven stack words: object/footprint handle then two by-value Coord3D records.
// Existing parity test2EBBFB and world-to-cell2E7875 establish the same
// handle/bool/Coord3D call roles as rowed cell resolver2EBC14. Both 8B cell
// outputs feed the rowed ICoord2D equality operator4CAD. Original name unknown.

#include "PathfinderPositionValue.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/ICoord2DBase.h"

bool __cdecl Rva002EBBFBIsOdd(void *object);
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool odd, const Coord3D *position);

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1,
	LAYER_WALL = 0x10
};

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
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};

enum ObjectID;

class Rva0006E009DwordField
{
public:
	int get()const;
};
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
	Int m_slopeLimitIndex;
	char m_pad570[0x634 - 0x570];
	Bool m_canPathThroughGates;
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
    bool rva002EE49B(Object *object, Rva002EE49BPosition first, Rva002EE49BPosition second);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool IsValidObjectMovement(Object *obj, const Coord3D *oldPos, const Coord3D *newPos);
	char m_pad00[0x08];
	Bool m_isMapReady;
	char m_pad09[0x48 - 0x09];
	ObjectID m_ignoreObstacleID;
};

Bool Pathfinder::IsValidObjectMovement(Object *obj, const Coord3D *oldPos, const Coord3D *newPos)
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
	if (oldCell == asBase(newCell) && oldLayer == newLayer)
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
	else if (!(newLayer == LAYER_GROUND)) {
		return false;
	} else {
		if (oldLayer != LAYER_WALL)
			return false;
	}

	ObjectID saved = m_ignoreObstacleID;
	m_ignoreObstacleID = (ObjectID)((Rva0006E009DwordField *)ai)->get();
	const ThingTemplate *thingTemplate = obj->getTemplate();
	Int maxLayer = thingTemplate->m_slopeLimitIndex;
	Bool flag = thingTemplate->m_canPathThroughGates;
	AIUpdateInterface *aIUpdate = obj->getAI();

	Bool ok;
	{
	Rva002E8BCF info((const Rva002E8BCFSrc *)((char *)aIUpdate + 0x1CC), !flag, maxLayer - 1, (obj->rva0028AFBB()));
	ok = reinterpret_cast<Rva002E6DC4 *>(this)->rva002E6DC4(&info, newC);
	}
	m_ignoreObstacleID = saved;
	return ok?true:false;
 }
}

bool Pathfinder::rva002EE49B(Object *object, Rva002EE49BPosition first, Rva002EE49BPosition second)
{
    bool odd = Rva002EBBFBIsOdd(object);
    ICoord2D firstCell, secondCell;
    return *Rva002E7875WorldToCell(&firstCell, odd, &first)
        == asBase(*Rva002E7875WorldToCell(&secondCell, odd, &second));
}
