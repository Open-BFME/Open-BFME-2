// ?loadFromDict@TeamTemplateInfo@@QAEXPAVDict@@@Z
// cl: /DBFME_ASCII_KEEP_COPY_SET_BODY /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// TeamTemplateInfo dictionary loader, RVA 0x0039FEBB..0x003A0CD1, 3606 bytes.
// Reference semantic guide: open-bfme-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngine/Source/Common/RTS/TeamTemplateInfoConstructor.cpp.
// Target facts: reset-prefix and nullable Dict guard (not a constructor),
// seven 24-byte unit records, waypoint home, 32 script hooks, teamType clamp.
// Each field offset and each StaticNameKey cache/string pair is read from retail.
// The donor supplies dictionary-loading semantics; loadFromDict is descriptive,
// not a recovered original spelling. The class name has independent target
// evidence in the TeamTemplateInfo vtable name getter (VA 0x00C1AE70).
// Direct target calls are in the TeamTemplateInfo constructor at 0x003A285D
// and the reset/reload path at 0x003A2C94.
// Assign the home member directly: VC7.1 then restores ESI before EDI
// after the waypoint copy, exactly as retail. A cached destination pointer
// reverses those independent restores. keyToName uses its verified provider.
// The existing lazy-cache owner is called directly; no alias pin is required.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
#include <string.h>
extern int g_Va00DBA4E4; // LogicFramesPerSecond: target initial value 5, existing owner ColdGlobalDwordGetters.cpp.
enum NameKeyType { NAMEKEY_INVALID=0 };
enum AttitudeType { AI_NORMAL=0 };
enum VeterancyLevel { LEVEL_REGULAR=0 };
class Rva00148F5ECache { public: NameKeyType get(); };
class StaticNameKey {
public: mutable int m_key; const char *m_name;
};
static __forceinline NameKeyType teamKey(const StaticNameKey &cache) { return ((Rva00148F5ECache *)&cache)->get(); }
class NameKeyGenerator {
public: const AsciiString &keyToName(NameKeyType); NameKeyType nameToKey(const AsciiString &);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Dict {
public:
 int getInt(int,bool *exists=0) const;
 float getReal(int,bool *exists=0) const;
 bool getBool(int,bool *exists=0) const;
 AsciiString getAsciiString(int,bool *exists=0) const;
};
class Waypoint { public:
 char prefix[8]; AsciiString name; Coord3D m_location; int m_18; Waypoint *m_pNext;
 const AsciiString &getName() const { return name; }
 const Coord3D *getLocation() const { return &m_location; }
};
class TerrainLogic {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18) SLOT(1c)
 SLOT(20) SLOT(24) SLOT(28) SLOT(2c) SLOT(30) SLOT(34) SLOT(38) SLOT(3c)
 SLOT(40) SLOT(44) SLOT(48) SLOT(4c) SLOT(50) SLOT(54) SLOT(58) SLOT(5c)
 SLOT(60) SLOT(64) SLOT(68) SLOT(6c) SLOT(70) SLOT(74) SLOT(78) SLOT(7c) SLOT(80)
#undef SLOT
 virtual Waypoint *getFirstWaypoint();
};
extern TerrainLogic *TheTerrainLogic;
struct TCreateUnitsInfo {
 int minUnits,maxUnits,experienceLevel; AsciiString upgradeList,unitThingName; char unknown14[4];
};
enum {MAX_GENERIC_SCRIPTS=32};
class TeamTemplateInfo {
public:
 void loadFromDict(Dict*);
 char vtable[4];
 TCreateUnitsInfo m_unitsInfo[7];
 int m_numUnitsInfo;
 Coord3D m_homeLocation;
 bool m_hasHomeLocation;
 AsciiString m_scriptOnCreate,m_teamEventsList,m_scriptOnIdle;
 int m_initialIdleFrames;
 AsciiString m_scriptOnEnemySighted,m_scriptOnAllClear,m_scriptOnUnitDestroyed,m_scriptOnDestroyed;
 float m_destroyedThreshold;
 bool m_isAIRecruitable,m_isBaseDefense,m_isPerimeterDefense,m_automaticallyReinforce;
 bool m_transportsReturn,m_avoidThreats,m_attackCommonTarget;
 int m_maxInstances,m_productionPriority,m_productionPrioritySuccessIncrease,m_productionPriorityFailureDecrease;
 AttitudeType m_initialTeamAttitude;
 AsciiString m_transportUnitType,m_startReinforceWaypoint;
 bool m_teamStartsFull,m_transportsExit;
 VeterancyLevel m_veterancy;
 AsciiString m_productionCondition;
 bool m_executeActions;
 AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS];
 int unknown198,m_teamType,unknown1A0,unknown1A4,unknown1A8,unknown1AC,unknown1B0;
 int counters1B4[7],counters1D0[7];
};

typedef char TeamTemplateInfoSize[sizeof(TeamTemplateInfo)==0x1EC ? 1 : -1];
extern const StaticNameKey TheKey_teamHome; // Existing WellKnownKeys definition: teamHome
extern const StaticNameKey TheKey_teamUnitType1; // Existing WellKnownKeys definition: teamUnitType1
extern const StaticNameKey TheKey_teamUnitMinCount1; // Existing WellKnownKeys definition: teamUnitMinCount1
extern const StaticNameKey TheKey_teamUnitMaxCount1; // Existing WellKnownKeys definition: teamUnitMaxCount1
extern const StaticNameKey TheKey_teamUnitExperienceLevel1 = {0,"teamUnitExperienceLevel1"};
extern const StaticNameKey TheKey_teamUnitUpgradeList1 = {0,"teamUnitUpgradeList1"};
extern const StaticNameKey TheKey_teamUnitType2; // Existing WellKnownKeys definition: teamUnitType2
extern const StaticNameKey TheKey_teamUnitMinCount2; // Existing WellKnownKeys definition: teamUnitMinCount2
extern const StaticNameKey TheKey_teamUnitMaxCount2; // Existing WellKnownKeys definition: teamUnitMaxCount2
extern const StaticNameKey TheKey_teamUnitExperienceLevel2 = {0,"teamUnitExperienceLevel2"};
extern const StaticNameKey TheKey_teamUnitUpgradeList2 = {0,"teamUnitUpgradeList2"};
extern const StaticNameKey TheKey_teamUnitType3; // Existing WellKnownKeys definition: teamUnitType3
extern const StaticNameKey TheKey_teamUnitMinCount3; // Existing WellKnownKeys definition: teamUnitMinCount3
extern const StaticNameKey TheKey_teamUnitMaxCount3; // Existing WellKnownKeys definition: teamUnitMaxCount3
extern const StaticNameKey TheKey_teamUnitExperienceLevel3 = {0,"teamUnitExperienceLevel3"};
extern const StaticNameKey TheKey_teamUnitUpgradeList3 = {0,"teamUnitUpgradeList3"};
extern const StaticNameKey TheKey_teamUnitType4; // Existing WellKnownKeys definition: teamUnitType4
extern const StaticNameKey TheKey_teamUnitMinCount4; // Existing WellKnownKeys definition: teamUnitMinCount4
extern const StaticNameKey TheKey_teamUnitMaxCount4; // Existing WellKnownKeys definition: teamUnitMaxCount4
extern const StaticNameKey TheKey_teamUnitExperienceLevel4 = {0,"teamUnitExperienceLevel4"};
extern const StaticNameKey TheKey_teamUnitUpgradeList4 = {0,"teamUnitUpgradeList4"};
extern const StaticNameKey TheKey_teamUnitType5; // Existing WellKnownKeys definition: teamUnitType5
extern const StaticNameKey TheKey_teamUnitMinCount5; // Existing WellKnownKeys definition: teamUnitMinCount5
extern const StaticNameKey TheKey_teamUnitMaxCount5; // Existing WellKnownKeys definition: teamUnitMaxCount5
extern const StaticNameKey TheKey_teamUnitExperienceLevel5 = {0,"teamUnitExperienceLevel5"};
extern const StaticNameKey TheKey_teamUnitUpgradeList5 = {0,"teamUnitUpgradeList5"};
extern const StaticNameKey TheKey_teamUnitType6; // Existing WellKnownKeys definition: teamUnitType6
extern const StaticNameKey TheKey_teamUnitMinCount6; // Existing WellKnownKeys definition: teamUnitMinCount6
extern const StaticNameKey TheKey_teamUnitMaxCount6; // Existing WellKnownKeys definition: teamUnitMaxCount6
extern const StaticNameKey TheKey_teamUnitExperienceLevel6 = {0,"teamUnitExperienceLevel6"};
extern const StaticNameKey TheKey_teamUnitUpgradeList6 = {0,"teamUnitUpgradeList6"};
extern const StaticNameKey TheKey_teamUnitType7; // Existing WellKnownKeys definition: teamUnitType7
extern const StaticNameKey TheKey_teamUnitMinCount7; // Existing WellKnownKeys definition: teamUnitMinCount7
extern const StaticNameKey TheKey_teamUnitMaxCount7; // Existing WellKnownKeys definition: teamUnitMaxCount7
extern const StaticNameKey TheKey_teamUnitExperienceLevel7 = {0,"teamUnitExperienceLevel7"};
extern const StaticNameKey TheKey_teamUnitUpgradeList7 = {0,"teamUnitUpgradeList7"};
extern const StaticNameKey TheKey_teamOnCreateScript; // Existing WellKnownKeys definition: teamOnCreateScript
extern const StaticNameKey TheKey_teamOnIdleScript; // Existing WellKnownKeys definition: teamOnIdleScript
extern const StaticNameKey TheKey_teamEventsList = {0,"teamEventsList"};
extern const StaticNameKey TheKey_teamInitialIdleSeconds = {0,"teamInitialIdleSeconds"};
extern const StaticNameKey TheKey_teamOnUnitDestroyedScript; // Existing WellKnownKeys definition: teamOnUnitDestroyedScript
extern const StaticNameKey TheKey_teamOnDestroyedScript; // Existing WellKnownKeys definition: teamOnDestroyedScript
extern const StaticNameKey TheKey_teamDestroyedThreshold; // Existing WellKnownKeys definition: teamDestroyedThreshold
extern const StaticNameKey TheKey_teamEnemySightedScript; // Existing WellKnownKeys definition: teamEnemySightedScript
extern const StaticNameKey TheKey_teamAllClearScript; // Existing WellKnownKeys definition: teamAllClearScript
extern const StaticNameKey TheKey_teamAutoReinforce; // Existing WellKnownKeys definition: teamAutoReinforce
extern const StaticNameKey TheKey_teamIsAIRecruitable; // Existing WellKnownKeys definition: teamIsAIRecruitable
extern const StaticNameKey TheKey_teamIsBaseDefense; // Existing WellKnownKeys definition: teamIsBaseDefense
extern const StaticNameKey TheKey_teamIsPerimeterDefense; // Existing WellKnownKeys definition: teamIsPerimeterDefense
extern const StaticNameKey TheKey_teamAggressiveness; // Existing WellKnownKeys definition: teamAggressiveness
extern const StaticNameKey TheKey_teamTransportsReturn; // Existing WellKnownKeys definition: teamTransportsReturn
extern const StaticNameKey TheKey_teamAvoidThreats; // Existing WellKnownKeys definition: teamAvoidThreats
extern const StaticNameKey TheKey_teamAttackCommonTarget; // Existing WellKnownKeys definition: teamAttackCommonTarget
extern const StaticNameKey TheKey_teamMaxInstances; // Existing WellKnownKeys definition: teamMaxInstances
extern const StaticNameKey TheKey_teamProductionCondition; // Existing WellKnownKeys definition: teamProductionCondition
extern const StaticNameKey TheKey_teamProductionPriority; // Existing WellKnownKeys definition: teamProductionPriority
extern const StaticNameKey TheKey_teamProductionPrioritySuccessIncrease; // Existing WellKnownKeys definition: teamProductionPrioritySuccessIncrease
extern const StaticNameKey TheKey_teamProductionPriorityFailureDecrease; // Existing WellKnownKeys definition: teamProductionPriorityFailureDecrease
extern const StaticNameKey TheKey_teamTransport; // Existing WellKnownKeys definition: teamTransport
extern const StaticNameKey TheKey_teamReinforcementOrigin; // Existing WellKnownKeys definition: teamReinforcementOrigin
extern const StaticNameKey TheKey_teamStartsFull; // Existing WellKnownKeys definition: teamStartsFull
extern const StaticNameKey TheKey_teamTransportsExit; // Existing WellKnownKeys definition: teamTransportsExit
extern const StaticNameKey TheKey_teamVeterancy; // Existing WellKnownKeys definition: teamVeterancy
extern const StaticNameKey TheKey_teamExecutesActionsOnCreate; // Existing WellKnownKeys definition: teamExecutesActionsOnCreate
extern const StaticNameKey TheKey_teamGenericScriptHook; // Existing WellKnownKeys definition: teamGenericScriptHook
extern const StaticNameKey TheKey_teamType = {0,"teamType"};
void TeamTemplateInfo::loadFromDict(Dict *d)
{
 unknown198 = -1; unknown1A4 = -1; unknown1AC = -1; unknown1A0 = -1;
 m_productionPriority=0; unknown1A8=1; unknown1B0=0; m_teamType=0; m_numUnitsInfo=0;
 memset(counters1B4,0,sizeof(counters1B4)); memset(counters1D0,0,sizeof(counters1D0));
 if (!d) return;
	Bool exists;
	Int min, max, experience;
	AsciiString upgradeList;
	AsciiString templateName;
	min = d->getInt(teamKey(TheKey_teamUnitMinCount1), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount1), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel1), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList1), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType1), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount2), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount2), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel2), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList2), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType2), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount3), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount3), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel3), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList3), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType3), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount4), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount4), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel4), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList4), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType4), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount5), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount5), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel5), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList5), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType5), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount6), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount6), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel6), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList6), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType6), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(teamKey(TheKey_teamUnitMinCount7), &exists);
	max = d->getInt(teamKey(TheKey_teamUnitMaxCount7), &exists);
	experience = d->getInt(teamKey(TheKey_teamUnitExperienceLevel7), &exists);
	upgradeList = d->getAsciiString(teamKey(TheKey_teamUnitUpgradeList7), &exists);
	templateName = d->getAsciiString(teamKey(TheKey_teamUnitType7), &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	AsciiString waypoint = d->getAsciiString(teamKey(TheKey_teamHome), &exists);
	m_homeLocation.x = m_homeLocation.y = 0;
	m_homeLocation.z = 0;
	m_hasHomeLocation = false;
	if (exists) {
		for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->m_pNext) {
			if (((const StringBase<char> *)&way->getName())->compare(*(const StringBase<char> *)&waypoint) == 0) {
				m_homeLocation = *way->getLocation();
				m_hasHomeLocation = true;
			}
		}
	}

	m_scriptOnCreate = d->getAsciiString(teamKey(TheKey_teamOnCreateScript), &exists);
	m_teamEventsList = d->getAsciiString(teamKey(TheKey_teamEventsList), &exists);
	m_isAIRecruitable	= d->getBool(teamKey(TheKey_teamIsAIRecruitable), &exists);
	if (!exists) {
		m_isAIRecruitable = false;
	}
	m_isBaseDefense	= d->getBool(teamKey(TheKey_teamIsBaseDefense), &exists);
	m_isPerimeterDefense	= d->getBool(teamKey(TheKey_teamIsPerimeterDefense), &exists);
	m_automaticallyReinforce = d->getBool(teamKey(TheKey_teamAutoReinforce), &exists);

	Int interact	= d->getInt(teamKey(TheKey_teamAggressiveness), &exists);
	m_initialTeamAttitude = AI_NORMAL;
	if (exists) {
		m_initialTeamAttitude = (AttitudeType) interact;
	}

	m_transportsReturn	= d->getBool(teamKey(TheKey_teamTransportsReturn), &exists);
	m_avoidThreats = d->getBool(teamKey(TheKey_teamAvoidThreats), &exists);

	m_attackCommonTarget = d->getBool(teamKey(TheKey_teamAttackCommonTarget), &exists);

	m_maxInstances = d->getInt(teamKey(TheKey_teamMaxInstances), &exists);

	m_scriptOnIdle = d->getAsciiString(teamKey(TheKey_teamOnIdleScript), &exists);
	m_initialIdleFrames = g_Va00DBA4E4 * d->getInt(teamKey(TheKey_teamInitialIdleSeconds), &exists);
	m_scriptOnEnemySighted = d->getAsciiString(teamKey(TheKey_teamEnemySightedScript), &exists);
	m_scriptOnAllClear = d->getAsciiString(teamKey(TheKey_teamAllClearScript), &exists);
	m_scriptOnDestroyed = d->getAsciiString(teamKey(TheKey_teamOnDestroyedScript), &exists);
	m_destroyedThreshold = d->getReal(teamKey(TheKey_teamDestroyedThreshold), &exists);
	m_scriptOnUnitDestroyed = d->getAsciiString(teamKey(TheKey_teamOnUnitDestroyedScript), &exists);

	m_productionPriority = d->getInt(teamKey(TheKey_teamProductionPriority), &exists);
	m_productionPrioritySuccessIncrease = d->getInt(teamKey(TheKey_teamProductionPrioritySuccessIncrease), &exists);
	m_productionPriorityFailureDecrease = d->getInt(teamKey(TheKey_teamProductionPriorityFailureDecrease), &exists);

	// Production scripts stuff
	m_productionCondition = d->getAsciiString(teamKey(TheKey_teamProductionCondition), &exists);
	m_executeActions = d->getBool(teamKey(TheKey_teamExecutesActionsOnCreate), &exists);


	// Which scripts to attempt during run?
	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i) {
		AsciiString keyName;
		keyName.format("%s%d", TheNameKeyGenerator->keyToName(teamKey(TheKey_teamGenericScriptHook)).str(), i);
		m_teamGenericScripts[i] = d->getAsciiString(TheNameKeyGenerator->nameToKey(keyName), &exists);
		if (!exists) {
			((StringBase<char> *)&m_teamGenericScripts[i])->clear();
		}
	}

	// reinforcement team info.
	m_transportUnitType = d->getAsciiString(teamKey(TheKey_teamTransport), &exists);
	m_transportsExit = d->getBool(teamKey(TheKey_teamTransportsExit), &exists);
	m_teamStartsFull = d->getBool(teamKey(TheKey_teamStartsFull), &exists);
	m_startReinforceWaypoint = d->getAsciiString(teamKey(TheKey_teamReinforcementOrigin), &exists);
	m_veterancy = (VeterancyLevel)d->getInt(teamKey(TheKey_teamVeterancy), &exists);
 int teamType=d->getInt(teamKey(TheKey_teamType),&exists);
 if(exists) { if(teamType<0) m_teamType=0; else m_teamType=teamType; }
}
