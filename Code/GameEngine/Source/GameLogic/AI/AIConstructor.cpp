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

class Rva002FE620;
class Rva002FED8D;
class Gen0014AE40;
class TAiData : public Snapshot
{
public:
	TAiData();
	friend class AI;
	void addNamedList(Rva002FED8D*);
	void addFactionBuildList(Gen0014AE40*);
	TAiData&operator=(const TAiData&other);
 TAiData *next()const{return m_next;}
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
	Real m_minDistanceForGroup;
	Real m_distanceRequiresGroup;
	Real m_minClumpDensity;
	UnsignedInt m_infantryPathfindDiameter;
	UnsignedInt m_vehiclePathfindDiameter;
	UnsignedInt m_rebuildDelaySeconds;
	Real m_supplyCenterSafeRadius;
	Real m_aiDozerBoredRadiusModifier;
	Bool m_aiCrushesInfantry;
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
	Real m_altCameraZoomOverride;
	Real m_altCameraPitchOverride;
	Real m_maxRetaliateDistance;
	Real m_retaliateFriendsRadius;
	Real m_chaseFromBehindLimit;
	Real m_castleSiegeStandBackDistance;
	Bool m_useLowLODTrees;
	AsciiString m_lowLodTreeName;
	AsciiString m_lowLodTreeNameNoGrab;
	AsciiString m_lowLodTreeNameNoHarvest;
	Real m_lowLodTreeScale;
	Bool m_disableTrees;
	Real m_unknownF0;
	Rva002FE620 *m_sideInfo;
	Gen0014AE40 *m_sideBuildLists;
	Rva002FED8D *m_namedLists;
	TAiData *m_next;
	unsigned int m_unknown104[4];
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

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class AIGroup;
namespace _STL {template<> _List_base<AIGroup *,allocator<AIGroup *> >::~_List_base();}
// Full target new-expression extent1D200 is proven by the167B AI caller;
// construction implementation is the separately rowed Pathfinder ctor.
class PathfindServicesInterface {public: virtual void slot0()=0;virtual void slot1()=0;virtual void slot2()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;};
class Pathfinder:public PathfindServicesInterface,public Snapshot {public: Pathfinder();virtual ~Pathfinder();virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void loadPostProcess();virtual const char *GetSnapshotName()const;virtual void xfer(Xfer*);char storage[0x1D200-8];};
class AI : public SubsystemInterface, public Snapshot
{
public:
 AI(); virtual ~AI();
 void newOverride();
 __declspec(noinline) void addSideInfo(Rva002FE620*);
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

TAiData&TAiData::operator=(const TAiData&other){
 m_structureSeconds=other.m_structureSeconds;
 m_teamSeconds=other.m_teamSeconds;
 m_resourcesWealthy=other.m_resourcesWealthy;
 m_resourcesPoor=other.m_resourcesPoor;
 m_forceIdleFramesCount=other.m_forceIdleFramesCount;
 m_structuresWealthyMod=other.m_structuresWealthyMod;
 m_teamWealthyMod=other.m_teamWealthyMod;
 m_structuresPoorMod=other.m_structuresPoorMod;
 m_teamPoorMod=other.m_teamPoorMod;
 m_teamResourcesToBuild=other.m_teamResourcesToBuild;
 m_guardInnerModifierAI=other.m_guardInnerModifierAI;
 m_guardOuterModifierAI=other.m_guardOuterModifierAI;
 m_guardInnerModifierHuman=other.m_guardInnerModifierHuman;
 m_guardOuterModifierHuman=other.m_guardOuterModifierHuman;
 m_guardChaseUnitFrames=other.m_guardChaseUnitFrames;
 m_guardEnemyScanRate=other.m_guardEnemyScanRate;
 m_guardEnemyReturnScanRate=other.m_guardEnemyReturnScanRate;
 m_wallHeight=other.m_wallHeight;
 m_alertRangeModifier=other.m_alertRangeModifier;
 m_aggressiveRangeModifier=other.m_aggressiveRangeModifier;
 m_attackPriorityDistanceModifier=other.m_attackPriorityDistanceModifier;
 m_maxRecruitDistance=other.m_maxRecruitDistance;
 m_skirmishBaseDefenseExtraDistance=other.m_skirmishBaseDefenseExtraDistance;
 m_repulsedDistance=other.m_repulsedDistance;
 m_enableRepulsors=other.m_enableRepulsors;
 m_forceSkirmishAI=other.m_forceSkirmishAI;
 m_rotateSkirmishBases=other.m_rotateSkirmishBases;
 m_attackUsesLineOfSight=other.m_attackUsesLineOfSight;
 m_attackIgnoreInsignificantBuildings=other.m_attackIgnoreInsignificantBuildings;
 m_minDistanceForGroup=other.m_minDistanceForGroup;
 m_distanceRequiresGroup=other.m_distanceRequiresGroup;
 m_minClumpDensity=other.m_minClumpDensity;
 m_infantryPathfindDiameter=other.m_infantryPathfindDiameter;
 m_vehiclePathfindDiameter=other.m_vehiclePathfindDiameter;
 m_rebuildDelaySeconds=other.m_rebuildDelaySeconds;
 m_supplyCenterSafeRadius=other.m_supplyCenterSafeRadius;
 m_aiDozerBoredRadiusModifier=other.m_aiDozerBoredRadiusModifier;
 m_aiCrushesInfantry=other.m_aiCrushesInfantry;
 m_meleeApproachTolerance=other.m_meleeApproachTolerance;
 m_meleeApproachDist=other.m_meleeApproachDist;
 m_meleeAcquireLimitDist=other.m_meleeAcquireLimitDist;
 m_wadeWaterDepth=other.m_wadeWaterDepth;
 m_formationColumnWidth=other.m_formationColumnWidth;
 m_formationRowDepth=other.m_formationRowDepth;
 m_formationSquadSpacing=other.m_formationSquadSpacing;
 m_narrowPassageScale=other.m_narrowPassageScale;
 m_unknownB0=other.m_unknownB0;
 m_formationColumns=other.m_formationColumns;
 m_waitForOthers=other.m_waitForOthers;
 m_hordesWaitForHordes=other.m_hordesWaitForHordes;
 m_attackMoveUsesFormations=other.m_attackMoveUsesFormations;
 m_forceHordesToLowLOD=other.m_forceHordesToLowLOD;
 m_allowForestFires=other.m_allowForestFires;
 m_useFormations=other.m_useFormations;
 m_altCameraZoomOverride=other.m_altCameraZoomOverride;
 m_altCameraPitchOverride=other.m_altCameraPitchOverride;
 m_maxRetaliateDistance=other.m_maxRetaliateDistance;
 m_retaliateFriendsRadius=other.m_retaliateFriendsRadius;
 m_chaseFromBehindLimit=other.m_chaseFromBehindLimit;
 m_castleSiegeStandBackDistance=other.m_castleSiegeStandBackDistance;
 m_useLowLODTrees=other.m_useLowLODTrees;
 m_lowLodTreeName=other.m_lowLodTreeName;
 m_lowLodTreeNameNoGrab=other.m_lowLodTreeNameNoGrab;
 m_lowLodTreeNameNoHarvest=other.m_lowLodTreeNameNoHarvest;
 m_lowLodTreeScale=other.m_lowLodTreeScale;
 m_disableTrees=other.m_disableTrees;
 m_unknownF0=other.m_unknownF0;
 m_sideInfo=other.m_sideInfo;
 m_sideBuildLists=other.m_sideBuildLists;
 m_namedLists=other.m_namedLists;
 m_next=other.m_next;
 for(unsigned int i=0;i<4;++i)m_unknown104[i]=other.m_unknown104[i];
 return *this;
}

// Native703B assignment at2FD7EF copies named scalar values, three strings,
// four intrusive links and four opaque final dwords. Padding is skipped.
// BF1 f989 TAiDataAssign is the semantic guide; BFME2 constructor/native
// stores prove target offsets and AsciiString usage at DC/E0/E4.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva002FE8CCDeleteView{public:virtual void*destroy(int);};
class BuildListInfo{public:virtual~BuildListInfo();BuildListInfo*duplicate();};
class Gen0014AE40{public:Gen0014AE40(AsciiString);virtual~Gen0014AE40();AsciiString side;BuildListInfo*build;Gen0014AE40*next;};
// BF1 f989 TAiData_addFactionBuildList guides the registration/ownership.
// Target2FE8CC..2FE940 RET4 proves headF8 and 16B node fields4/8/C.
// Slot0 is a deletion ABI view: flag0 returns the allocation pointer which
// native feeds to ordinary cdecl scalar delete. No original slot name inferred.
// Native clears build and next before loading the slot; preserve this order.
void TAiData::addFactionBuildList(Gen0014AE40*incoming){
 Gen0014AE40*info=m_sideBuildLists;
 while(info){
  if(incoming->side.compare(info->side)==0){
   if(info->build)::operator delete(((Rva002FE8CCDeleteView*)info->build)->destroy(0));
   info->build=incoming->build;incoming->build=0;incoming->next=0;_ReadWriteBarrier();
   ::operator delete(((Rva002FE8CCDeleteView*)incoming)->destroy(0));return;
  }
  info=info->next;
 }
 incoming->next=m_sideBuildLists;m_sideBuildLists=incoming;
}

class Rva002FE620{public:Rva002FE620();virtual~Rva002FE620();unsigned char body[0x1B8];Rva002FE620*next;};
class Rva0014A470{public:Rva0014A470&operator=(const Rva0014A470&);};
struct Rva002FFC74Record{unsigned char bytes[8];};
class Rva002FED8D{public:Rva002FED8D(AsciiString);virtual~Rva002FED8D();AsciiString name;unsigned int value;_STL::list<Rva002FFC74Record>tail;Rva002FED8D*next;};
void AI::newOverride(){
 TAiData*cur=m_aiData;
 m_aiData=new TAiData;
 *m_aiData=*cur;
 m_aiData->m_sideInfo=0;
 for(Rva002FE620*info=cur->m_sideInfo;info;info=info->next){
  Rva002FE620*newInfo=new Rva002FE620;
  *(Rva0014A470*)newInfo=*(Rva0014A470*)info;
  newInfo->next=0;
  addSideInfo(newInfo);
 }
 m_aiData->m_sideBuildLists=0;
 for(Gen0014AE40*build=cur->m_sideBuildLists;build;build=build->next){
  Gen0014AE40*node=new Gen0014AE40(build->side);
  node->next=0;
  if(build->build)node->build=build->build->duplicate();
  m_aiData->addFactionBuildList(node);
 }
 m_aiData->m_namedLists=0;
 for(Rva002FED8D*named=cur->m_namedLists;named;named=named->next){
  Rva002FED8D*node=new Rva002FED8D(named->name);
  node->tail=named->tail;node->value=named->value;
  m_aiData->addNamedList(node);
 }
 m_aiData->m_next=cur;
}

void AI::addSideInfo(Rva002FE620*info){TAiData*link=m_aiData;Rva002FE620*previous=link->m_sideInfo;info->next=previous;link->m_sideInfo=info;}

inline void TAiData::addNamedList(Rva002FED8D*node){node->next=m_namedLists;m_namedLists=node;}

// BF1f989 AINewOverride.cpp guides the three deep copies and old-data link.
// Native2FFDC3..2FFF72 RET0 proves allocation114, three-list offsetsF4/F8/FC,
// side-info1C0/name-list14/side-build10, and every listed constructor/assignment.
// Existing25B AI addSideInfo provider is reconciled here from its private view.

// Native2FEBB7..2FEC4A RET0; namedAI vtables and constructor identify owner.
// BF1 AI destructor supplies the pointer deletion semantics. The native
// EH state1 before list cleanup requires an out-of-line list destructor:
// its definition in this TU would prove it nonthrowing and erase that store.
AI::~AI()
{
 if(m_pathfinder)::delete m_pathfinder;
 m_pathfinder=0;
 while(m_aiData) {
  TAiData *current=m_aiData;
  m_aiData=m_aiData->next();
  ::delete current;
 }
}
