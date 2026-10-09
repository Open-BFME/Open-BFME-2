// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?computeQuickPath@AIUpdateInterface@@QAE_NPBUCoord3D@@@Z, retail 0x00265C5B
// (432 bytes, RET 4). Zero Hour's AIUpdateInterface::computeQuickPath with
// BFME 2's changes: the existing path is kept when its last node (no
// optimized successor) lies within 0.5 of the destination; aircraft that are
// not projectiles (template kind +0x109 bit 4, +0x10B bit 1) take the rowed
// Pathfinder::GetAircraftPath; others get a plain new Path (operator new 0x28,
// rowed constructor 0x00363DC8) with the destination and the owner's
// position at the destination's height prepended (Path 0x00265596, third
// argument 0x7FFFFFFF), shown when TheWritableGlobalData +0x9B8 is 1. Either
// path is then run through the pinned Path 0x00365E98 with the owner, its 2D
// direction and the +0x14 value of the owner's 0x0028AC4E entry; the
// timestamp (+0x160), AI slot 131, the blocked frame count (+0x16C) and the
// blocked flag (+0x3B8) follow.

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;
extern GameLogic *TheGameLogic;

class PathNode
{
public:
	PathNode *getNextOptimized() const { return m_nextOptimized; }
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad00[0x08];
	PathNode *m_nextOptimized; // +0x08
	Coord3D m_pos; // +0x0C
};

class Path
{
public:
	Path();
	void rva00265596(const Coord3D *pos, PathfindLayerEnum layer, Int limit);
	void rva00365E98(Object *obj, const Coord3D *direction, Int value, Bool flag);
	PathNode *getLastNode() const { return m_lastNode; }
private:
	unsigned char m_pad00[0x08];
	PathNode *m_lastNode; // +0x08
	unsigned char m_pad0C[0x28 - 0x0C];
};

struct Rva002EDEABArg;

class Pathfinder
{
public:
	Path *GetAircraftPath(const Object *obj, const Coord3D *destination);
	void SetDebugPath(Rva002EDEABArg *path);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class GlobalData
{
public:
	unsigned char m_pad0000[0x9B8];
	Int m_debugAI; // +0x9B8
};
extern GlobalData *TheWritableGlobalData;

struct Rva0028AC4EValue
{
	unsigned char m_pad00[0x14];
	Int m_14; // +0x14
};

struct Rva0028AC4EEntry
{
	unsigned char m_pad00[0x04];
	const Rva0028AC4EValue *m_value; // +0x04
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x14]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	void getUnitDirectionVector2D(Coord3D &dir) const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Int rva0028B511() const; // the layer
	Bool isKindOfAircraft() const { return (getTemplate()->m_kindOf[1] & 0x10) != 0; }
	Bool isKindOfProjectile() const { return (getTemplate()->m_kindOf[3] & 2) != 0; }
};

class AIUpdateInterface
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004();
	virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009();
	virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014();
	virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024();
	virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029();
	virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034();
	virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044();
	virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049();
	virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054();
	virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064();
	virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069();
	virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074();
	virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083(); virtual void s084();
	virtual void s085(); virtual void s086(); virtual void s087(); virtual void s088(); virtual void s089();
	virtual void s090(); virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094();
	virtual void s095(); virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103(); virtual void s104();
	virtual void s105(); virtual void s106(); virtual void s107(); virtual void s108(); virtual void s109();
	virtual void s110(); virtual void s111(); virtual void s112(); virtual void s113(); virtual void s114();
	virtual void s115(); virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123(); virtual void s124();
	virtual void s125(); virtual void s126(); virtual void s127(); virtual void s128(); virtual void s129();
	virtual void s130();
	virtual void slot131(); // after a new quick path
	Bool computeQuickPath(const Coord3D *destination);
	void destroyPath();
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad004[0x08 - 0x04];
	Object *m_object; // +0x08
	unsigned char m_pad00C[0x140 - 0x0C];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x160 - 0x144];
	UnsignedInt m_pathTimestamp; // +0x160
	unsigned char m_pad164[0x16C - 0x164];
	Int m_blockedFrames; // +0x16C
	unsigned char m_pad170[0x3B8 - 0x170];
	Bool m_isBlockedAndStuck; // +0x3B8
};

Bool AIUpdateInterface::computeQuickPath(const Coord3D *destination)
{
	Object *obj = getObject();
	const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
	if (m_path)
	{
		PathNode *closeNode = m_path->getLastNode();
		if (closeNode && closeNode->getNextOptimized() == 0)
		{
			Real dxSqr = destination->x - closeNode->getPosition()->x;
			dxSqr *= dxSqr;
			Real dySqr = destination->y - closeNode->getPosition()->y;
			dySqr *= dySqr;
			Real dzSqr = destination->z - closeNode->getPosition()->z;
			dzSqr *= dzSqr;
			if (dxSqr + dySqr + dzSqr < 0.25f)
				return true;
		}
	}
	destroyPath();
	if (obj->isKindOfAircraft() && !obj->isKindOfProjectile())
	{
		m_path = TheAI->pathfinder()->GetAircraftPath(getObject(), destination);
	}
	else
	{
		m_path = new Path;
		m_path->rva00265596(destination, LAYER_GROUND, 0x7FFFFFFF);
		Coord3D pos;
		pos.x = getObject()->getPosition()->x;
		pos.y = getObject()->getPosition()->y;
		pos.z = destination->z;
		m_path->rva00265596(&pos, (PathfindLayerEnum)getObject()->rva0028B511(), 0x7FFFFFFF);
		if (TheWritableGlobalData->m_debugAI == 1)
			TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	}
	Coord3D direction;
	obj->getUnitDirectionVector2D(direction);
	m_path->rva00365E98(obj, &direction, entry->m_value->m_14, false);
	m_pathTimestamp = TheGameLogic->getFrame();
	slot131();
	m_blockedFrames = 0;
	m_isBlockedAndStuck = false;
	return true;
}
