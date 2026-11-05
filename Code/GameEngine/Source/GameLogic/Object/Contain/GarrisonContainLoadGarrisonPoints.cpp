// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// GarrisonContain::loadGarrisonPoints, retail 0x0047901B (631 bytes):
// ?loadGarrisonPoints@GarrisonContain@@IAEXXZ (name pinned from its caller
// recalcApparentControllingPlayer 0x00479432).
// Identity (target): WorldBuilder's debug GarrisonContain.cpp body at
// 0x011A4B10 has the same callees and the BitFlags<591> SetBit asserts.
// Body: Zero Hour's loadGarrisonPoints (GeneralsMD GameEngine/Source/
// GameLogic/Object/Contain/GarrisonContain.cpp) as ported for BFME 1
// (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Contain/
// GarrisonContainLoadGarrisonPoints.cpp): every point starts at the object
// position, then for the pristine / damaged / really-damaged condition
// states the passenger bone positions (OpenContain::getPassengerBoneName
// 0x00463235) are read into the matching table and the bone count recorded.
// BFME 2 target evidence: module data +4, object +8, garrison points
// +0x424 (3 x 40 Coord3D), bone counts +0x9C4, initialized flag +0x9DC,
// module data mobile-garrison flag +0xA0, drawable (Thing::getDrawable
// 0x005508E2) condition flags +0x258. The 0x4C-byte condition flag set is
// copied by the out-of-line 0x00045455 and cleared/set inline; the
// clear-and-set and replace calls are Object 0x0028CFB2/0x0028CFF5.
// The WorldBuilder twin also shows the conditionIndex and draw locals.
#include <string.h>
#include "ascii_string.h"
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;

class Matrix3D;
class Thing;

// ModelConditionFlags (BitFlags<591>) view; its copy constructor 0x00045455
// is rowed under this name.
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead() { memset( m_bits, 0, sizeof( m_bits ) ); }
	WeaponTemplateSetHead( const WeaponTemplateSetHead &that );
	void clear() { memset( m_bits, 0, sizeof( m_bits ) ); }
	unsigned int &getWord( Int bit ) { return m_bits[ bit >> 5 ]; }
	void set( Int bit ) { getWord( bit ) |= 1u << ( bit & 31 ); }
	unsigned int m_bits[ 0x4C / 4 ];
};
typedef WeaponTemplateSetHead ModelConditionFlags;

// Zero Hour's ModelConditionFlagType values; retail's three mask pairs use exactly these bits.
enum ModelConditionFlagType
{
	MODELCONDITION_DAMAGED = 3,
	MODELCONDITION_REALLY_DAMAGED = 4,
	MODELCONDITION_RUBBLE = 5,
	MODELCONDITION_SPECIAL_DAMAGED = 6,
	MODELCONDITION_GARRISONED = 10
};

class Drawable
{
public:
	const ModelConditionFlags &getModelConditionFlags() const { return m_conditionFlags; }
	unsigned char m_pad00[0x258];
	ModelConditionFlags m_conditionFlags;
};

#include "../../../Common/Thing/thing.h"
#include "../object.h"


// OpenContain::getPassengerBoneName, address-named as rowed.
class Rva00463235
{
public:
	AsciiString rva00463235( Thing *thing );
};

#include "../../../../Include/GameLogic/Module/GarrisonContainModuleData.h"

enum
{
	GARRISON_POINT_PRISTINE = 0,
	GARRISON_POINT_DAMAGED = 1,
	GARRISON_POINT_REALLY_DAMAGED = 2,
	MAX_GARRISON_POINT_CONDITIONS = 3,
	MAX_GARRISON_POINTS = 40
};

class GarrisonContain
{
protected:
	void loadGarrisonPoints( void );

	const GarrisonContainModuleData *getGarrisonContainModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	const GarrisonContainModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x424 - 0x0C];
	Coord3D m_garrisonPoint[ MAX_GARRISON_POINT_CONDITIONS ][ MAX_GARRISON_POINTS ];
	Int m_garrisonPointCount[ MAX_GARRISON_POINT_CONDITIONS ];
	unsigned char m_pad9D0[0x9DC - 0x9D0];
	Bool m_garrisonPointsInitialized;
};

// ------------------------------------------------------------------------------------------------
/** Load the garrison point position data and save for use later */
// ------------------------------------------------------------------------------------------------
void GarrisonContain::loadGarrisonPoints( void )
{
	const GarrisonContainModuleData *modData = getGarrisonContainModuleData();
	Object *structure = getObject();
	Int i, j;
	Bool gBonesFound = false;

	//
	// initialize all the garrison points to the center of the object, this assumes that we
	// will never move (these points are cached)
	//
	for( i = 0; i < MAX_GARRISON_POINT_CONDITIONS; ++i )
		for( j = 0; j < MAX_GARRISON_POINTS; ++j )
			m_garrisonPoint[ i ][ j ] = *(structure->getPosition());

	//
	// in order to get all the garrison point positions we will actually switch the model
	// condition through the garrisoned pristine, damaged, and really damaged states.  This
	// is especially important because at the time or "garrisoning" a model condition may
	// not actually switch to a garrisoned state because of units that garrison things
	// all stealthy.  By caching all the bone positions once we will have access to
	// any of the points for any condition state at any time
	//
	{
		Int conditionIndex;
		Int count = 0;

		// save the original paramters for the model condition
		Drawable* draw = structure->getDrawable();
		const ModelConditionFlags originalFlags = draw->getModelConditionFlags();
		ModelConditionFlags clearFlags;
		ModelConditionFlags setFlags;

		// pristine garrisoned
		clearFlags.clear();
		setFlags.clear();
		clearFlags.set( MODELCONDITION_REALLY_DAMAGED );
		clearFlags.set( MODELCONDITION_RUBBLE );
		clearFlags.set( MODELCONDITION_SPECIAL_DAMAGED );
		clearFlags.set( MODELCONDITION_DAMAGED );
		setFlags.set( MODELCONDITION_GARRISONED );
		structure->rva0028CFB2( (const int *)&clearFlags, (const int *)&setFlags );
		conditionIndex = GARRISON_POINT_PRISTINE;

		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( NULL ).str(), MAX_GARRISON_POINTS,
			m_garrisonPoint[ conditionIndex ], NULL, true, 0 );
		m_garrisonPointCount[ conditionIndex ] = count;

		if ( count > 0) gBonesFound = true;

		// damaged garrisoned
		clearFlags.clear();
		setFlags.clear();
		clearFlags.set( MODELCONDITION_REALLY_DAMAGED );
		clearFlags.set( MODELCONDITION_RUBBLE );
		clearFlags.set( MODELCONDITION_SPECIAL_DAMAGED );
		setFlags.set( MODELCONDITION_DAMAGED );
		structure->rva0028CFB2( (const int *)&clearFlags, (const int *)&setFlags );
		conditionIndex = GARRISON_POINT_DAMAGED;

		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( NULL ).str(), MAX_GARRISON_POINTS,
			m_garrisonPoint[ conditionIndex ], NULL, true, 0 );
		m_garrisonPointCount[ conditionIndex ] = count;

		if ( count > 0) gBonesFound = true;

		// really damaged garrisoned
		clearFlags.clear();
		setFlags.clear();
		clearFlags.set( MODELCONDITION_RUBBLE );
		clearFlags.set( MODELCONDITION_SPECIAL_DAMAGED );
		clearFlags.set( MODELCONDITION_DAMAGED );
		setFlags.set( MODELCONDITION_REALLY_DAMAGED );
		structure->rva0028CFB2( (const int *)&clearFlags, (const int *)&setFlags );
		conditionIndex = GARRISON_POINT_REALLY_DAMAGED;

		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( NULL ).str(), MAX_GARRISON_POINTS,
			m_garrisonPoint[ conditionIndex ], NULL, true, 0 );
		m_garrisonPointCount[ conditionIndex ] = count;

		if ( count > 0) gBonesFound = true;

		// restore the original condition flags
		structure->rva0028CFF5( (const int *)&originalFlags, false );

	}  // end if, draw

	// garrison points are now initialized
	m_garrisonPointsInitialized = true;

	if (gBonesFound && modData->m_mobileGarrison && (getObject()->isMobile() == true) )
	{
		// Zero Hour asserts here that a mobile garrison has no garrison bones
	}

}  // end loadGarrisonPoints
