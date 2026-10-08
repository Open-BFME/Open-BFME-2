// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Bridge::Bridge(Object *) (0x00280C21, 1449 bytes) and Bridge::createTower
// (0x0027EDBC, 241 bytes), after Zero Hour's TerrainLogic.cpp
// (GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp) and the
// matched BFME 1 BridgeObjectCtor.cpp / Bridge_createTower_Thunk.cpp.
//
// Target facts: the landmark-bridge constructor default-constructs the
// 0xA8-byte bridge info (0x0027C36A) at +0x0C, copies the bridge object's
// template name, derives the four corners from its position (+0x38), angle
// (+0x44) and box radii (+0xCC/+0xD0, Cos 0x0002FBC0, Sin 0x0002FBB0), and,
// unlike Zero Hour, also copies them into the info's four-point polygon at
// +0x6C (from-left, from-right, to-right, to-left) and stores the two
// triangles 0,1,2 and 0,2,3 at +0x9C. The tower positions are an array built
// and torn down by the eh vector iterators with Coord3D's constructor
// 0x0047A6A9 and destructor 0x000B3FD0; the tower offset is the tower
// template's major radius (template +0xB0); the tower ID is stored without a
// null test. createTower zeroes a 16-byte create mask, passes the bridge's
// team (+0x304) to the 4-argument ThingFactory::newObject, turns the from
// side by pi (constant 0x00BC7468), and copies the bridge body's
// indestructible flag (body +0x254, slots +0x88/+0x84).
//
// Carried from the donors: member and local names, the corner formulas and
// the four separate switch cases of createTower. Structural inference: the
// polygon and triangle members are written in source order before the
// bounds; the scheduler interleaves the triangle stores with them.
#include "ascii_string.h"

#include <string.h>

typedef bool Bool;
typedef int Int;
typedef short Short;
typedef float Real;

#define NULL 0

extern Real Cos(Real);
extern Real Sin(Real);

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

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_TOWER_FROM_RIGHT,
	BRIDGE_TOWER_TO_LEFT,
	BRIDGE_TOWER_TO_RIGHT,
	BRIDGE_MAX_TOWERS
};

const Real PI = 3.14159265359f;
const Real PATHFIND_CELL_SIZE_F = 10.0f;

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
};

// class-gate: allow Coord3D the tower array is built and torn down through BFME 2's out-of-line Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; the three floats live in Coord3DBase as in coord3d.cpp
struct Coord3D : public Coord3DBase
{
	Coord3D();
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	~Coord3D() {}
};

// class-gate: allow Coord2D the canonical data-only header cannot declare BFME 2's out-of-line normalize (rowed 0x0000378A) that the constructor calls; same two floats
class Coord2D
{
public:
	Real x;
	Real y;
	void normalize();
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Rva0027C36A
{
public:
	Rva0027C36A();

	Coord3DBase from; // +0x00
	Coord3DBase to; // +0x0C
	Real bridgeWidth; // +0x18
	Coord3DBase fromLeft; // +0x1C
	Coord3DBase fromRight; // +0x28
	Coord3DBase toLeft; // +0x34
	Coord3DBase toRight; // +0x40
	Int bridgeIndex; // +0x4C
	BodyDamageType curDamageState; // +0x50
	ObjectID bridgeObjectID; // +0x54
	ObjectID towerObjectID[BRIDGE_MAX_TOWERS]; // +0x58
	Bool damageStateChanged; // +0x68
	Coord3DBase polygon[4]; // +0x6C
	Short triangles[6]; // +0x9C
};
typedef Rva0027C36A BridgeInfo;

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getMinorRadius() const { return m_minorRadius; }
private:
	void *m_vptr;
	char m_pad04[0x10 - 0x04];
	Real m_majorRadius; // +0x10
	Real m_minorRadius; // +0x14
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
private:
	char m_pad00[0x64];
	AsciiString m_name; // +0x64
	char m_pad68[0xA0 - 0x68];
	GeometryInfo m_geometryInfo; // +0xA0
};

class Team;

struct CreateMask
{
	unsigned int m_bits[4];
};

class BodyModuleInterface
{
public:
	virtual void bmi00() = 0;
	virtual void bmi01() = 0;
	virtual void bmi02() = 0;
	virtual void bmi03() = 0;
	virtual void bmi04() = 0;
	virtual void bmi05() = 0;
	virtual void bmi06() = 0;
	virtual void bmi07() = 0;
	virtual void bmi08() = 0;
	virtual void bmi09() = 0;
	virtual void bmi10() = 0;
	virtual void bmi11() = 0;
	virtual void bmi12() = 0;
	virtual void bmi13() = 0;
	virtual void bmi14() = 0;
	virtual void bmi15() = 0;
	virtual void bmi16() = 0;
	virtual void bmi17() = 0;
	virtual void bmi18() = 0;
	virtual void bmi19() = 0;
	virtual void bmi20() = 0;
	virtual void bmi21() = 0;
	virtual void bmi22() = 0;
	virtual void bmi23() = 0;
	virtual void bmi24() = 0;
	virtual void bmi25() = 0;
	virtual void bmi26() = 0;
	virtual void bmi27() = 0;
	virtual void bmi28() = 0;
	virtual void bmi29() = 0;
	virtual void bmi30() = 0;
	virtual void bmi31() = 0;
	virtual void bmi32() = 0;
	virtual void setIndestructible(Bool indestructible) = 0; // +0x84
	virtual Bool isIndestructible() const = 0; // +0x88
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_cachedPos; // +0x38
	Real m_cachedAngle; // +0x44
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Team *getTeam() const { return m_team; }
private:
	char m_pad48[0x74 - 0x48];
	ObjectID m_id; // +0x74
	char m_pad78[0xBC - 0x78];
	GeometryInfo m_geometryInfo; // +0xBC
	char m_padD4[0x254 - 0xD4];
	BodyModuleInterface *m_body; // +0x254
	char m_pad258[0x304 - 0x258];
	Team *m_team; // +0x304
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};
extern ThingFactory *TheThingFactory;

class TerrainRoadType
{
public:
	AsciiString getTowerObjectName(BridgeTowerType type);
};

class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
};
extern TerrainRoadCollection *TheTerrainRoads;

class BridgeBehaviorInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;
};

class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge) = 0;
	virtual ObjectID getBridgeID() = 0;
	virtual void setTowerType(BridgeTowerType type) = 0;
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

class BridgeTowerBehavior
{
public:
	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *obj);
};

class Bridge
{
public:
	Bridge(Object *bridgeObj);
	virtual ~Bridge();
	Object *createTower(Coord3D *worldPos, BridgeTowerType towerType, const ThingTemplate *towerTemplate, Object *bridge);
private:
	Bridge *m_next; // +0x04
	AsciiString m_templateName; // +0x08
	BridgeInfo m_bridgeInfo; // +0x0C
	Region2D m_bounds; // +0xB4
	Int m_layer; // +0xC4
	void *m_outline; // +0xC8
};

Bridge::Bridge(Object *bridgeObj) :
m_next(NULL),
m_layer(LAYER_INVALID),
m_outline(NULL)
{
	// save the template name
	m_templateName = bridgeObj->getTemplate()->getName();

	const Coord3D *pos = bridgeObj->getPosition();
	Real angle = bridgeObj->getOrientation();

	Real halfsizeX = bridgeObj->getGeometryInfo().getMajorRadius();
	Real halfsizeY = bridgeObj->getGeometryInfo().getMinorRadius();
	m_bridgeInfo.bridgeWidth = 2*halfsizeY;

	Real c = (Real)Cos(angle);
	Real s = (Real)Sin(angle);

	m_bridgeInfo.fromLeft.set(pos->x-halfsizeX*c-halfsizeY*s, pos->y + halfsizeY*c - halfsizeX*s, pos->z);
	m_bridgeInfo.toLeft.set(pos->x+halfsizeX*c-halfsizeY*s, pos->y + halfsizeY*c + halfsizeX*s, pos->z);
	m_bridgeInfo.fromRight.set(pos->x-halfsizeX*c+halfsizeY*s, pos->y - halfsizeY*c - halfsizeX*s, pos->z);
	m_bridgeInfo.toRight.set(pos->x+halfsizeX*c+halfsizeY*s, pos->y - halfsizeY*c + halfsizeX*s, pos->z);

	m_bridgeInfo.polygon[0].set(m_bridgeInfo.fromLeft.x, m_bridgeInfo.fromLeft.y, m_bridgeInfo.fromLeft.z);
	m_bridgeInfo.polygon[1].set(m_bridgeInfo.fromRight.x, m_bridgeInfo.fromRight.y, m_bridgeInfo.fromRight.z);
	m_bridgeInfo.polygon[2].set(m_bridgeInfo.toRight.x, m_bridgeInfo.toRight.y, m_bridgeInfo.toRight.z);
	m_bridgeInfo.polygon[3].set(m_bridgeInfo.toLeft.x, m_bridgeInfo.toLeft.y, m_bridgeInfo.toLeft.z);

	m_bridgeInfo.from.x = (m_bridgeInfo.fromLeft.x + m_bridgeInfo.fromRight.x)/2.0f;
	m_bridgeInfo.from.y = (m_bridgeInfo.fromLeft.y + m_bridgeInfo.fromRight.y)/2.0f;
	m_bridgeInfo.from.z = (m_bridgeInfo.fromLeft.z + m_bridgeInfo.fromRight.z)/2.0f;

	m_bridgeInfo.to.x = (m_bridgeInfo.toLeft.x + m_bridgeInfo.toRight.x)/2.0f;
	m_bridgeInfo.to.y = (m_bridgeInfo.toLeft.y + m_bridgeInfo.toRight.y)/2.0f;
	m_bridgeInfo.to.z = (m_bridgeInfo.toLeft.z + m_bridgeInfo.toRight.z)/2.0f;

	m_bridgeInfo.triangles[0] = 0;
	m_bridgeInfo.triangles[1] = 1;
	m_bridgeInfo.triangles[2] = 2;
	m_bridgeInfo.triangles[3] = 0;
	m_bridgeInfo.triangles[4] = 2;
	m_bridgeInfo.triangles[5] = 3;

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

	m_bridgeInfo.curDamageState = BODY_PRISTINE;

	m_bridgeInfo.bridgeObjectID = bridgeObj->getID();

	// get the template of the bridge
	AsciiString bridgeTemplateName = bridgeObj->getTemplate()->getName();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );
	if( bridgeTemplate == NULL ) {
		return;
	}

	Coord2D v;
	v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.toRight.x;
	v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.toRight.y;
	v.normalize();

	// initialize each of the tower positions to that of the bridge info bounding rect
	Coord3D towerPos[ BRIDGE_MAX_TOWERS ];
	static_cast<Coord3DBase &>(towerPos[ BRIDGE_TOWER_FROM_LEFT ]) = m_bridgeInfo.fromLeft;
	static_cast<Coord3DBase &>(towerPos[ BRIDGE_TOWER_FROM_RIGHT ]) = m_bridgeInfo.fromRight;
	static_cast<Coord3DBase &>(towerPos[ BRIDGE_TOWER_TO_LEFT ]) = m_bridgeInfo.toLeft;
	static_cast<Coord3DBase &>(towerPos[ BRIDGE_TOWER_TO_RIGHT ]) = m_bridgeInfo.toRight;

	Real offset = PATHFIND_CELL_SIZE_F/2.0f;
	// create objects targetable objects for the 4 tower pieces
	const ThingTemplate *towerTemplate;
	BridgeTowerType type;
	Object *tower;
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{

		type = (BridgeTowerType)i;
		towerTemplate = TheThingFactory->findTemplate( bridgeTemplate->getTowerObjectName( type ) );
		if (towerTemplate) {
			offset = towerTemplate->getTemplateGeometryInfo().getMajorRadius();
		}
		Coord3D pos = towerPos[type];
		switch( type )
		{
			case BRIDGE_TOWER_FROM_LEFT:
			case BRIDGE_TOWER_TO_LEFT:
				pos.x += v.x*offset;
				pos.y += v.y*offset;
				break;
			case BRIDGE_TOWER_FROM_RIGHT:
			case BRIDGE_TOWER_TO_RIGHT:
				pos.x -= v.x*offset;
				pos.y -= v.y*offset;
				break;

		}  // end switch
		tower = createTower( &pos, type, towerTemplate, bridgeObj );
		m_bridgeInfo.towerObjectID[ i ] = tower->getID();

	}  // end for, i
}

Object *Bridge::createTower(Coord3D *worldPos, BridgeTowerType towerType, const ThingTemplate *towerTemplate, Object *bridge)
{
	if (towerTemplate == NULL || bridge == NULL)
		return NULL;

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Object *tower = TheThingFactory->newObject(towerTemplate, bridge->getTeam(), &mask, false);

	Real angle = 0;
	switch (towerType)
	{
		case BRIDGE_TOWER_FROM_LEFT:
			angle = bridge->getOrientation() + PI;
			break;

		case BRIDGE_TOWER_FROM_RIGHT:
			angle = bridge->getOrientation() + PI;
			break;

		case BRIDGE_TOWER_TO_LEFT:
			angle = bridge->getOrientation();
			break;

		case BRIDGE_TOWER_TO_RIGHT:
			angle = bridge->getOrientation();
			break;

		default:
			return NULL;
	}

	tower->setPosition(worldPos);
	tower->setOrientation(angle);

	BridgeBehaviorInterface *bridgeInterface = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridge);
	if (bridgeInterface)
		bridgeInterface->setTower(towerType, tower);

	BridgeTowerBehaviorInterface *bridgeTowerInterface = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(tower);
	if (bridgeTowerInterface)
	{
		bridgeTowerInterface->setBridge(bridge);
		bridgeTowerInterface->setTowerType(towerType);
	}

	BodyModuleInterface *bridgeBody = bridge->getBodyModule();
	if (bridgeBody->isIndestructible())
	{
		BodyModuleInterface *towerBody = tower->getBodyModule();
		towerBody->setIndestructible(true);
	}

	return tower;
}
