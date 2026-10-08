// ??0Bridge@@QAE@AAVRva0027C36A@@PAVDict@@ABVAsciiString@@PAVPolygonTrigger@@@Z
// partial score=0.9 date=2026-10-08
// Banked 2026-10-08 at session wind-down: Bridge::Bridge 0x0027F882 (810 B). Compiles to 810 B; every
// instruction matches except frame slot offsets (retail sub esp,0x24: IRegion2D at ebp-0x30 sharing with the
// center Coord3D at ebp-0x2C, CreateMask at ebp-0x20; this gives 0x2C with region -0x28, mask -0x38) and the
// three unresolved callees setPosition 0x0030AA80, updateObjValuesFromMapProperties 0x002951AB (needs a pin;
// identity: reads Dict keys, sets name +0x88 and initial health) and setOrientation 0x0030AB9D.
// Needs /EHsc; Coord2D toAngle/normalize are a private view here (needs a Coord2D contract extension).
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
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
	void rva002E3978(Int *bounds);
	void getBounds(IRegion2D *bounds) { rva002E3978((Int *)bounds); }
};

class Dict;
class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int m_bits[4];
};

class Object
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
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
	Object *newObject(const ThingTemplate *tmplate, Team *team)
	{
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		return newObject(tmplate, team, &mask, false);
	}
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
	Bridge(BridgeInfo &theInfo, Dict *props, const AsciiString &bridgeTemplateName, PolygonTrigger *outline);
	virtual ~Bridge();
private:
	Bridge *m_next; // +0x04
	AsciiString m_templateName; // +0x08
	BridgeInfo m_bridgeInfo; // +0x0C
	Region2D m_bounds; // +0xB4
	Int m_layer; // +0xC4
	PolygonTrigger *m_outline; // +0xC8
};

// ??0Bridge@@QAE@AAVRva0027C36A@@PAVDict@@ABVAsciiString@@PAVPolygonTrigger@@@Z @0x0027F882
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
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			Object *bridge = TheThingFactory->newObject(genericBridgeTemplate, NULL, &mask, false);
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
			Coord2D v;
			v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.fromLeft.x;
			v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.fromLeft.y;
			bridge->setOrientation( v.toAngle() );

			v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.toRight.x;
			v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.toRight.y;
			v.normalize();

			// get the template of the bridge
			TheTerrainRoads->findBridge( bridgeTemplateName );
		}
	}
}
