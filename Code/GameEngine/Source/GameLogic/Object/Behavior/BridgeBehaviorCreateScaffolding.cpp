// cl: /FIzh_ascii.h /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_bridgebehavior /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/zh_outofline /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ivendor/stlport /Ireference/shims/asciistring_outofline /ICode/GameEngine/Include /Ireference/shims/iniexception /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
// The scaffold ID list's nodes come from the fixed-size pool at 0x00DA60E8.
#define __PLACEMENT_VEC_NEW_INLINE
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_MODULE_NO_MPO
#define _CRTIMP
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "ascii_string.h"
#include "Common/ThingFactory.h"
#include "Common/Geometry.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"
#include <math.h>
#include <string.h>
#include "wwmath.h"
#undef REAL_TO_INT_CEIL
// Retail's ceil goes through the import table, spelled as math.h's float overload does it; the
// seed's _CRTIMP makes the CRT's other calls direct.
namespace BridgeCrtImport {
extern "C" __declspec(dllimport) double __cdecl ceil(double);
inline float __cdecl ceilf(float x) { return ((float)ceil((double)x)); }
inline float __cdecl ceil(float x) { return (ceilf(x)); }
}
#define REAL_TO_INT_CEIL(x) WWMath::Float_To_Long((Real)BridgeCrtImport::ceil(x))

// The support positions copy member-wise when constructed and block-copy when assigned.
struct ScaffoldCoord : Coord3D
{
	ScaffoldCoord() {}
	ScaffoldCoord(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
};

// The template's geometry info at +0xA0; Zero Hour's ThingTemplate holds it elsewhere.
struct BridgeTemplateGeometryView
{
	unsigned char m_unmodelled000[0xA0];
	GeometryInfo m_geometryInfo;	// +0xA0
};

// newObject's third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask
{
	unsigned int m_bits[4];
};

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

class TerrainType
{
public:
	AsciiString getTexture() const;
};

extern const Real g_00BC2A10;

// Select-any: BridgeBehaviorCreateScaffolding.cpp compiles an identical copy for its caller.
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

	const BridgeBehaviorModuleData *moduleData = getBridgeBehaviorModuleData();
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - g_00BC2A10;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion((ScaffoldTargetMotion)1);
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
	Real spacing = ((const BridgeTemplateGeometryView *)scaffoldTemplate)->m_geometryInfo.getMajorRadius() * 2.0f;

	// how tall are the scaffold objects
	Real scaffoldHeight = ((const BridgeTemplateGeometryView *)scaffoldTemplate)->m_geometryInfo.getMaxHeightAbovePosition() +
												((const BridgeTemplateGeometryView *)scaffoldTemplate)->m_geometryInfo.getMaxHeightBelowPosition();
	Real scaffoldSupportHeight = ((const BridgeTemplateGeometryView *)scaffoldSupportTemplate)->m_geometryInfo.getMaxHeightAbovePosition() +
															 ((const BridgeTemplateGeometryView *)scaffoldSupportTemplate)->m_geometryInfo.getMaxHeightBelowPosition();

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
