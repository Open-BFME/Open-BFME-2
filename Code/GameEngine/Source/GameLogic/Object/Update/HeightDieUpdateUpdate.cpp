// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
//
// HeightDieUpdate::update (BFME 2), from the Generals Zero Hour
// HeightDieUpdate.cpp.
//
// Target facts. update is slot 0 of HeightDieUpdate's UpdateModuleInterface
// vftable. The fields follow the ZH order from +0x20 (has-died and
// particles-destroyed bytes, the last position at +0x24, the earliest death
// frame at +0x30; the rowed ctor 0x0048FCB2 sets them). The module data
// (rowed ctor 0x0048FC75) holds TargetHeight +8,
// TargetHeightIncludesStructures +0xC, OnlyWhenMovingDown +0xD,
// DestroyAttachedParticlesAtHeight +0x10, SnapToGroundOnDeath +0x14 and
// InitialDelay +0x18. BFME 2 differences from ZH:
// - getHighestLayerForDestination (0x002803F9) drops ZH's wall layer.
// - The structure scan passes one partition filter, BFME 2's KindOf filter
//   (Rva0004584D) over the KINDOF_STRUCTURE mask (bit 7) and the empty mask,
//   and walks the range query's result handle with next() only.
// - destroyAttachedSystems is ParticleSystemManager 0x001F5BBE (its rowed
//   body destroys every system whose attached object ID is the object's).
// - The object's container is at +0x274, its GeometryInfo at +0xA8.
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE 1
#define FALSE 0
#define UINT_MAX 0xffffffff
#define NULL 0

class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum DistanceCalculationType
{
	FROM_BOUNDINGSPHERE_3D = 3
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	Real getMaxHeightAbovePosition() const;

private:
	char m_unknown00[0x10];
	Real m_boundingCircleRadius; // +0x10
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	void setPosition(const Coord3D *pos);

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	Object *getContainedBy() const { return m_containedBy; }
	void kill(DamageType damageType = DAMAGE_UNRESISTABLE, DeathType deathType = DEATH_NORMAL);

private:
	char m_unknown44[0xA8 - 0x44];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_unknownBC[0x274 - 0xBC];
	Object *m_containedBy; // +0x274
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02();
	virtual void t03(); virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges = false);
};

extern TerrainLogic *TheTerrainLogic;

class ParticleSystemManager
{
public:
	void rva001F5BBE(Object *obj); // destroyAttachedSystems
};

extern ParticleSystemManager *TheParticleSystemManager;

// Partition filters (see the BroadcastStealthUpdateUpdate.cpp view).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// A KindOfMaskType (0x0004543D copies it).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit) throw(); // 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

extern unsigned char g_00DFEFA4StoragePrototype[28]; // KINDOFMASK_NONE

// vftable 0x00BC2908: accept what has every kind of the first mask and none
// of the second (PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct BfmeWideResult
{
	Object *next() throw(); // 0x00045623
	~BfmeWideResult(); // 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order); // 0x00625610
};

extern PartitionManager *ThePartitionManager;

class HeightDieUpdateModuleData
{
public:
	char m_unknown00[0x08];
	Real m_targetHeightAboveTerrain; // +0x08
	Bool m_targetHeightIncludesStructures; // +0x0C
	Bool m_onlyWhenMovingDown; // +0x0D
	Real m_destroyAttachedParticlesAtHeight; // +0x10
	Bool m_snapToGroundOnDeath; // +0x14
	UnsignedInt m_initialDelay; // +0x18
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class HeightDieUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	const HeightDieUpdateModuleData *getHeightDieUpdateModuleData() const
	{
		return (const HeightDieUpdateModuleData *)m_moduleData;
	}

	Bool m_hasDied; // +0x20
	Bool m_particlesDestroyed; // +0x21
	Coord3D m_lastPosition; // +0x24
	UnsignedInt m_earliestDeathFrame; // +0x30
};

// ?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048FD1B 604B
UpdateSleepTime HeightDieUpdate::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if( m_earliestDeathFrame == UINT_MAX )
		m_earliestDeathFrame = now + getHeightDieUpdateModuleData()->m_initialDelay;

	// If at least a one frame delay has been set, then stop for a while
	if( m_earliestDeathFrame > now )
		return UPDATE_SLEEP_NONE;

	// do nothing if we're contained within other objects ... like a transport
	if( getObject()->getContainedBy() != NULL )
	{

		// keep track of our last position even though we're not doing anything yet
		m_lastPosition = *getObject()->getPosition();

		// get outta here
		return UPDATE_SLEEP_NONE;

	}  // end if

	// get the module data
	const HeightDieUpdateModuleData *modData = getHeightDieUpdateModuleData();

	// get our current position
	const Coord3D *pos = getObject()->getPosition();

	Bool directionOK = TRUE;
	if( m_hasDied == FALSE )
	{

		if( modData->m_onlyWhenMovingDown )
		{

			if( pos->z >= m_lastPosition.z )
				directionOK = FALSE;

		}  // end fi

		// get the terrain height
		Real terrainHeightAtPos = TheTerrainLogic->getGroundHeight( pos->x, pos->y );

		// if including structures, check for bridges
		if (modData->m_targetHeightIncludesStructures)
		{
			PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(pos);
			if (layer != LAYER_GROUND)
			{
				Real layerHeight = TheTerrainLogic->getLayerHeight(pos->x, pos->y, layer);
				if (layerHeight > terrainHeightAtPos)
					terrainHeightAtPos = layerHeight;
			}
		}

		//
		// our target height to die at is by default the height specified in the INI entry above
		// the terrain ... we may change our target height if we care about dying above
		// objects under us (see below)
		//
		Real targetHeight = terrainHeightAtPos + modData->m_targetHeightAboveTerrain;

		//
		// if we consider objects under us ... we will die when we are the specified distance above
		// those objects
		//
		if( modData->m_targetHeightIncludesStructures == TRUE )
		{

			Real tallestHeight = 0.0f;

			// scan all objects in the radius of our extent and find the tallest height among them
			Real range = getObject()->getGeometryInfo().getBoundingCircleRadius();
			BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( getObject()->getPosition(),
				range, FROM_BOUNDINGSPHERE_3D,
				&Rva0004584D( BfmeFixedStorage0004543D( 0, 7 ), *(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype ),
				0 );
			Object *obj;

			Real thisHeight;
			while( (obj = iter.next()) != NULL )
			{

				// ignore ourselves
				if( obj == getObject() )
					continue;

				// store the height of the tallest object under us
				thisHeight = obj->getGeometryInfo().getMaxHeightAbovePosition();

				if( thisHeight > tallestHeight )
					tallestHeight = thisHeight;

			}  // end for obj

			//
			// our target height is either the height above the terrain as specified by the INI
			// entry for the object that has this update ... or it is the building height of the
			// tallest thing under us
			//
			if( tallestHeight > modData->m_targetHeightAboveTerrain )
				targetHeight = tallestHeight + terrainHeightAtPos;

		}  // end if

		// if we are below the target height ... DIE!
		if( pos->z < targetHeight && directionOK )
		{

			// if we're supposed to snap us to the ground on death do so
			// AND: even if we're not snapping to ground, be sure we don't go BELOW ground
			if( modData->m_snapToGroundOnDeath || pos->z < terrainHeightAtPos )
			{
				Coord3D ground;

				ground.x = pos->x;
				ground.y = pos->y;
				ground.z = terrainHeightAtPos;
				getObject()->setPosition( &ground );

			}

			// kill the object
			getObject()->kill();

			// we have died ... don't do this again
			m_hasDied = TRUE;

		}  // end if

	}  // end if

	//
	// if our height is below the destroy attached particles height above the terrain, clean
	// them up from the particle system
	//
	if( m_particlesDestroyed == FALSE && pos->z < modData->m_destroyAttachedParticlesAtHeight && (m_hasDied || directionOK) )
	{

		// destroy them
		TheParticleSystemManager->rva001F5BBE( getObject() );

		// don't do this again
		m_particlesDestroyed = TRUE;

	}  // end if

	// save our current position as the last position we monitored
	m_lastPosition = *pos;

	return UPDATE_SLEEP_NONE;

}  // end update
