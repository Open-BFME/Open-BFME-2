// cl: /O1 /G7 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP=
// Split from AIConstructor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
// BF1 f98983a7d TAiDataCtor.cpp is the semantic and member-name guide.
// Native670B 2FE382..2FE620 supplies every offset and constant:50-unit
// water depth;5-unit acquire limit; extra floatB0=FLT_MAX andF0=1.0;
// string membersDC/E0/E4; pointersF4/F8/FC/100. AI constructor2FEA85
// allocates114B and calls this exact body. Unaccessed final10B remain opaque.
// Original TAiData and semantic member names are carried from the donor;
// target construction spine and Snapshot-family tableC071E4 corroborate
// the subsystem relationship. Extra field meanings remain unresolved.
// Existing global owner BfmeLogicFramesPerSecond is read normally twice as retail does.

typedef float Real;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Xfer;

#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
extern int BfmeLogicFramesPerSecond;

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
protected:
	virtual void xfer( Xfer *xfer );
public:
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
	Real m_minFlightHeight;
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
	Real m_artilleryMaxFriendlyFire;
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
	m_guardEnemyScanRate( BfmeLogicFramesPerSecond / 2 ),
	m_guardEnemyReturnScanRate( BfmeLogicFramesPerSecond ),
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
	m_minFlightHeight( 3.4028234663852886e+38f ),
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
	m_artilleryMaxFriendlyFire = 1.0f;
}

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
#include "../../../Include/GameLogic/AIPathfind.h"
class INI;
#include "../../../Include/GameLogic/AI.h"
// ?TAiData::loadPostProcess present-unmatched
void TAiData::loadPostProcess()
{
}

AI::AI():m_nextGroupID(0),m_nextFormationID(0)
{
 m_aiData=new TAiData;
 m_pathfinder=new Pathfinder;
}


// Native703B assignment at2FD7EF copies named scalar values, three strings,
// four intrusive links and four opaque final dwords. Padding is skipped.
// BF1 f989 TAiDataAssign is the semantic guide; BFME2 constructor/native
// stores prove target offsets and AsciiString usage at DC/E0/E4.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"
class Gen0014AE40{public:Gen0014AE40(AsciiString);virtual~Gen0014AE40();AsciiString side;BuildListInfo*build;Gen0014AE40*next;};

class Rva002FE620{public:Rva002FE620();virtual~Rva002FE620();unsigned char body[0x1B8];Rva002FE620*next;};
class Rva0014A470{public:Rva0014A470&operator=(const Rva0014A470&);};
struct Rva002FFC74Record
{
public:
	Rva002FFC74Record();
	Rva002FFC74Record(const Rva002FFC74Record&);
	~Rva002FFC74Record();
	Rva002FFC74Record&operator=(const Rva002FFC74Record&);
	bool operator==(const Rva002FFC74Record&) const;
	bool operator<(const Rva002FFC74Record&) const;
	unsigned char bytes[8]; // +0x00
};
// The named-list copy calls the separately rowed assignment at 0x002FFC74.
// Its opaque record declaration cannot supply the element's nontrivial
// assignment or cleanup. Reuse the exact provider instead of emitting a POD copy.
namespace _STL {
template <> list<Rva002FFC74Record, allocator<Rva002FFC74Record> >&
list<Rva002FFC74Record, allocator<Rva002FFC74Record> >::operator=(const list&);
}

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

struct FieldParse;
#include "../../../Include/Common/INI/INI.h"
extern AI *TheAI;
extern const FieldParse s_aiDataFieldParseTable[];

// Zero Hour's INI field-parse record: the token, its parser, the parser's
// user data and the field offset within TAiData.
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"
// The skirmish build-list parser the SkirmishBuildList token runs (rowed 0x002FE9FC).
class Rva0014C090
{
public:
	static void parseDefinition(INI *ini, void *instance, void *store, const void *userData);
};

// The AIData block's fields, retail VA 0x00C06650 (74 records and the null
// terminator, 0x4B0 bytes): tokens, parsers and TAiData offsets read from retail.
const FieldParse s_aiDataFieldParseTable[] =
{
	{ "StructureSeconds", &INI::parseReal, 0, 0x4 },
	{ "TeamSeconds", &INI::parseReal, 0, 0x8 },
	{ "Wealthy", &INI::parseInt, 0, 0xC },
	{ "Poor", &INI::parseInt, 0, 0x10 },
	{ "ForceIdleMSEC", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "StructuresWealthyRate", &INI::parseReal, 0, 0x18 },
	{ "TeamsWealthyRate", &INI::parseReal, 0, 0x1C },
	{ "StructuresPoorRate", &INI::parseReal, 0, 0x20 },
	{ "TeamsPoorRate", &INI::parseReal, 0, 0x24 },
	{ "TeamResourcesToStart", &INI::parseReal, 0, 0x28 },
	{ "GuardInnerModifierAI", &INI::parseReal, 0, 0x2C },
	{ "GuardOuterModifierAI", &INI::parseReal, 0, 0x30 },
	{ "GuardInnerModifierHuman", &INI::parseReal, 0, 0x34 },
	{ "GuardOuterModifierHuman", &INI::parseReal, 0, 0x38 },
	{ "GuardChaseUnitsDuration", &INI::parseDurationUnsignedInt, 0, 0x3C },
	{ "GuardEnemyScanRate", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "GuardEnemyReturnScanRate", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ "SkirmishGroupFudgeDistance", &INI::parseReal, 0, 0x58 },
	{ "RepulsedDistance", &INI::parseReal, 0, 0x60 },
	{ "EnableRepulsors", &INI::parseBool, 0, 0x64 },
	{ "AlertRangeModifier", &INI::parseReal, 0, 0x4C },
	{ "AggressiveRangeModifier", &INI::parseReal, 0, 0x50 },
	{ "ForceSkirmishAI", &INI::parseBool, 0, 0x65 },
	{ "RotateSkirmishBases", &INI::parseBool, 0, 0x66 },
	{ "AttackUsesLineOfSight", &INI::parseBool, 0, 0x67 },
	{ "AttackIgnoreInsignificantBuildings", &INI::parseBool, 0, 0x68 },
	{ "AttackPriorityDistanceModifier", &INI::parseReal, 0, 0x54 },
	{ "MaxRecruitRadius", &INI::parseReal, 0, 0x5C },
	{ "WallHeight", &INI::parseReal, 0, 0x48 },
	{ "SideInfo", &AI::parseSideInfo, 0, 0x0 },
	{ "AttackPriority", &AI::parseAttackPriority, 0, 0x0 },
	{ "SkirmishBuildList", &Rva0014C090::parseDefinition, 0, 0x0 },
	{ "MinDistanceForGroup", &INI::parseReal, 0, 0x6C },
	{ "FormationEnemyDistance", &INI::parseReal, 0, 0x70 },
	{ "MinClumpDensity", &INI::parseReal, 0, 0x74 },
	{ "InfantryPathfindDiameter", &INI::parseInt, 0, 0x78 },
	{ "VehiclePathfindDiameter", &INI::parseInt, 0, 0x7C },
	{ "RebuildDelayTimeSeconds", &INI::parseInt, 0, 0x80 },
	{ "SupplyCenterSafeRadius", &INI::parseReal, 0, 0x84 },
	{ "AIDozerBoredRadiusModifier", &INI::parseReal, 0, 0x88 },
	{ "AICrushesInfantry", &INI::parseBool, 0, 0x8C },
	{ "MeleeApproachTolerance", &INI::parseReal, 0, 0x90 },
	{ "MeleeApproachDist", &INI::parseReal, 0, 0x94 },
	{ "WadeWaterDepth", &INI::parseReal, 0, 0x98 },
	{ "DeepWaterDepth", &INI::parseReal, 0, 0x9C },
	{ "FormationColumnWidth", &INI::parseReal, 0, 0xA0 },
	{ "FormationRowDepth", &INI::parseReal, 0, 0xA4 },
	{ "FormationSquadSpacing", &INI::parseReal, 0, 0xA8 },
	{ "FormationColumns", &INI::parseInt, 0, 0xB4 },
	{ "NarrowPassageScale", &INI::parseReal, 0, 0xAC },
	{ "HordesWaitForHordes", &INI::parseBool, 0, 0xB9 },
	{ "AttackMoveUsesFormations", &INI::parseBool, 0, 0xBA },
	{ "MinFlightHeight", &INI::parseReal, 0, 0xB0 },
	{ "ForceHordesToLowLOD", &INI::parseBool, 0, 0xBB },
	{ "AllowForestFires", &INI::parseBool, 0, 0xBC },
	{ "UseFormations", &INI::parseBool, 0, 0xBD },
	{ "WaitForOthers", &INI::parseBool, 0, 0xB8 },
	{ "AltCameraZoomOverride", &INI::parseReal, 0, 0xC0 },
	{ "AltCameraPitchOverride", &INI::parseReal, 0, 0xC4 },
	{ "MaxRetaliateDistance", &INI::parseReal, 0, 0xC8 },
	{ "RetaliateFriendsRadius", &INI::parseReal, 0, 0xCC },
	{ "ChaseFromBehindLimit", &INI::parseReal, 0, 0xD0 },
	{ "CastleSiegeStandBackDistance", &INI::parseReal, 0, 0xD4 },
	{ "BuildPhase1_PerSecondPriorityModifier", &INI::parseInt, 0, 0x104 },
	{ "BuildPhase2_PerSecondPriorityModifier", &INI::parseInt, 0, 0x108 },
	{ "BuildPhase3_PerSecondPriorityModifier", &INI::parseInt, 0, 0x10C },
	{ "BuildPhaseN_PerSecondPriorityModifier", &INI::parseInt, 0, 0x110 },
	{ "UseLowLODTrees", &INI::parseBool, 0, 0xD8 },
	{ "DisableTrees", &INI::parseBool, 0, 0xEC },
	{ "LowLodTreeName", &INI::parseAsciiString, 0, 0xDC },
	{ "LowLodTreeNameNoGrab", &INI::parseAsciiString, 0, 0xE0 },
	{ "LowLodTreeNameNoHarvest", &INI::parseAsciiString, 0, 0xE4 },
	{ "LowLodTreeScale", &INI::parseReal, 0, 0xE8 },
	{ "ArtilleryMaxFriendlyFire", &INI::parsePercentToReal, 0, 0xF0 },
	{ 0, 0, 0, 0 }
};


void AI::parseAiDataDefinition(INI *ini)
{
 if (TheAI)
 {
  if (ini->getLoadType() == 2)
   TheAI->newOverride();
  ini->initFromINI(TheAI->m_aiData, s_aiDataFieldParseTable);
 }
}
