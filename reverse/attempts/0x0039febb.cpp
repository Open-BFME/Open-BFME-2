// ?loadFromDict@TeamTemplateInfo@@QAEXPAVDict@@@Z
// partial score=0.99889 date=2026-10-06
// BFME2 TeamTemplateInfo dictionary loader, RVA 0x0039FEBB, 3606 bytes.
// Provisional descriptive method name loadFromDict; original spelling is unknown.
// Reference semantic guide: BFME1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngine/Source/Common/RTS/TeamTemplateInfoConstructor.cpp.
// Target evidence: Dict calls with teamHome, teamUnit1..7 and team script keys;
// reset-prefix followed by nullable Dict guard, seven 24-byte unit records,
// waypoint copy, 32 generic script names and teamType clamp at the tail.
// Target field offsets and key cache/string pairs read from retail independently.
// This is not the donor constructor: target performs no member construction.
// Partial: all 3606 bytes except four match after existing relocation resolution.
// At RVA 0x003A0776 compiler restores EDI then ESI, retail restores ESI then EDI.
// Tried equivalent copy/loop expressions, /G6 /Ob2 /Oy-; none resolves this.
// Key globals and callee providers still require ownership/link verification;
// NameKeyGenerator::keyToName, in particular, needs a proven provider.
// No progress claim or pins were added for this bank.
// cl: /Ireference/shims/gamewindow /O1 /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
#include "ascii_string.h"
#include "basetype.h"
#include <string.h>
extern int g_rva0058AD9FBase;
enum NameKeyType { NAMEKEY_INVALID=0 };
enum AttitudeType { AI_NORMAL=0 };
enum VeterancyLevel { LEVEL_REGULAR=0 };
class StaticNameKey {
public: mutable int m_key; const char *m_name; NameKeyType key() const; operator NameKeyType() const { return key(); }
};
class NameKeyGenerator {
public: const AsciiString &keyToName(NameKeyType); NameKeyType nameToKey(const AsciiString &);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Dict {
public:
 int getInt(int,bool *exists=0) const;
 float getReal(int,bool *exists=0) const;
 bool getBool(int,bool *exists=0) const;
 AsciiString getAsciiString(NameKeyType,bool *exists=0) const;
};
class Waypoint { public:
 char prefix[8]; AsciiString name; Coord3D m_location; int m_18; Waypoint *m_pNext;
 const AsciiString &getName() const { return name; }
 const Coord3D *getLocation() const { return &m_location; }
 Waypoint *getNext() const { return m_pNext; }
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
 int minUnits,maxUnits,experienceLevel; AsciiString upgradeList,unitThingName; int unknown14;
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
extern const StaticNameKey TheKey_teamHome = {0,"teamHome"};
extern const StaticNameKey TheKey_teamUnitType1 = {0,"teamUnitType1"};
extern const StaticNameKey TheKey_teamUnitMinCount1 = {0,"teamUnitMinCount1"};
extern const StaticNameKey TheKey_teamUnitMaxCount1 = {0,"teamUnitMaxCount1"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel1 = {0,"teamUnitExperienceLevel1"};
extern const StaticNameKey TheKey_teamUnitUpgradeList1 = {0,"teamUnitUpgradeList1"};
extern const StaticNameKey TheKey_teamUnitType2 = {0,"teamUnitType2"};
extern const StaticNameKey TheKey_teamUnitMinCount2 = {0,"teamUnitMinCount2"};
extern const StaticNameKey TheKey_teamUnitMaxCount2 = {0,"teamUnitMaxCount2"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel2 = {0,"teamUnitExperienceLevel2"};
extern const StaticNameKey TheKey_teamUnitUpgradeList2 = {0,"teamUnitUpgradeList2"};
extern const StaticNameKey TheKey_teamUnitType3 = {0,"teamUnitType3"};
extern const StaticNameKey TheKey_teamUnitMinCount3 = {0,"teamUnitMinCount3"};
extern const StaticNameKey TheKey_teamUnitMaxCount3 = {0,"teamUnitMaxCount3"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel3 = {0,"teamUnitExperienceLevel3"};
extern const StaticNameKey TheKey_teamUnitUpgradeList3 = {0,"teamUnitUpgradeList3"};
extern const StaticNameKey TheKey_teamUnitType4 = {0,"teamUnitType4"};
extern const StaticNameKey TheKey_teamUnitMinCount4 = {0,"teamUnitMinCount4"};
extern const StaticNameKey TheKey_teamUnitMaxCount4 = {0,"teamUnitMaxCount4"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel4 = {0,"teamUnitExperienceLevel4"};
extern const StaticNameKey TheKey_teamUnitUpgradeList4 = {0,"teamUnitUpgradeList4"};
extern const StaticNameKey TheKey_teamUnitType5 = {0,"teamUnitType5"};
extern const StaticNameKey TheKey_teamUnitMinCount5 = {0,"teamUnitMinCount5"};
extern const StaticNameKey TheKey_teamUnitMaxCount5 = {0,"teamUnitMaxCount5"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel5 = {0,"teamUnitExperienceLevel5"};
extern const StaticNameKey TheKey_teamUnitUpgradeList5 = {0,"teamUnitUpgradeList5"};
extern const StaticNameKey TheKey_teamUnitType6 = {0,"teamUnitType6"};
extern const StaticNameKey TheKey_teamUnitMinCount6 = {0,"teamUnitMinCount6"};
extern const StaticNameKey TheKey_teamUnitMaxCount6 = {0,"teamUnitMaxCount6"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel6 = {0,"teamUnitExperienceLevel6"};
extern const StaticNameKey TheKey_teamUnitUpgradeList6 = {0,"teamUnitUpgradeList6"};
extern const StaticNameKey TheKey_teamUnitType7 = {0,"teamUnitType7"};
extern const StaticNameKey TheKey_teamUnitMinCount7 = {0,"teamUnitMinCount7"};
extern const StaticNameKey TheKey_teamUnitMaxCount7 = {0,"teamUnitMaxCount7"};
extern const StaticNameKey TheKey_teamUnitExperienceLevel7 = {0,"teamUnitExperienceLevel7"};
extern const StaticNameKey TheKey_teamUnitUpgradeList7 = {0,"teamUnitUpgradeList7"};
extern const StaticNameKey TheKey_teamOnCreateScript = {0,"teamOnCreateScript"};
extern const StaticNameKey TheKey_teamOnIdleScript = {0,"teamOnIdleScript"};
extern const StaticNameKey TheKey_teamEventsList = {0,"teamEventsList"};
extern const StaticNameKey TheKey_teamInitialIdleSeconds = {0,"teamInitialIdleSeconds"};
extern const StaticNameKey TheKey_teamOnUnitDestroyedScript = {0,"teamOnUnitDestroyedScript"};
extern const StaticNameKey TheKey_teamOnDestroyedScript = {0,"teamOnDestroyedScript"};
extern const StaticNameKey TheKey_teamDestroyedThreshold = {0,"teamDestroyedThreshold"};
extern const StaticNameKey TheKey_teamEnemySightedScript = {0,"teamEnemySightedScript"};
extern const StaticNameKey TheKey_teamAllClearScript = {0,"teamAllClearScript"};
extern const StaticNameKey TheKey_teamAutoReinforce = {0,"teamAutoReinforce"};
extern const StaticNameKey TheKey_teamIsAIRecruitable = {0,"teamIsAIRecruitable"};
extern const StaticNameKey TheKey_teamIsBaseDefense = {0,"teamIsBaseDefense"};
extern const StaticNameKey TheKey_teamIsPerimeterDefense = {0,"teamIsPerimeterDefense"};
extern const StaticNameKey TheKey_teamAggressiveness = {0,"teamAggressiveness"};
extern const StaticNameKey TheKey_teamTransportsReturn = {0,"teamTransportsReturn"};
extern const StaticNameKey TheKey_teamAvoidThreats = {0,"teamAvoidThreats"};
extern const StaticNameKey TheKey_teamAttackCommonTarget = {0,"teamAttackCommonTarget"};
extern const StaticNameKey TheKey_teamMaxInstances = {0,"teamMaxInstances"};
extern const StaticNameKey TheKey_teamProductionCondition = {0,"teamProductionCondition"};
extern const StaticNameKey TheKey_teamProductionPriority = {0,"teamProductionPriority"};
extern const StaticNameKey TheKey_teamProductionPrioritySuccessIncrease = {0,"teamProductionPrioritySuccessIncrease"};
extern const StaticNameKey TheKey_teamProductionPriorityFailureDecrease = {0,"teamProductionPriorityFailureDecrease"};
extern const StaticNameKey TheKey_teamTransport = {0,"teamTransport"};
extern const StaticNameKey TheKey_teamReinforcementOrigin = {0,"teamReinforcementOrigin"};
extern const StaticNameKey TheKey_teamStartsFull = {0,"teamStartsFull"};
extern const StaticNameKey TheKey_teamTransportsExit = {0,"teamTransportsExit"};
extern const StaticNameKey TheKey_teamVeterancy = {0,"teamVeterancy"};
extern const StaticNameKey TheKey_teamExecutesActionsOnCreate = {0,"teamExecutesActionsOnCreate"};
extern const StaticNameKey TheKey_teamGenericScriptHook = {0,"teamGenericScriptHook"};
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
	min = d->getInt(TheKey_teamUnitMinCount1, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount1, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel1, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList1, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType1, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount2, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount2, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel2, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList2, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType2, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount3, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount3, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel3, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList3, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType3, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount4, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount4, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel4, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList4, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType4, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount5, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount5, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel5, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList5, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType5, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount6, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount6, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel6, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList6, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType6, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount7, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount7, &exists);
	experience = d->getInt(TheKey_teamUnitExperienceLevel7, &exists);
	upgradeList = d->getAsciiString(TheKey_teamUnitUpgradeList7, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType7, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].experienceLevel = experience;
		m_unitsInfo[m_numUnitsInfo].upgradeList = upgradeList;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	AsciiString waypoint = d->getAsciiString(TheKey_teamHome, &exists);
	m_homeLocation.x = m_homeLocation.y = 0;
	m_homeLocation.z = 0;
	m_hasHomeLocation = false;
	if (exists) {
		for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
			if (way->getName().compare(waypoint) == 0) {
				m_homeLocation = *way->getLocation();
				m_hasHomeLocation = true;
			}
		}
	}

	m_scriptOnCreate = d->getAsciiString(TheKey_teamOnCreateScript, &exists);
	m_teamEventsList = d->getAsciiString(TheKey_teamEventsList, &exists);
	m_isAIRecruitable	= d->getBool(TheKey_teamIsAIRecruitable, &exists);
	if (!exists) {
		m_isAIRecruitable = false;
	}
	m_isBaseDefense	= d->getBool(TheKey_teamIsBaseDefense, &exists);
	m_isPerimeterDefense	= d->getBool(TheKey_teamIsPerimeterDefense, &exists);
	m_automaticallyReinforce = d->getBool(TheKey_teamAutoReinforce, &exists);

	Int interact	= d->getInt(TheKey_teamAggressiveness, &exists);
	m_initialTeamAttitude = AI_NORMAL;
	if (exists) {
		m_initialTeamAttitude = (AttitudeType) interact;
	}

	m_transportsReturn	= d->getBool(TheKey_teamTransportsReturn, &exists);
	m_avoidThreats = d->getBool(TheKey_teamAvoidThreats, &exists);

	m_attackCommonTarget = d->getBool(TheKey_teamAttackCommonTarget, &exists);

	m_maxInstances = d->getInt(TheKey_teamMaxInstances, &exists);

	m_scriptOnIdle = d->getAsciiString(TheKey_teamOnIdleScript, &exists);
	m_initialIdleFrames = g_rva0058AD9FBase * d->getInt(TheKey_teamInitialIdleSeconds, &exists);
	m_scriptOnEnemySighted = d->getAsciiString(TheKey_teamEnemySightedScript, &exists);
	m_scriptOnAllClear = d->getAsciiString(TheKey_teamAllClearScript, &exists);
	m_scriptOnDestroyed = d->getAsciiString(TheKey_teamOnDestroyedScript, &exists);
	m_destroyedThreshold = d->getReal(TheKey_teamDestroyedThreshold, &exists);
	m_scriptOnUnitDestroyed = d->getAsciiString(TheKey_teamOnUnitDestroyedScript, &exists);

	m_productionPriority = d->getInt(TheKey_teamProductionPriority, &exists);
	m_productionPrioritySuccessIncrease = d->getInt(TheKey_teamProductionPrioritySuccessIncrease, &exists);
	m_productionPriorityFailureDecrease = d->getInt(TheKey_teamProductionPriorityFailureDecrease, &exists);

	// Production scripts stuff
	m_productionCondition = d->getAsciiString(TheKey_teamProductionCondition, &exists);
	m_executeActions = d->getBool(TheKey_teamExecutesActionsOnCreate, &exists);

	
	// Which scripts to attempt during run?
	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i) {
		AsciiString keyName;
		keyName.format("%s%d", TheNameKeyGenerator->keyToName(TheKey_teamGenericScriptHook).str(), i);			
		m_teamGenericScripts[i] = d->getAsciiString(TheNameKeyGenerator->nameToKey(keyName), &exists);
		if (!exists) {
			m_teamGenericScripts[i].clear();
		}
	}

	// reinforcement team info.
	m_transportUnitType = d->getAsciiString(TheKey_teamTransport, &exists);
	m_transportsExit = d->getBool(TheKey_teamTransportsExit, &exists);
	m_teamStartsFull = d->getBool(TheKey_teamStartsFull, &exists);
	m_startReinforceWaypoint = d->getAsciiString(TheKey_teamReinforcementOrigin, &exists);
	m_veterancy = (VeterancyLevel)d->getInt(TheKey_teamVeterancy, &exists);
 int teamType=d->getInt(TheKey_teamType,&exists);
 if(exists) { if(teamType<0) m_teamType=0; else m_teamType=teamType; }
}

