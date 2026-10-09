// ?loadGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.95 date=2026-10-09
// ?loadGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047901B, 631B: GarrisonContain::loadGarrisonPoints (name pinned
// from its caller recalcApparentControllingPlayer 0x00479432).
// Body: Zero Hour's loadGarrisonPoints (GeneralsMD GameEngine/Source/
// GameLogic/Object/Contain/GarrisonContain.cpp) as ported for BFME 1
// (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Contain/
// GarrisonContainLoadGarrisonPoints.cpp): every point starts at the object
// position, then for the pristine / damaged / really-damaged condition
// states the passenger bone positions (OpenContain::getPassengerBoneName
// 0x00463235) are read into the matching table and the bone count recorded.
// BFME 2 target evidence: module data +4, object +8, garrison points
// +0x424 (3 x 40 Coord3D), bone counts +0x9C4, initialized flag +0x9DC,
// module data mobile-garrison flag +0xA0, drawable (Object::getDrawable
// 0x005508E2) condition flags +0x258. The 0x4C-byte condition flag set is
// copied by the out-of-line 0x00045455 and cleared/set inline; the
// clear-and-set and replace calls are Object 0x0028CFB2/0x0028CFF5.

#include <string.h>
#include "ascii_string.h"
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;

class Matrix3D;
class Thing;

// ModelConditionFlags view: 0x4C bytes, out-of-line copy 0x00045455.
class Rva00045455Flags
{
public:
	Rva00045455Flags() { memset( m_bits, 0, sizeof( m_bits ) ); }
	Rva00045455Flags( const Rva00045455Flags &that );
	void clear() { memset( m_bits, 0, sizeof( m_bits ) ); }
	void set( Int bit ) { m_bits[ bit >> 5 ] |= 1u << ( bit & 31 ); }
	unsigned int m_bits[ 0x4C / 4 ];
};

class Drawable
{
public:
	unsigned char m_pad00[0x258];
	Rva00045455Flags m_conditionFlags;
};

class Object
{
public:
	Drawable *getDrawable() const;
	const Coord3D *getPosition() const { return &m_pos; }
	Int getMultiLogicalBonePosition( const char *boneNamePrefix, Int maxBones, Coord3D *positions,
		Matrix3D *transforms, Bool convertToWorld, Int unused ) const;
	void rva0028CFB2( const int *clr, const int *set );
	void rva0028CFF5( const int *flags, bool forceUpdate );
	Bool isMobile() const;
	unsigned char m_pad00[0x38];
	Coord3D m_pos;
};

// OpenContain::getPassengerBoneName, address-named as rowed.
class Rva00463235
{
public:
	AsciiString rva00463235( Thing *thing );
};

struct GarrisonContainModuleData
{
	unsigned char m_pad00[0xA0];
	Bool m_mobileGarrison;
};

enum
{
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
/** Load the garrison points from the bones of the structure */
// ------------------------------------------------------------------------------------------------
void GarrisonContain::loadGarrisonPoints( void )
{
	const GarrisonContainModuleData *modData = getGarrisonContainModuleData();
	Object *structure = getObject();
	Int i;
	Int j;
	Bool gBonesFound = false;

	// initialize all garrison points to the structure position
	for( i = 0; i < MAX_GARRISON_POINT_CONDITIONS; ++i )
		for( j = 0; j < MAX_GARRISON_POINTS; ++j )
			m_garrisonPoint[ i ][ j ] = *structure->getPosition();

	{
		Int count = 0;

		// save the original condition state
		const Rva00045455Flags originalFlags( structure->getDrawable()->m_conditionFlags );
		struct LocalMasks { unsigned int set[19]; unsigned int clear[19]; } masks;
		memset(masks.clear,0,sizeof(masks.clear));
		memset(masks.set,0,sizeof(masks.set));

		// pristine
		memset(masks.clear,0,sizeof(masks.clear));
		memset(masks.set,0,sizeof(masks.set));
		masks.clear[4 >> 5] |= 1u << (4 & 31);
		masks.clear[5 >> 5] |= 1u << (5 & 31);
		masks.clear[6 >> 5] |= 1u << (6 & 31);
		masks.clear[3 >> 5] |= 1u << (3 & 31);
		masks.set[10 >> 5] |= 1u << (10 & 31);
		structure->rva0028CFB2( (const int *)masks.clear, (const int *)masks.set );
		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( 0 ).str(),
			MAX_GARRISON_POINTS, m_garrisonPoint[ 0 ], 0, true, 0 );
		m_garrisonPointCount[ 0 ] = count;
		if( count > 0 )
			gBonesFound = true;

		// damaged
		memset(masks.clear,0,sizeof(masks.clear));
		memset(masks.set,0,sizeof(masks.set));
		masks.clear[4 >> 5] |= 1u << (4 & 31);
		masks.clear[5 >> 5] |= 1u << (5 & 31);
		masks.clear[6 >> 5] |= 1u << (6 & 31);
		masks.set[3 >> 5] |= 1u << (3 & 31);
		structure->rva0028CFB2( (const int *)masks.clear, (const int *)masks.set );
		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( 0 ).str(),
			MAX_GARRISON_POINTS, m_garrisonPoint[ 1 ], 0, true, 0 );
		m_garrisonPointCount[ 1 ] = count;
		if( count > 0 )
			gBonesFound = true;

		// really damaged
		memset(masks.clear,0,sizeof(masks.clear));
		memset(masks.set,0,sizeof(masks.set));
		masks.clear[5 >> 5] |= 1u << (5 & 31);
		masks.clear[6 >> 5] |= 1u << (6 & 31);
		masks.clear[3 >> 5] |= 1u << (3 & 31);
		masks.set[4 >> 5] |= 1u << (4 & 31);
		structure->rva0028CFB2( (const int *)masks.clear, (const int *)masks.set );
		count = structure->getMultiLogicalBonePosition( ((Rva00463235 *)this)->rva00463235( 0 ).str(),
			MAX_GARRISON_POINTS, m_garrisonPoint[ 2 ], 0, true, 0 );
		m_garrisonPointCount[ 2 ] = count;
		if( count > 0 )
			gBonesFound = true;

		// restore the original condition state
		structure->rva0028CFF5( (const int *)&originalFlags, false );
	}

	// garrison points are now initialized
	m_garrisonPointsInitialized = true;

	// mobile garrisons must not have garrison bones (ZH asserts here)
	if( gBonesFound && modData->m_mobileGarrison && getObject()->isMobile() )
	{
	}

}  // end loadGarrisonPoints
