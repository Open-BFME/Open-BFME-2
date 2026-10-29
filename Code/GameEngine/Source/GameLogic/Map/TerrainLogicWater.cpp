// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include
// platformsdk
//
// TerrainLogic::setWaterHeight, slot 31 of the TerrainLogic vftable
// (0x007FB2C8; slot 53 of W3DTerrainLogic's at 0x007C5838), from Zero Hour's
// GameLogic/Map/TerrainLogic.cpp.
//
// Target facts: BFME 2's water handle is an object of its own; the new height
// goes to it as an integer through its slot 6 (+0x18), so the grid-water and
// polygon-point branches of Zero Hour collapse into that one call between two
// getWaterHeight reads (slot 30, +0x78). The bounding rectangle comes from the
// rowed findAxisAlignedBoundingRect (0x0027D960, named for its address on the
// TerrainLogic view W3DTerrainLogic), the pathfinder remap from TheAI's pathfinder
// (+0x10) at 0x002E7133, isUnderwater is slot 19 (+0x4C, BFME 2's five-argument
// form) and the range scan is ThePartitionManager's unfiltered native query
// (0x006255D0) walked with next() only. The water damage is DamageInfo's
// damage type 9 and death type 7 from no source.
// The header inlines below are only expanded here (no reloc to them); the COMDATs this unit still emits are not
// retail's, so they get TU-local names instead of colliding with the rowed bodies.
#define zero zero_RV
#include <windows.h>
#include "Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

#include "../../../../Libraries/Include/Lib/Region3D.h"

class WaterHandle
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void setHeight(Int height); // +0x18
};

class DamageInfo
{
public:
	DamageInfo();
	char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	char m_pad0C[0x10 - 0x0C];
	Int m_damageType; // +0x10
	char m_pad14[0x1C - 0x14];
	Int m_deathType; // +0x1C
	Real m_amount; // +0x20
	char m_pad24[0x7C - 0x24];
};
class Rva00263895Member
{
public:
	Rva00263895Member(); // 0x00263895
	char m_pad00[0x8];
	ObjectID m_sourceID; // +0x08 +0x08
	char m_pad0C[0x4];
	Int m_damageType; // +0x10 +0x10
	char m_pad14[0x8];
	Int m_deathType; // +0x1C +0x1C
	Real m_amount; // +0x20 +0x20
	char m_pad24[0x58];
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	void attemptDamage(DamageInfo *damageInfo);
private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
};

class Pathfinder
{
public:
	void ForceMapRecalculation();
};

// TheAI's pathfinder at +0x10.
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;

// The rowed findAxisAlignedBoundingRect keeps its address-derived name on
// its address-named TerrainLogic view.
class W3DTerrainLogic
{
public:
	void Rva0027DA58();
	void Rva0027D960(void *water, float *region);
};

// N unnamed vftable slots appended to Base.
template <class Base, int N> class TerrainLogicSlots : public TerrainLogicSlots<Base, N - 1>
{
public:
	virtual void gap(Base *, char (*)[N]);
};
template <class Base> class TerrainLogicSlots<Base, 0> : public Base
{
};

class TerrainLogicHead
{
public:
	virtual void slot0();
};

class TerrainLogicUnderwater : public TerrainLogicSlots<TerrainLogicHead, 18>
{
public:
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL, Int unused = 0); // +0x4C
};

class TerrainLogic : public TerrainLogicSlots<TerrainLogicUnderwater, 10>
{
public:
	virtual Real getWaterHeight(const WaterHandle *water); // +0x78
	virtual void setWaterHeight(const WaterHandle *water, Real height, Real damageAmount, Bool forcePathfindUpdate); // +0x7C
private:
	void findAxisAlignedBoundingRect(const WaterHandle *water, Region3D *region)
	{
		((W3DTerrainLogic *)this)->Rva0027D960((void *)water, (Real *)region);
	}
};

// ?setWaterHeight@TerrainLogic@@UAEXPBVWaterHandle@@MM_N@Z @0x00282E20
void TerrainLogic::setWaterHeight( const WaterHandle *water, Real height, Real damageAmount,
																	 Bool forcePathfindUpdate )
{

	// sanity
	if( water == NULL )
		return;

	// save the previous height, set the new one and read back what the water took
	Real previousHeight = getWaterHeight( water );
	((WaterHandle *)water)->setHeight( (Int)height );
	height = getWaterHeight( water );

	// find the bounding rectangle of this water area
	Region3D affectedRegion;
	affectedRegion.zero();
	findAxisAlignedBoundingRect( water, &affectedRegion );

	// changes in the water level force us to recalculate the pathfinding map
	if( forcePathfindUpdate || previousHeight != height )
	{

		// do the pathfind remapping
		TheAI->pathfinder()->ForceMapRecalculation();

	}  // end if

	//
	// if the water height has risen, we need apply water damage to things that are now
	// under the water
	//
	if( damageAmount > 0.0f && height > previousHeight )
	{

		// find the center of the water "area" given the bounding region
		Coord3D center;
		center.x = affectedRegion.lo.x + affectedRegion.width() / 2.0f;
		center.y = affectedRegion.lo.y + affectedRegion.height() / 2.0f;
		center.z = 0.0f;  // irrelavant

		// the max radius to scan around us is the diagonal of the bounding region
		Real maxDist = sqrt( affectedRegion.width() * affectedRegion.width() +
												 affectedRegion.height() * affectedRegion.height() );

		// scan the objects in the area of the water affected
		BfmeWideResult iter = ThePartitionManager->rva006255D0( &center, maxDist, 0, 0 );
		Object *obj;
		const Coord3D *objPos;
		while( (obj = iter.next()) != NULL )
		{

			// get other object position
			objPos = obj->getPosition();

			// if this object is underwater, do some damage
			if( isUnderwater( objPos->x, objPos->y ) )
			{

				// do a lot of water damage
				Rva00263895Member damageInfo;
				damageInfo.m_damageType = 9;
				damageInfo.m_deathType = 7;
				damageInfo.m_sourceID = INVALID_ID;
				damageInfo.m_amount = damageAmount;
				obj->attemptDamage( (DamageInfo *)&damageInfo );

			}  // end if

		}  // end for obj

	}  // end if, water has risen

}  // end setWaterHeight
