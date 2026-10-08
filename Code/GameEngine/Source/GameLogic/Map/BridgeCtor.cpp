// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Bridge::Bridge (0x0027F882, 810 bytes), after Zero Hour's TerrainLogic.cpp
// Bridge constructor (GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp).
//
// Target facts: the 0xCC-byte bridge stores vftable 0x00BFB1E0, copies the
// 0xA8-byte bridge info (copy constructor 0x0027C410) to +0x0C, keeps the
// template name at +0x08, the bounds at +0xB4, the layer at +0xC4 and the
// outline polygon at +0xC8; the bounds are widened by the outline's integer
// bounds (PolygonTrigger::getBounds 0x002E3978). With a property dict it
// creates the "GenericBridge" object through the 4-argument
// ThingFactory::newObject (0x002D0A23) under a function-static template,
// positions it at the bridge centre (Thing::setPosition 0x0030AA80), applies
// the map properties (0x002951AB) and orients it (Coord2D::toAngle 0x00005923,
// Thing::setOrientation 0x0030AB9D), then normalizes a side vector and looks
// up the bridge road type (0x002DB4DA) without using either result.
//
// TerrainLogic::addBridgeToLogic (0x00280294, 106 bytes) and
// addLandmarkBridgeToLogic (0x0028125C, 99 bytes) push a new bridge on the
// list at TerrainLogic+0x40, register it with the pathfinder (TheAI+0x10,
// 0x002E71BF) and store the returned layer at Bridge+0xC4.
//
// Carried from the donor: member names, the order of the bound tests and the
// _STL::min/max widening. Structural inference: retail's 0x24-byte frame
// shares the create mask's slot with the side vector and the outline bounds'
// slot with the centre, which MSVC 7.1 does only for locals of disjoint
// scopes, so both sit in their own blocks.
#include "ascii_string.h"
#include "Lib/Coord3D.h"

#include <algorithm>
#include <string.h>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};

enum BodyDamageType
{
	BODY_PRISTINE = 0
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

// class-gate: allow Coord2D the canonical data-only header cannot declare BFME 2's out-of-line toAngle (rowed 0x00005923) and normalize (rowed 0x0000378A) that the constructor calls; same two floats
class Coord2D
{
public:
	Real x;
	Real y;
	Real toAngle() const;
	void normalize();
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Rva0027C36A
{
public:
	Rva0027C36A(const Rva0027C36A &other);

	Coord3D from; // +0x00
	Coord3D to; // +0x0C
	Real bridgeWidth; // +0x18
	Coord3D fromLeft; // +0x1C
	Coord3D fromRight; // +0x28
	Coord3D toLeft; // +0x34
	Coord3D toRight; // +0x40
	Int bridgeIndex; // +0x4C
	BodyDamageType curDamageState; // +0x50
	ObjectID bridgeObjectID; // +0x54
	ObjectID towerObjectID[4]; // +0x58
	Bool damageStateChanged; // +0x68
private:
	char m_pad69[0xA8 - 0x69];
};
typedef Rva0027C36A BridgeInfo;

class PolygonTrigger
{
public:
	void getBounds(IRegion2D *bounds);
};

class Dict;
class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int m_bits[4];
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	void updateObjValuesFromMapProperties(Dict *properties);
private:
	char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};
extern ThingFactory *TheThingFactory;

class TerrainRoadType;
class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
};
extern TerrainRoadCollection *TheTerrainRoads;

class Bridge
{
public:
	Bridge(BridgeInfo &theInfo, Dict *props, const AsciiString &bridgeTemplateName, PolygonTrigger *outline = NULL);
	Bridge(Object *bridgeObj);
	virtual ~Bridge();

	void setNext(Bridge *next) { m_next = next; }
	void setLayer(Int layer) { m_layer = layer; }
private:
	Bridge *m_next; // +0x04
	AsciiString m_templateName; // +0x08
	BridgeInfo m_bridgeInfo; // +0x0C
	Region2D m_bounds; // +0xB4
	Int m_layer; // +0xC4
	PolygonTrigger *m_outline; // +0xC8
};

Bridge::Bridge(BridgeInfo &theInfo, Dict *props, const AsciiString &bridgeTemplateName, PolygonTrigger *outline) :
m_next(NULL),
m_bridgeInfo(theInfo),
m_layer(LAYER_INVALID),
m_outline(outline)
{
	// save the template name
	m_templateName = bridgeTemplateName;

	m_bounds.lo.x = m_bridgeInfo.fromLeft.x;
	m_bounds.lo.y = m_bridgeInfo.fromLeft.y;
	m_bounds.hi = m_bounds.lo;
	if (m_bounds.lo.x > m_bridgeInfo.fromRight.x) m_bounds.lo.x = m_bridgeInfo.fromRight.x;
	if (m_bounds.lo.y > m_bridgeInfo.fromRight.y) m_bounds.lo.y = m_bridgeInfo.fromRight.y;
	if (m_bounds.hi.x < m_bridgeInfo.fromRight.x) m_bounds.hi.x = m_bridgeInfo.fromRight.x;
	if (m_bounds.hi.y < m_bridgeInfo.fromRight.y) m_bounds.hi.y = m_bridgeInfo.fromRight.y;
	if (m_bounds.lo.x > m_bridgeInfo.toLeft.x) m_bounds.lo.x = m_bridgeInfo.toLeft.x;
	if (m_bounds.lo.y > m_bridgeInfo.toLeft.y) m_bounds.lo.y = m_bridgeInfo.toLeft.y;
	if (m_bounds.hi.x < m_bridgeInfo.toLeft.x) m_bounds.hi.x = m_bridgeInfo.toLeft.x;
	if (m_bounds.hi.y < m_bridgeInfo.toLeft.y) m_bounds.hi.y = m_bridgeInfo.toLeft.y;
	if (m_bounds.lo.x > m_bridgeInfo.toRight.x) m_bounds.lo.x = m_bridgeInfo.toRight.x;
	if (m_bounds.lo.y > m_bridgeInfo.toRight.y) m_bounds.lo.y = m_bridgeInfo.toRight.y;
	if (m_bounds.hi.x < m_bridgeInfo.toRight.x) m_bounds.hi.x = m_bridgeInfo.toRight.x;
	if (m_bounds.hi.y < m_bridgeInfo.toRight.y) m_bounds.hi.y = m_bridgeInfo.toRight.y;

	if (m_outline)
	{
		IRegion2D outlineBounds;
		outline->getBounds(&outlineBounds);
		m_bounds.lo.x = _STL::min((Real)outlineBounds.lo.x, m_bounds.lo.x);
		m_bounds.lo.y = _STL::min((Real)outlineBounds.lo.y, m_bounds.lo.y);
		m_bounds.hi.x = _STL::max((Real)outlineBounds.hi.x, m_bounds.hi.x);
		m_bounds.hi.y = _STL::max((Real)outlineBounds.hi.y, m_bounds.hi.y);
	}

	m_bridgeInfo.curDamageState = BODY_PRISTINE;
	m_bridgeInfo.bridgeObjectID = INVALID_ID;

	if (props)
	{
		static const ThingTemplate* genericBridgeTemplate = TheThingFactory->findTemplate("GenericBridge");
		if (genericBridgeTemplate)
		{
			Object *bridge;
			{
				CreateMask mask;
				memset(&mask, 0, sizeof(mask));
				bridge = TheThingFactory->newObject(genericBridgeTemplate, NULL, &mask, false);
			}
			Coord3D center;
			center.x = (m_bridgeInfo.fromLeft.x + m_bridgeInfo.toRight.x)/2.0f;
			center.y = (m_bridgeInfo.fromLeft.y + m_bridgeInfo.toRight.y)/2.0f;
			center.z = (m_bridgeInfo.fromLeft.z + m_bridgeInfo.toRight.z)/2.0f;
			bridge->setPosition(&center);
			m_bridgeInfo.bridgeObjectID = bridge->getID();
			bridge->updateObjValuesFromMapProperties(props);

			//
			// we'll say the angle of this object representing the bridge is from the 'from' side
			// to the 'to' side.
			//
			{
				Coord2D v;
				v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.fromLeft.x;
				v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.fromLeft.y;
				bridge->setOrientation( v.toAngle() );

				v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.toRight.x;
				v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.toRight.y;
				v.normalize();
			}

			// get the template of the bridge
			TheTerrainRoads->findBridge( bridgeTemplateName );
		}
	}
}

// The rowed name of 0x002E71BF takes and returns an Int; it is Zero Hour's
// Pathfinder::addBridge(Bridge *), returning the bridge's pathfind layer.
class Pathfinder
{
public:
	Int AddBridge(Int bridge);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void addBridgeToLogic(BridgeInfo *pInfo, Dict *props, const AsciiString &bridgeTemplateName);
	virtual void addLandmarkBridgeToLogic(Object *bridgeObj);
private:
	char m_pad04[0x40 - 0x04];
	Bridge *m_bridgeListHead; // +0x40
};

void TerrainLogic::addBridgeToLogic(BridgeInfo *pInfo, Dict *props, const AsciiString &bridgeTemplateName)
{
	Bridge *pBridge = new Bridge(*pInfo, props, bridgeTemplateName);
	pBridge->setNext(m_bridgeListHead);
	m_bridgeListHead = pBridge;
	Int layer = TheAI->pathfinder()->AddBridge((Int)pBridge);
	pBridge->setLayer(layer);
}

void TerrainLogic::addLandmarkBridgeToLogic(Object *bridgeObj)
{
	Bridge *pBridge = new Bridge(bridgeObj);
	pBridge->setNext(m_bridgeListHead);
	m_bridgeListHead = pBridge;
	Int layer = TheAI->pathfinder()->AddBridge((Int)pBridge);
	pBridge->setLayer(layer);
}
