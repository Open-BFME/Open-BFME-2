// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
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
// Like retail's header-only callees, the BaseType.h Coord3D/Coord2D inlines
// (0x00003571, 0x000035B6, 0x00005923), the scaffold ID list's STLport
// push_back/insert/_M_create_node (0x002A1B6F, 0x002A1316, 0x0029FB80, the
// DamageField pooled ObjectID list) and setScaffoldData are visible here as
// select-any copies, so cl sees which local addresses they keep.
template <class T> class BfmeObjectIdPoolAllocator;
namespace _STL {
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> &__stl_alloc_rebind(BfmeObjectIdPoolAllocator<T> &a, const U *)
{ return (BfmeObjectIdPoolAllocator<U> &)a; }
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> __stl_alloc_create(const BfmeObjectIdPoolAllocator<T> &, const U *)
{ return BfmeObjectIdPoolAllocator<U>(); }
}
// WWLib's always.h supplies the vector placement new/delete.
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"

// The support positions copy member-wise when constructed and block-copy when assigned.
struct ScaffoldCoord : Coord3D
{
	ScaffoldCoord() {}
	ScaffoldCoord(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
};

#include <math.h>
float ACos(float value);

inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

inline float Coord2D::length() const
{
	return (float)sqrt(x * x + y * y);
}

// The angle of the vector, clamped so a rounding overshoot cannot reach acos out of range.
inline float Coord2D::toAngle() const
{
	float len = length();
	if (len == 0.0f) {
		return 0.0f;
	}
	const float raw = x / len;
	float cosine;
	if (raw < -1.0f) {
		cosine = -1.0f;
	} else if (raw > 1.0f) {
		cosine = 1.0f;
	} else {
		cosine = raw;
	}
	if (y < 0.0f) {
		return -ACos(cosine);
	}
	return ACos(cosine);
}

#include <string.h>
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#define TWO_PI 6.28318530718f
#include "wwmath.h"
#define REAL_TO_INT_CEIL(x) WWMath::Float_To_Long((Real)ceil(x))
#define INT_TO_REAL(x) ((Real)(x))

class Team;

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getMaxHeightBelowPosition() const;
	Real getMaxHeightAbovePosition() const;
private:
	unsigned char m_unmodelled00[0x10];
	Real m_majorRadius;	// +0x10
};

class ThingTemplate
{
public:
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
private:
	unsigned char m_unmodelled000[0xA0];
	GeometryInfo m_geometryInfo;	// +0xA0
};

enum ObjectID { INVALID_ID = 0 };

// The scaffold ID list's nodes come from the fixed-size pool at 0x00DA60E8.
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool;
extern void *g_freeList;
template <class T> class BfmeObjectIdPoolAllocator {
public:
	typedef T value_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;
	typedef unsigned int size_type;
	typedef int difference_type;
	template <class U> struct rebind { typedef BfmeObjectIdPoolAllocator<U> other; };
	BfmeObjectIdPoolAllocator() {}
	template <class U> BfmeObjectIdPoolAllocator(const BfmeObjectIdPoolAllocator<U> &) {}
	pointer allocate(size_type, const void * = 0) { return (pointer)g_freelistPool.pop(); }
	void deallocate(pointer p, size_type)
	{
		if (p)
		{
			*(void **)p = g_freeList;
			g_freeList = p;
		}
	}
	void construct(pointer p, const_reference value) { new (p) T(value); }
	void destroy(pointer p) { p->~T(); }
	size_type max_size() const { return (size_type)(-1)/sizeof(T); }
};
namespace _STL {
template <class T, class U> struct _Alloc_traits<T, BfmeObjectIdPoolAllocator<U> > {
	typedef BfmeObjectIdPoolAllocator<U> _Orig;
	typedef BfmeObjectIdPoolAllocator<T> allocator_type;
	static allocator_type create_allocator(const _Orig &a) { return allocator_type(a); }
};
}
typedef std::list<ObjectID, BfmeObjectIdPoolAllocator<ObjectID> > ObjectIDList;

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	Team *getTeam() const { return m_team; }
private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id;	// +0x74
	unsigned char m_unmodelled078[0x304 - 0x78];
	Team *m_team;	// +0x304
};

// newObject's third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask
{
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b);
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

// The road template's scaffold / scaffold-support object name getters are
// rowed under address-derived owners (0x002D9BC1 / 0x0056394A).
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

class TerrainRoadType;

class Rva0027C36A
{
public:
	Rva0027C36A();
	Rva0027C36A &operator=(const Rva0027C36A &other);
	Coord3D from;		// +0x00
	Coord3D to;		// +0x0C
	Real bridgeWidth;	// +0x18
	Coord3D fromLeft;	// +0x1C
	Coord3D fromRight;	// +0x28
	Coord3D toLeft;		// +0x34
	Coord3D toRight;	// +0x40
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
	Bridge *m_next;			// +0x04
	AsciiString m_templateName;	// +0x08
	BridgeInfo m_bridgeInfo;	// +0x0C
	char m_padB4[0xC4 - 0xB4];
	Int m_layer;			// +0xC4
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
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
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
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

struct BridgeBehaviorModuleData
{
	char pad[8];
	Real m_lateralScaffoldSpeed, m_verticalScaffoldSpeed;
};

class BridgeBehaviorBase
{
public:
	virtual ~BridgeBehaviorBase();
	Object *getObject() const { return m_object; }
protected:
	BridgeBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
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
	Bool m_scaffoldPresent;			// +0xFD
	unsigned char m_unmodelledFE[0x100 - 0xFE];
	ObjectIDList m_scaffoldObjectIDList;	// +0x100
};

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3D *sunkenPosition,
		const Coord3D *risePosition, const Coord3D *buildPosition);
	virtual void setMotion(int motion);
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
	virtual void setLateralSpeed(Real speed);
	virtual void setVerticalSpeed(Real speed);
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

extern const Real g_00BC2A10;

// Select-any copy of the rowed BridgeBehaviorSetScaffoldData.cpp body.
__declspec(noinline) inline void BridgeBehavior::setScaffoldData(Object *object, Real *angle,
	Real *sunkenHeight, const Coord3D *risePosition,
	const Coord3D *buildPosition, const Coord3D *bridgeCenter)
{
	if (!object)
		return;
	if (!angle)
		return;
	if (!risePosition)
		return;
	if (!buildPosition)
		return;

	BridgeBehaviorModuleData *moduleData = m_moduleData;
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - g_00BC2A10;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion(1);
	((Thing *)object)->setOrientation(*angle);

	Real lateralSpeed = moduleData->m_lateralScaffoldSpeed;
	Coord3D buildToCenter;
	buildToCenter.x = buildPosition->x - risePosition->x;
	buildToCenter.y = buildPosition->y - risePosition->y;
	buildToCenter.z = buildPosition->z - risePosition->z;
	Coord3D riseToCenter;
	riseToCenter.x = bridgeCenter->x - risePosition->x;
	riseToCenter.y = bridgeCenter->y - risePosition->y;
	riseToCenter.z = bridgeCenter->z - risePosition->z;
	Real buildDistance = buildToCenter.length();
	Real riseDistance = riseToCenter.length();
	scaffold->setLateralSpeed(lateralSpeed * (buildDistance / riseDistance));
	Real verticalSpeed = moduleData->m_verticalScaffoldSpeed;
	scaffold->setVerticalSpeed(verticalSpeed);
}

// ------------------------------------------------------------------------------------------------
/** Start the bridge repair scaffolding.  If we already have scaffolding this call
	* is ignored */
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::createScaffolding( void )
{

	// if we have scaffolding up already do nothing
	if( m_scaffoldPresent == true )
		return;

	// get the bridge world object
	Object *us = getObject();
	const Coord3D *center = us->getPosition();

	// get our bridge object
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// get the bridge template
	AsciiString bridgeTemplateName = ((const TerrainType *)bridge)->getTexture();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );

	// get the thing template for the scaffold object we're going to use
	AsciiString scaffoldObjectName = ((const Rva002D9BC1AsciiField *)bridgeTemplate)->get();
	const ThingTemplate *scaffoldTemplate = TheThingFactory->findTemplate( scaffoldObjectName );
	if( scaffoldTemplate == 0 )
		return;

	// get thing template for scaffold support object
	AsciiString scaffoldSupportObjectName = ((Rva0056394A *)bridgeTemplate)->rva0056394A();
	const ThingTemplate *scaffoldSupportTemplate = TheThingFactory->findTemplate( scaffoldSupportObjectName );
	if( scaffoldSupportTemplate == 0 )
		return;

	// how much space is going to be between each of the scaffold objects at their final positions
	Real spacing = scaffoldTemplate->getTemplateGeometryInfo().getMajorRadius() * 2.0f;

	// how tall are the scaffold objects
	Real scaffoldHeight = scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
												scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();
	Real scaffoldSupportHeight = scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
															 scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();

	// get the bridge info
	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo( &bridgeInfo );

	//
	// given the area of the bridge, figure out what the start and end points are to create
	// all the scaffold objects at (just in the 2D bridge plane, not thinking about
	// rising the objects up through the ground yet)
	//
	Coord3D leftStart;
	leftStart.x = ((bridgeInfo.fromLeft.x - bridgeInfo.fromRight.x) / 2.0f) + bridgeInfo.fromRight.x;
	leftStart.y = ((bridgeInfo.fromLeft.y - bridgeInfo.fromRight.y) / 2.0f) + bridgeInfo.fromRight.y;
	leftStart.z = ((bridgeInfo.fromLeft.z - bridgeInfo.fromRight.z) / 2.0f) + bridgeInfo.fromRight.z;

	Coord3D rightStart;
	rightStart.x = ((bridgeInfo.toLeft.x - bridgeInfo.toRight.x) / 2.0f) + bridgeInfo.toRight.x;
	rightStart.y = ((bridgeInfo.toLeft.y - bridgeInfo.toRight.y) / 2.0f) + bridgeInfo.toRight.y;
	rightStart.z = ((bridgeInfo.toLeft.z - bridgeInfo.toRight.z) / 2.0f) + bridgeInfo.toRight.z;

	//
	// now that we have the left and right start points, we will compute two angles to
	// use for all the objects that we will create ... objects on the left side of the
	// bridge will be given a 'leftAngle' pointing from 'leftStart' to 'rightStart' and
	// the opposite will be given to objects on the right side of the bridge
	//
	Coord2D angleV;
	angleV.x = rightStart.x - leftStart.x;
	angleV.y = rightStart.y - leftStart.y;
	Real leftAngle = angleV.toAngle();
	Real rightAngle = leftAngle + TWO_PI;

	// compute vector from left to right across bridge and the reverse
	Coord3D leftVector;
	leftVector.x = rightStart.x - leftStart.x;
	leftVector.y = rightStart.y - leftStart.y;
	leftVector.z = rightStart.z - leftStart.z;
	Coord3D rightVector;
	rightVector.x = leftStart.x - rightStart.x;
	rightVector.y = leftStart.y - rightStart.y;
	rightVector.z = leftStart.z - rightStart.z;

	//
	// how many of these scaffold objects will take to tile from each of the endpoints
	// to the center area of the bridge
	//
	Real tileDistance = leftVector.length();
	Int numObjects = REAL_TO_INT_CEIL( tileDistance / spacing ) + 1;

	//
	// given the number of objects that we need to tile across the whole bridge, we will
	// go through the creation loop ceil( numObjects / 2.0f ) times, and each
	// time through the loop we'll create an object to move from each side of the
	// bridge, except the last object if the number of objects is odd is dead in the
	// center
	//
	Int numIterations = REAL_TO_INT_CEIL( INT_TO_REAL( numObjects ) / 2.0f );

	//
	// normalize left and right vectors as it is a vector that goes from our left start
	// position to the destination right start position ... we will multiply this vector by a
	// spacing amount and add to the left start position to find a destination position
	// for a particular scaffold object along the bridge surface
	//
	leftVector.normalize();
	rightVector.normalize();

	// create the scaffold objects for now
	Int scaffoldObjectsCreated = 0;
	Coord3D destinationPos, *riseToPos;
	Real *angle;
	Object *obj;
	for( Int i = 0; i < numIterations; ++i )
	{

		// create object
		CreateMask leftMask;
		memset( &leftMask, 0, sizeof( leftMask ) );
		obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &leftMask, (ObjectID)0 );

		// this object is from the "left" side of the bridge
		riseToPos = &leftStart;
		angle = &leftAngle;

		//
		// compute position for object moving from the left side, we're adding 0.1 here
		// so that all scaffold objects *have* to move some distance ... that way we
		// can just assign the speeds so they line up perfectly and not have to worry
		// about any object reaching a destination before any other object
		//
		destinationPos.x = leftVector.x * (spacing * i) + riseToPos->x + 0.1f;
		destinationPos.y = leftVector.y * (spacing * i) + riseToPos->y;
		destinationPos.z = leftVector.z * (spacing * i) + riseToPos->z;

		//
		// now that they key positions are calculated, set the rest of the position data
		// and movement speeds for the object
		//
		setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

		// keeping track of objects created
		scaffoldObjectsCreated++;
		m_scaffoldObjectIDList.push_back( obj->getID() );

		//
		// create support object layers under the scaffold object, this object mirrors the scaffold
		// object except is on a lower layer
		//
		Real offset = riseToPos->z;
		ScaffoldCoord supportRiseToPos = *riseToPos;
		ScaffoldCoord supportDestinationPos = destinationPos;
		ScaffoldCoord supportBridgeCenter = *center;
		while( offset >= 0.0f )
		{

			supportRiseToPos.z -= scaffoldSupportHeight;
			supportDestinationPos.z -= scaffoldSupportHeight;
			supportBridgeCenter.z -= scaffoldSupportHeight;
			CreateMask supportMask;
			memset( &supportMask, 0, sizeof( supportMask ) );
			obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, (ObjectID)0 );
			setScaffoldData( obj,
											 angle,
											 &scaffoldSupportHeight,
											 &supportRiseToPos,
											 &supportDestinationPos,
											 &supportBridgeCenter );
			m_scaffoldObjectIDList.push_back( obj->getID() );


			// off to the next layer
			offset -= scaffoldSupportHeight;

		}  // end while

		//
		// now create the object from the "right" side of the bridge ... but note that
		// we don't do this on the last iteration through this loop when we have an odd
		// number of objects we're tiling because all the space is already perfectly used up)
		//
		if( scaffoldObjectsCreated < numObjects )
		{

			// create new object
			CreateMask rightMask;
			memset( &rightMask, 0, sizeof( rightMask ) );
			obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &rightMask, (ObjectID)0 );

			// this object is on the "right" side of the bridge
			riseToPos = &rightStart;
			angle = &rightAngle;

			//
			// compute position for object moving from the left side, we're adding 0.1 here
			// so that all scaffold objects *have* to move some distance ... that way we
			// can just assign the speeds so they line up perfectly and not have to worry
			// about any object reaching a destination before any other object
			//
			destinationPos.x = rightVector.x * (spacing * i) + riseToPos->x + 0.1f;
			destinationPos.y = rightVector.y * (spacing * i) + riseToPos->y;
			destinationPos.z = rightVector.z * (spacing * i) + riseToPos->z;

			// set the rest scaffold data again
			setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

			// keeping track of objects created
			scaffoldObjectsCreated++;
			m_scaffoldObjectIDList.push_back( obj->getID() );

			//
			// create support object layers under the scaffold object, this object mirrors the scaffold
			// object except is on a lower layer
			//
			offset = riseToPos->z;
			(Coord3D &)supportRiseToPos = *riseToPos;
			(Coord3D &)supportDestinationPos = destinationPos;
			(Coord3D &)supportBridgeCenter = *center;
			while( offset >= 0.0f )
			{

				supportRiseToPos.z -= scaffoldSupportHeight;
				supportDestinationPos.z -= scaffoldSupportHeight;
				supportBridgeCenter.z -= scaffoldSupportHeight;
				CreateMask supportMask;
				memset( &supportMask, 0, sizeof( supportMask ) );
				obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, (ObjectID)0 );
				setScaffoldData( obj,
												 angle,
												 &scaffoldSupportHeight,
												 &supportRiseToPos,
												 &supportDestinationPos,
												 &supportBridgeCenter );
				m_scaffoldObjectIDList.push_back( obj->getID() );


				// off to the next layer
				offset -= scaffoldSupportHeight;

			}  // end while

		}  // end if

	}  // end for i

	// scaffolding is now present
	m_scaffoldPresent = true;

	// when scaffolding is present, a bridge cannot be used
	TheAI->pathfinder()->SetBridgeStateRepaired( bridge->getLayer(), false );

}  // end createScaffolding
