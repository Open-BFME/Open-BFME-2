// ?createScaffolding@BridgeBehavior@@UAEXXZ
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
// BridgeBehavior::createScaffolding (retail 0x00457737, 1851B), the Zero Hour
// GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp body built
// /O1 G7 SSE like the rest of the BridgeBehavior TU
// (BridgeBehaviorAreaEffects.cpp). `this` is the BridgeBehaviorInterface
// subobject at +0x20; setScaffoldData (0x004568EC) runs on the behavior.
// BFME target facts: scaffold present flag +0xFD and scaffold ObjectID list
// +0x100 of the behavior; scaffold/support template names come from the road
// template (0x002D9BC1 / 0x0056394A) and are looked up through
// TheThingFactory 0x002D06CA; geometry major radius at template +0xB0 and
// the GeometryInfo height getters 0x000BD7C0 / 0x000BD8A0 on template +0xA0;
// objects come from the four-argument newObject with a zeroed CreateMask
// and the owner's team (+0x304); bridge layer +0xC4 goes to
// Pathfinder::SetBridgeStateRepaired(layer, false) on TheAI +0x10.
// The bridge template name getter is the ICF-folded 0x000AF1DD body, reached
// through the admitted TerrainType::getTexture pin as in
// BridgeBehaviorAreaEffects.cpp.

#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <math.h>
#include <string.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TWO_PI 6.28318530718f

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil(x)))
#define INT_TO_REAL(x) ((Real)(x))

// class-gate: allow Coord2D the canonical data-only header lacks the rowed out-of-line toAngle (0x00005923) this body calls; same two floats
class Coord2D
{
public:
	Real x;
	Real y;
	Real toAngle() const;
};

class Team;

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getMaxHeightAbovePosition() const;
	Real getMaxHeightBelowPosition() const;

private:
	unsigned char m_unmodelled00[0x10];
	Real m_majorRadius; // +0x10
};

class ThingTemplate
{
public:
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }

private:
	unsigned char m_unmodelled000[0xA0];
	GeometryInfo m_geometryInfo; // +0xA0
};

typedef UnsignedInt ObjectID;

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	Team *getTeam() const { return m_team; }

private:
	unsigned char m_unmodelled000[0x38];
	Coord3D m_pos; // +0x38
	unsigned char m_unmodelled044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_unmodelled078[0x304 - 0x78];
	Team *m_team; // +0x304
};

// newObject's third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask
{
	unsigned int m_bits[4];
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
	const ThingTemplate *findTemplate(const AsciiString &name)
	{
		return (const ThingTemplate *)((Rva002D06CA *)this)->rva002D06CA(&name);
	}
};
extern ThingFactory *TheThingFactory;

class Rva002D9BC1AsciiField
{
public:
	AsciiString get() const;
};

class Rva0056394A
{
public:
	AsciiString rva0056394A();
};

// The road template's scaffold / scaffold-support object name getters are
// rowed under address-derived owners (0x002D9BC1 / 0x0056394A).
class TerrainRoadType;

class Rva0027C36A
{
public:
	Rva0027C36A();
	Rva0027C36A &operator=(const Rva0027C36A &other);

	Coord3D from; // +0x00
	Coord3D to; // +0x0C
	Real bridgeWidth; // +0x18
	Coord3D fromLeft; // +0x1C
	Coord3D fromRight; // +0x28
	Coord3D toLeft; // +0x34
	Coord3D toRight; // +0x40
private:
	char m_pad4C[0xA8 - 0x4C];
};
typedef Rva0027C36A BridgeInfo;

class TerrainType
{
public:
	AsciiString getTexture() const;
};

class Bridge
{
public:
	void getBridgeInfo(BridgeInfo *info) { *info = m_bridgeInfo; }
	Int getLayer() const { return m_layer; }

private:
	void *m_vtable;
	Bridge *m_next; // +0x04
	AsciiString m_templateName; // +0x08
	BridgeInfo m_bridgeInfo; // +0x0C
	char m_padB4[0xC4 - 0xB4];
	Int m_layer; // +0xC4
};

class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
};
extern TerrainRoadCollection *TheTerrainRoads;

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0();
	virtual Bridge *findBridgeAt(const Coord3D *loc) const;
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void SetBridgeStateRepaired(Int layer, bool repaired);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_unmodelled00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class Rva002A1B6FNativeList
{
public:
	void append(void *const &value);
};

class BridgeBehaviorBase
{
public:
	virtual ~BridgeBehaviorBase();
	Object *getObject() const { return m_object; }

private:
	void *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_unmodelled0C[0x20 - 0x0C];
};

class BridgeBehaviorInterface
{
public:
	virtual void createScaffolding() = 0;
};

class BridgeBehavior : public BridgeBehaviorBase, public BridgeBehaviorInterface
{
public:
	virtual void createScaffolding();

protected:
	void setScaffoldData(Object *obj, Real *angle, Real *height, const Coord3D *riseToPos,
		const Coord3D *buildPos, const Coord3D *bridgeCenter);

private:
	unsigned char m_unmodelled24[0xFD - 0x24];
	Bool m_scaffoldPresent; // +0xFD
	unsigned char m_unmodelledFE[0x100 - 0xFE];
	Rva002A1B6FNativeList m_scaffoldObjectIDList; // +0x100
};

// ------------------------------------------------------------------------------------------------
/** Start the bridge repair scaffolding.  If we already have scaffolding this call
	* is ignored */
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::createScaffolding( void )
{

	// if we already have scaffolding, do nothing
	if( m_scaffoldPresent == true )
		return;

	// get our bridge
	Object *us = getObject();
	const Coord3D *center = us->getPosition();
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// get the bridge template
	AsciiString bridgeTemplateName = ((const TerrainType *)bridge)->getTexture();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );

	// get the scaffold template
	AsciiString scaffoldObjectName = ((const Rva002D9BC1AsciiField *)bridgeTemplate)->get();
	const ThingTemplate *scaffoldTemplate = TheThingFactory->findTemplate( scaffoldObjectName );
	if( scaffoldTemplate == 0 )
		return;

	// get the scaffold support template
	AsciiString scaffoldSupportObjectName = ((Rva0056394A *)bridgeTemplate)->rva0056394A();
	const ThingTemplate *scaffoldSupportTemplate = TheThingFactory->findTemplate( scaffoldSupportObjectName );
	if( scaffoldSupportTemplate == 0 )
		return;

	// how far apart are the scaffold objects, and how tall are they
	Real spacing = scaffoldTemplate->getTemplateGeometryInfo().getMajorRadius() * 2.0f;
	Real scaffoldHeight = scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition() +
												scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition();
	Real scaffoldSupportHeight = scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition() +
															 scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition();

	// get the bridge info
	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo( &bridgeInfo );

	// the scaffolding starts at the middle of each end of the bridge
	Coord3D leftStart;
	leftStart.x = ((bridgeInfo.fromLeft.x - bridgeInfo.fromRight.x) / 2.0f) + bridgeInfo.fromRight.x;
	leftStart.y = ((bridgeInfo.fromLeft.y - bridgeInfo.fromRight.y) / 2.0f) + bridgeInfo.fromRight.y;
	leftStart.z = ((bridgeInfo.fromLeft.z - bridgeInfo.fromRight.z) / 2.0f) + bridgeInfo.fromRight.z;
	Coord3D rightStart;
	rightStart.x = ((bridgeInfo.toLeft.x - bridgeInfo.toRight.x) / 2.0f) + bridgeInfo.toRight.x;
	rightStart.y = ((bridgeInfo.toLeft.y - bridgeInfo.toRight.y) / 2.0f) + bridgeInfo.toRight.y;
	rightStart.z = ((bridgeInfo.toLeft.z - bridgeInfo.toRight.z) / 2.0f) + bridgeInfo.toRight.z;

	// angles of the scaffolding at each end
	Coord2D angleV;
	angleV.x = rightStart.x - leftStart.x;
	angleV.y = rightStart.y - leftStart.y;
	Real leftAngle = angleV.toAngle();
	Real rightAngle = leftAngle + TWO_PI;

	// vectors from each end to the other
	Coord3D leftVector;
	leftVector.x = rightStart.x - leftStart.x;
	leftVector.y = rightStart.y - leftStart.y;
	leftVector.z = rightStart.z - leftStart.z;
	Coord3D rightVector;
	rightVector.x = leftStart.x - rightStart.x;
	rightVector.y = leftStart.y - rightStart.y;
	rightVector.z = leftStart.z - rightStart.z;

	// how many objects we need
	Real tileDistance = leftVector.length();
	Int numObjects = REAL_TO_INT_CEIL( tileDistance / spacing ) + 1;
	Int numIterations = REAL_TO_INT_CEIL( INT_TO_REAL( numObjects ) / 2.0f );
	leftVector.normalize();
	rightVector.normalize();

	// create the objects from each end towards the middle
	Int scaffoldObjectsCreated = 0;
	Coord3D destinationPos, *riseToPos;
	Real *angle;
	Object *obj;
	for( Int i = 0; i < numIterations; ++i )
	{

		// the left side
		CreateMask leftMask;
		memset( &leftMask, 0, sizeof( leftMask ) );
		obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &leftMask, false );
		riseToPos = &leftStart;
		angle = &leftAngle;
		destinationPos.x = leftVector.x * (spacing * i) + riseToPos->x + 0.1f;
		destinationPos.y = leftVector.y * (spacing * i) + riseToPos->y;
		destinationPos.z = leftVector.z * (spacing * i) + riseToPos->z;
		setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );
		scaffoldObjectsCreated++;
		m_scaffoldObjectIDList.append( (void *)obj->getID() );

		// supports under the left piece
		Real offset = riseToPos->z;
		Coord3D supportRiseToPos = *riseToPos;
		Coord3D supportDestinationPos = destinationPos;
		Coord3D supportBridgeCenter = *center;
		while( offset >= 0.0f )
		{
			supportRiseToPos.z -= scaffoldSupportHeight;
			supportDestinationPos.z -= scaffoldSupportHeight;
			supportBridgeCenter.z -= scaffoldSupportHeight;
			CreateMask supportMask;
			memset( &supportMask, 0, sizeof( supportMask ) );
			obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, false );
			setScaffoldData( obj, angle, &scaffoldSupportHeight,
											 &supportRiseToPos, &supportDestinationPos, &supportBridgeCenter );
			m_scaffoldObjectIDList.append( (void *)obj->getID() );
			offset -= scaffoldSupportHeight;
		}  // end while

		// the right side
		if( scaffoldObjectsCreated < numObjects )
		{
			CreateMask rightMask;
			memset( &rightMask, 0, sizeof( rightMask ) );
			obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &rightMask, false );
			riseToPos = &rightStart;
			angle = &rightAngle;
			destinationPos.x = rightVector.x * (spacing * i) + riseToPos->x + 0.1f;
			destinationPos.y = rightVector.y * (spacing * i) + riseToPos->y;
			destinationPos.z = rightVector.z * (spacing * i) + riseToPos->z;
			setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );
			scaffoldObjectsCreated++;
			m_scaffoldObjectIDList.append( (void *)obj->getID() );

			offset = riseToPos->z;
			supportRiseToPos = *riseToPos;
			supportDestinationPos = destinationPos;
			supportBridgeCenter = *center;
			while( offset >= 0.0f )
			{
				supportRiseToPos.z -= scaffoldSupportHeight;
				supportDestinationPos.z -= scaffoldSupportHeight;
				supportBridgeCenter.z -= scaffoldSupportHeight;
				CreateMask supportMask;
				memset( &supportMask, 0, sizeof( supportMask ) );
				obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, false );
				setScaffoldData( obj, angle, &scaffoldSupportHeight,
												 &supportRiseToPos, &supportDestinationPos, &supportBridgeCenter );
				m_scaffoldObjectIDList.append( (void *)obj->getID() );
				offset -= scaffoldSupportHeight;
			}  // end while

		}  // end if

	}  // end for i

	// we now have scaffolding
	m_scaffoldPresent = true;

	// the bridge is not passable while being repaired
	TheAI->pathfinder()->SetBridgeStateRepaired( bridge->getLayer(), false );

}  // end createScaffolding
