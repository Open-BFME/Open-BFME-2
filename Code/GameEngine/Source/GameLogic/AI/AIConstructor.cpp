// cl: /O1 /G7 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP=
// stlport
// BF1 f98983a7d TAiDataCtor.cpp is the semantic and member-name guide.
// Native670B 2FE382..2FE620 supplies every offset and constant:50-unit
// water depth;5-unit acquire limit; extra floatB0=FLT_MAX andF0=1.0;
// string membersDC/E0/E4; pointersF4/F8/FC/100. AI constructor2FEA85
// allocates114B and calls this exact body. Unaccessed final10B remain opaque.
// Original TAiData and semantic member names are carried from the donor;
// target construction spine and Snapshot-family tableC071E4 corroborate
// the subsystem relationship. Extra field meanings remain unresolved.
// Existing global owner g_Va00DBA4E4 is read normally twice as retail does.

typedef float Real;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Xfer;

#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
extern int g_Va00DBA4E4;

class TAiData : public Snapshot
{
public:
	TAiData();
	virtual ~TAiData();
	virtual const char *GetSnapshotName() const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();

private:
	Real m_structureSeconds;
	Real m_teamSeconds;
	UnsignedInt m_resourcesWealthy;
	UnsignedInt m_resourcesPoor;
	UnsignedInt m_forceIdleFramesCount;
	Real m_structuresWealthyMod;
	Real m_teamWealthyMod;
	Real m_structuresPoorMod;
	Real m_teamPoorMod;
	Real m_teamResourcesToBuild;
	Real m_guardInnerModifierAI;
	Real m_guardOuterModifierAI;
	Real m_guardInnerModifierHuman;
	Real m_guardOuterModifierHuman;
	UnsignedInt m_guardChaseUnitFrames;
	UnsignedInt m_guardEnemyScanRate;
	UnsignedInt m_guardEnemyReturnScanRate;
	Real m_wallHeight;
	Real m_alertRangeModifier;
	Real m_aggressiveRangeModifier;
	Real m_attackPriorityDistanceModifier;
	Real m_maxRecruitDistance;
	Real m_skirmishBaseDefenseExtraDistance;
	Real m_repulsedDistance;
	Bool m_enableRepulsors;
	Bool m_forceSkirmishAI;
	Bool m_rotateSkirmishBases;
	Bool m_attackUsesLineOfSight;
	Bool m_attackIgnoreInsignificantBuildings;
	unsigned char m_groupAlignment[3];
	Real m_minDistanceForGroup;
	Real m_distanceRequiresGroup;
	Real m_minClumpDensity;
	UnsignedInt m_infantryPathfindDiameter;
	UnsignedInt m_vehiclePathfindDiameter;
	UnsignedInt m_rebuildDelaySeconds;
	Real m_supplyCenterSafeRadius;
	Real m_aiDozerBoredRadiusModifier;
	Bool m_aiCrushesInfantry;
	unsigned char m_retaliationAlignment[3];
	Real m_meleeApproachTolerance;
	Real m_meleeApproachDist;
	Real m_meleeAcquireLimitDist;
	Real m_wadeWaterDepth;
	Real m_formationColumnWidth;
	Real m_formationRowDepth;
	Real m_formationSquadSpacing;
	Real m_narrowPassageScale;
	Real m_unknownB0;
	UnsignedInt m_formationColumns;
	Bool m_waitForOthers;
	Bool m_hordesWaitForHordes;
	Bool m_attackMoveUsesFormations;
	Bool m_forceHordesToLowLOD;
	Bool m_allowForestFires;
	Bool m_useFormations;
	unsigned char m_bfmeBA[2];
	Real m_altCameraZoomOverride;
	Real m_altCameraPitchOverride;
	Real m_maxRetaliateDistance;
	Real m_retaliateFriendsRadius;
	Real m_chaseFromBehindLimit;
	Real m_castleSiegeStandBackDistance;
	Bool m_useLowLODTrees;
	unsigned char m_bfmeD5[3];
	AsciiString m_lowLodTreeName;
	AsciiString m_lowLodTreeNameNoGrab;
	AsciiString m_lowLodTreeNameNoHarvest;
	Real m_lowLodTreeScale;
	Bool m_disableTrees;
	unsigned char m_bfmeE9[3];
	Real m_unknownF0;
	void *m_sideInfo;
	void *m_sideBuildLists;
	void *m_namedLists;
	TAiData *m_next;
	char m_unknown104[0x10];
};

TAiData::TAiData() :
	m_structureSeconds( 0.0f ),
	m_teamSeconds( 0.0f ),
	m_resourcesWealthy( 0 ),
	m_resourcesPoor( 0 ),
	m_forceIdleFramesCount( 1 ),
	m_structuresWealthyMod( 0.0f ),
	m_teamWealthyMod( 0.0f ),
	m_structuresPoorMod( 0.0f ),
	m_teamPoorMod( 0.0f ),
	m_teamResourcesToBuild( 0.0f ),
	m_guardInnerModifierAI( 0.0f ),
	m_guardOuterModifierAI( 0.0f ),
	m_guardInnerModifierHuman( 0.0f ),
	m_guardOuterModifierHuman( 0.0f ),
	m_guardChaseUnitFrames( 0 ),
	m_guardEnemyScanRate( g_Va00DBA4E4 / 2 ),
	m_guardEnemyReturnScanRate( g_Va00DBA4E4 ),
	m_wallHeight( 0.0f ),
	m_alertRangeModifier( 0.0f ),
	m_aggressiveRangeModifier( 0.0f ),
	m_attackPriorityDistanceModifier( 0.0f ),
	m_maxRecruitDistance( 0.0f ),
	m_skirmishBaseDefenseExtraDistance( 0.0f ),
	m_repulsedDistance( 0.0f ),
	m_enableRepulsors( 0 ),
	m_forceSkirmishAI( 0 ),
	m_rotateSkirmishBases( 0 ),
	m_attackUsesLineOfSight( 1 ),
	m_attackIgnoreInsignificantBuildings( 0 ),
	m_minDistanceForGroup( 100.0f ),
	m_distanceRequiresGroup( 600.0f ),
	m_minClumpDensity( 0.5f ),
	m_infantryPathfindDiameter( 6 ),
	m_vehiclePathfindDiameter( 6 ),
	m_rebuildDelaySeconds( 10 ),
	m_supplyCenterSafeRadius( 250.0f ),
	m_aiDozerBoredRadiusModifier( 2.0f ),
	m_aiCrushesInfantry( 1 ),
	m_meleeApproachTolerance( 20.0f ),
	m_meleeApproachDist( 60.0f ),
	m_meleeAcquireLimitDist( 5.0f ),
	m_wadeWaterDepth( 50.0f ),
	m_formationColumnWidth( 65.0f ),
	m_formationRowDepth( 65.0f ),
	m_formationSquadSpacing( 30.0f ),
	m_narrowPassageScale( 1.0f ),
	m_unknownB0( 3.4028234663852886e+38f ),
	m_formationColumns( 2 ),
	m_waitForOthers( 0 ),
	m_hordesWaitForHordes( 1 ),
	m_attackMoveUsesFormations( 1 ),
	m_forceHordesToLowLOD( 1 ),
	m_allowForestFires( 0 ),
	m_useFormations( 1 ),
	m_altCameraZoomOverride( 1.4f ),
	m_altCameraPitchOverride( 0.5f ),
	m_maxRetaliateDistance( 200.0f ),
	m_retaliateFriendsRadius( 120.0f ),
	m_chaseFromBehindLimit( 50.0f ),
	m_castleSiegeStandBackDistance( 100.0f ),
	m_useLowLODTrees( 0 ),
	m_lowLodTreeName( "TreeF03" ),
	m_lowLodTreeNameNoGrab( "TreeF02" ),
	m_lowLodTreeNameNoHarvest( "PTStump02" ),
	m_lowLodTreeScale( 0.55f ),
	m_disableTrees( 0 ),
	m_sideInfo( 0 ),
	m_sideBuildLists( 0 ),
	m_namedLists( 0 ),
	m_next( 0 )
{
	m_unknownF0 = 1.0f;
}

#include "subsystem_interface.h"
#include <list>
class AIGroup;
// Full target new-expression extent1D200 is proven by the167B AI caller;
// construction implementation is the separately rowed Pathfinder ctor.
class Pathfinder {public: Pathfinder(); char storage[0x1D200];};
class AI : public SubsystemInterface, public Snapshot
{
public:
 AI(); virtual ~AI();
 virtual void init(); virtual void reset(); virtual void update();
 virtual void loadPostProcess(); virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer *);
private:
 Pathfinder *m_pathfinder;
 _STL::list<AIGroup *> m_groupList;
 TAiData *m_aiData;
 int m_nextGroupID,m_nextFormationID;
};
AI::AI():m_nextGroupID(0),m_nextFormationID(0)
{
 m_aiData=new TAiData;
 m_pathfinder=new Pathfinder;
}
