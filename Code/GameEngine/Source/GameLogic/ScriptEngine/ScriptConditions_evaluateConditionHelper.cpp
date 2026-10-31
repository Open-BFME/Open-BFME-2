// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ScriptConditions::evaluateConditionHelper, retail 0x003EA9AF, 7185 bytes:
// the script condition dispatcher (WorldBuilder's ScriptConditions.cpp,
// assert line 5418 "Unknown ScriptCondition type %d"; Zero Hour's
// ScriptConditions::evaluateCondition made BFME2). The jump table at
// 0x007EC5C0 maps condition type - 5 (0xC5 entries); unmapped types return
// false. Case bodies fetch parameters with the inlined Condition::getParameter
// (null past the parameter count) and call the evaluators at their rowed
// addresses; where several callers share a push tail the compiler
// cross-jumps it again.
#include "ascii_string.h"

class ScriptConditions;
class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

class Condition
{
public:
	bool isInverted() const { return m_inverted; }
	Parameter *getParameter(int ndx) const { if (ndx >= 0 && ndx < m_numParms) return m_parms[ndx]; return 0; }
	int getCustomData() const { return m_customData; }
	void setCustomData(int val) { m_customData = val; }
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomFrame(unsigned int frame) { m_customFrame = frame; }
	int getType() const { return m_type; }
	int getNumParameters() const { return m_numParms; }
	char m_pad00[0x4];
private:
	int m_type; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[13]; // +0x0C
	char m_pad40[0x4];
	int m_customData; // +0x44
	unsigned int m_customFrame; // +0x48
	char m_pad4C[0x1];
	bool m_inverted; // +0x4D
	char m_pad4E[0x2];
};

struct Cond003E5D95;
struct CondA003E514F;
struct CondA003E52EB;
struct CondA003E53C8;
struct CondA003E5F73;
struct CondB003E514F;
struct CondB003E52EB;
struct CondB003E53C8;
struct CondB003E5F73;
struct CondC003E5F73;

class View
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual bool isCameraMovementFinished();
};
extern View *TheTacticalView;

struct UnknownE03138
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual bool isLocalAlliedVictory();
	virtual bool isLocalAlliedDefeat();
};
class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;

class Rva0022AD10Subsystem
{
public:
	bool m_flag34() const { return m_f; }
private:
	unsigned char m_pad[0x34];
	bool m_f;
};
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern int g_Va00E04450;
bool Rva0056815AAny(void);

bool __stdcall Rva003E41CBGet(Parameter *);
int __cdecl evaluateMultiplayerPlayerDefeat(void);
bool __stdcall Rva003E4B83Get(Parameter *);
int __cdecl Rva003E4C77Get(void);
bool __stdcall Rva003E4E6AGet(Parameter *);
bool __stdcall Rva003E4EA5Get(Parameter *);
bool __stdcall Rva003E4ED5Get(Parameter *);
bool __stdcall Rva003E4F05Get(Parameter *);
bool __stdcall Rva003E4F3BGet(Parameter *);
bool __stdcall Rva003E4F6BGet(void);
bool __stdcall Rva003E537DCheck(Parameter *);
bool __stdcall Rva003E7FD5Get(Parameter *);
bool __stdcall Rva003E8FEE(Parameter *);
bool __stdcall Rva003E9029(const AsciiString *);
int __cdecl Rva0043C99AGet(void);
int __stdcall bfmeGo939D(char);

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateConditionHelper(Condition *condition)
{
	switch (condition->getType()) {
	case 5:
		return this->evaluateAllDestroyed(condition->getParameter(0));
	case 6:
		return this->evaluateAllBuildFacilitiesDestroyed(condition->getParameter(0));
	case 7:
		return this->evaluateTeamInsideAreaPartially(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 13:
		return this->evaluateNamedInsideArea(condition->getParameter(0), condition->getParameter(1));
	case 8:
		return this->evaluateIsDestroyed(condition->getParameter(0));
	case 170:
		return this->evaluateTeamCountCompare(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 172:
		return this->evaluateNamedUnitRankLevel(condition->getParameter(0), condition->getParameter(1));
	case 15:
		return this->evaluateNamedUnitDestroyed(condition->getParameter(0));
	case 56:
		return this->evaluateNamedUnitDying(condition->getParameter(0));
	case 57:
		return this->evaluateNamedUnitTotallyDead(condition->getParameter(0));
	case 16:
		return this->evaluateNamedUnitExists(condition->getParameter(0));
	case 10:
		return this->evaluateHasUnits(condition->getParameter(0));
	case 9:
		return TheTacticalView->isCameraMovementFinished();
	case 189:
		return Rva003E4ED5Get(condition->getParameter(0));
	case 190:
		return Rva003E4F05Get(condition->getParameter(0));
	case 191:
		return Rva003E4F3BGet(condition->getParameter(0));
	case 192:
		return Rva003E4F6BGet();
	case 11:
		return this->evaluateTeamStateIs(condition->getParameter(0), condition->getParameter(1));
	case 12:
		return this->evaluateTeamStateIsNot(condition->getParameter(0), condition->getParameter(1));
	case 14:
		return this->evaluateNamedOutsideArea(condition->getParameter(0), condition->getParameter(1));
	case 17:
		return this->evaluateTeamInsideAreaEntirely(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 18:
		return this->evaluateTeamOutsideAreaEntirely(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 19:
		return this->evaluateNamedAttackedByType(condition->getParameter(0), condition->getParameter(1));
	case 20:
		return this->evaluateTeamAttackedByType(condition->getParameter(0), condition->getParameter(1));
	case 21:
		return this->evaluateNamedAttackedByPlayer(condition->getParameter(0), condition->getParameter(1));
	case 22:
		return this->evaluateTeamAttackedByPlayer(condition->getParameter(0), condition->getParameter(1));
	case 23:
		return this->evaluateBuiltByPlayer(condition, condition->getParameter(0), condition->getParameter(1));
	case 24:
		return this->evaluateNamedCreated(condition->getParameter(0));
	case 25:
		return (this->*(bool (ScriptConditions::*)(Parameter *))&ScriptConditions::evaluateTeamCreated)(condition->getParameter(0));
	case 26:
		return this->evaluatePlayerHasCredits(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 54:
		return this->evaluateBridgeRepaired(condition->getParameter(0));
	case 55:
		return this->evaluateBridgeBroken(condition->getParameter(0));
	case 27:
		return this->evaluateNamedDiscovered(condition->getParameter(0), condition->getParameter(1));
	case 28:
		return this->evaluateTeamDiscovered(condition->getParameter(0), condition->getParameter(1));
	case 51:
		return this->evaluateBuildingEntered(condition->getParameter(0), condition->getParameter(1));
	case 52:
		if (condition->getNumParameters() < 3)
			return false;
		return this->evaluateEnemySighted(*(const AsciiString *)condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 133:
		return this->rva003E6835(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 77:
		return this->evaluateTypeSighted(*(const AsciiString *)condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 78:
		return this->evaluateIsBuildingEmpty(condition->getParameter(0));
	case 30:
		return this->evaluateNamedOwnedByPlayer(condition->getParameter(0), condition->getParameter(1));
	case 31:
		return this->evaluateTeamOwnedByPlayer(condition->getParameter(0), condition->getParameter(1));
	case 32:
		return this->evaluatePlayerHasNOrFewerBuildings(condition->getParameter(1), condition->getParameter(0));
	case 79:
		return this->evaluatePlayerHasNOrFewerFactionBuildings(condition->getParameter(1), condition->getParameter(0));
	case 131:
		return this->evaluatePlayerHasNOrFewerBases(condition->getParameter(1), condition->getParameter(0));
	case 33:
		return this->evaluatePlayerHasPower(condition->getParameter(0));
	case 47:
		return !this->evaluatePlayerHasPower(condition->getParameter(0));
	case 34:
		return this->evaluateNamedReachedWaypointsEnd(condition->getParameter(0), condition->getParameter(1));
	case 35:
		return this->evaluateTeamReachedWaypointsEnd(condition->getParameter(0), condition->getParameter(1));
	case 200:
		return this->rva003E6BC5(condition, condition->getParameter(0));
	case 37:
		return this->evaluateNamedSelected(condition, condition->getParameter(0));
	case 38:
		return this->evaluateNamedEnteredArea(condition->getParameter(0), condition->getParameter(1));
	case 39:
		return this->evaluateNamedExitedArea(condition->getParameter(0), condition->getParameter(1));
	case 40:
		return this->evaluateTeamEnteredAreaEntirely(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 121:
		return this->evaluateNamedBaseUnpackableForPlayer(condition->getParameter(0), condition->getParameter(1));
	case 41:
		return this->evaluateTeamEnteredAreaPartially(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 42:
		return this->evaluateTeamExitedAreaEntirely(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 43:
		return this->evaluateTeamExitedAreaPartially(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 147:
		return this->rva003E51D9(condition->getParameter(0), condition->getParameter(1));
	case 148:
		return this->rva003E6ED0(condition->getParameter(0), (const AsciiString *)condition->getParameter(1), 0, true, false);
	case 149:
		return this->rva003E6ED0(condition->getParameter(0), (const AsciiString *)condition->getParameter(1), 0, true, true);
	case 150:
		return this->rva003E6ED0(condition->getParameter(0), (const AsciiString *)condition->getParameter(1), 0, false, false);
	case 151:
		return this->rva003E6ED0(condition->getParameter(0), (const AsciiString *)condition->getParameter(1), 0, false, true);
	case 152:
		return this->rva003E6ED0(condition->getParameter(0), 0, condition->getParameter(1), true, false);
	case 153:
		return this->rva003E6ED0(condition->getParameter(0), 0, condition->getParameter(1), true, true);
	case 154:
		return this->rva003E6ED0(condition->getParameter(0), 0, condition->getParameter(1), false, false);
	case 155:
		return this->rva003E6ED0(condition->getParameter(0), 0, condition->getParameter(1), false, true);
	case 156:
		return this->rva003E59B0(condition->getParameter(0), condition->getParameter(1), 0, true);
	case 157:
		return this->rva003E59B0(condition->getParameter(0), condition->getParameter(1), 0, false);
	case 158:
		return this->rva003E59B0(condition->getParameter(0), 0, condition->getParameter(1), true);
	case 159:
		return this->rva003E59B0(condition->getParameter(0), 0, condition->getParameter(1), false);
	case 138:
		return this->rva003E5CB1(condition->getParameter(0), condition->getParameter(1));
	case 141:
		return this->rva003E83AF(condition->getParameter(0), condition->getParameter(1));
	case 44:
		return ((UnknownE03138 *)TheVictoryConditions)->isLocalAlliedVictory();
	case 45:
		return ((UnknownE03138 *)TheVictoryConditions)->isLocalAlliedDefeat();
	case 46:
		return ((bool (__cdecl *)(void))evaluateMultiplayerPlayerDefeat)();
	case 36:
		return Rva003E41CBGet(condition->getParameter(0));
	case 48:
		return this->evaluateVideoHasCompleted(condition->getParameter(0));
	case 49:
		return this->evaluateSpeechHasCompleted(condition->getParameter(0));
	case 50:
		return this->evaluateAudioHasCompleted(condition->getParameter(0));
	case 53:
		return this->evaluateUnitHealth(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 61:
		return this->evaluatePlayerSpecialPowerFromUnitTriggered(condition->getParameter(0), condition->getParameter(1), 0);
	case 64:
		return this->evaluatePlayerSpecialPowerFromUnitTriggered(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 63:
		return this->evaluatePlayerSpecialPowerFromUnitMidway(condition->getParameter(0), condition->getParameter(1), 0);
	case 66:
		return this->evaluatePlayerSpecialPowerFromUnitMidway(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 62:
		return this->evaluatePlayerSpecialPowerFromUnitComplete(condition->getParameter(0), condition->getParameter(1), 0);
	case 65:
		return this->evaluatePlayerSpecialPowerFromUnitComplete(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 100:
		return this->evaluateScienceAcquired(condition->getParameter(0), condition->getParameter(1));
	case 102:
		return this->evaluateCanPurchaseScience(condition->getParameter(0), condition->getParameter(1));
	case 101:
		return this->evaluateSciencePurchasePoints(condition->getParameter(0), condition->getParameter(1));
	case 173:
		return this->rva003E4519(condition->getParameter(0));
	case 69:
		return this->evaluateUpgradeFromUnitComplete(condition->getParameter(0), condition->getParameter(1), 0);
	case 70:
		return this->evaluateUpgradeFromUnitComplete(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 58:
		return this->evaluatePlayerUnitCondition(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 71:
		return this->evaluatePlayerDestroyedNOrMoreBuildings(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 74:
		{
		Parameter *parameter;
		if (condition->getNumParameters() < 5)
			return false;
		parameter = condition->getParameter(4);
		return this->evaluatePlayerHasUnitTypeInArea(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3), parameter, 0, false);
		}
	case 188:
		{
		Parameter *parameter;
		if (condition->getNumParameters() < 5)
			return false;
		parameter = condition->getParameter(4);
		return this->evaluatePlayerHasUnitTypeInArea(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3), parameter, 0, true);
		}
	case 110:
		{
		Parameter *parameter;
		Parameter *p5;
		if (condition->getNumParameters() < 6)
			return false;
		p5 = condition->getParameter(5);
		parameter = condition->getParameter(4);
		return this->evaluatePlayerHasUnitTypeInArea(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3), parameter, p5, false);
		}
	case 194:
		return TheFormationAssistant->m_flag34();
	case 75:
		{
		Parameter *parameter;
		if (condition->getNumParameters() < 5)
			return false;
		parameter = condition->getParameter(4);
		return this->evaluatePlayerHasUnitKindInArea(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3), parameter);
		}
	case 160:
		return this->evaluatePlayerHasNumberObjectsWithModelCondition(condition->getParameter(0), (CondA003E5F73 *)condition->getParameter(1), (CondB003E5F73 *)condition->getParameter(2), (CondC003E5F73 *)condition->getParameter(3));
	case 161:
		return this->evaluatePlayerHasNumberUnitsDistanceFromObject(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3), condition->getParameter(4));
	case 76:
		return this->evaluateUnitHasEmptied(condition->getParameter(0));
	case 83:
		return this->evaluatePlayerHasComparisonPercentPower(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 84:
		return this->evaluatePlayerHasComparisonValueExcessPower(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 85:
		return this->evaluateSkirmishSpecialPowerIsReady(condition->getParameter(0), condition->getParameter(1));
	case 171:
		return this->evaluateSkirmishCanFireSpecialPowerOnTeam(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 80:
		return this->evaluateUnitHasObjectStatus(condition->getParameter(0), condition->getParameter(1));
	case 193:
		return this->rva003E5267(condition->getParameter(0), condition->getParameter(1));
	case 81:
		return this->evaluateTeamHasObjectStatus(condition->getParameter(0), condition->getParameter(1), true);
	case 82:
		return this->evaluateTeamHasObjectStatus(condition->getParameter(0), condition->getParameter(1), false);
	case 86:
		return this->evaluateSkirmishValueInArea(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 87:
		return this->evaluateSkirmishPlayerIsFaction(condition->getParameter(0), condition->getParameter(1));
	case 88:
		return this->evaluateSkirmishSuppliesWithinDistancePerimeter(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 89:
		return evaluateSkirmishCommandButtonIsReady(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), true);
	case 90:
		return evaluateSkirmishCommandButtonIsReady(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), false);
	case 91:
		return this->evaluateSkirmishUnownedFactionUnitComparison(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 92:
		return this->evaluateSkirmishPlayerHasPrereqsToBuild(condition->getParameter(0), condition->getParameter(1));
	case 93:
		return this->evaluateSkirmishPlayerHasComparisonGarrisoned(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 94:
		return this->evaluateSkirmishPlayerHasComparisonCapturedUnits(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 95:
		return this->evaluateSkirmishNamedAreaExists(condition->getParameter(0), condition->getParameter(1));
	case 96:
		return this->evaluateSkirmishPlayerHasUnitsInArea(condition, condition->getParameter(0), condition->getParameter(1));
	case 97:
		return this->evaluateSkirmishPlayerHasBeenAttackedByPlayer(condition->getParameter(0), condition->getParameter(1));
	case 98:
		return this->evaluateSkirmishPlayerIsOutsideArea(condition, condition->getParameter(0), condition->getParameter(1));
	case 99:
		return this->evaluateSkirmishPlayerHasDiscoveredPlayer(condition->getParameter(0), condition->getParameter(1));
	case 103:
		return this->evaluateMusicHasCompleted(condition->getParameter(0), condition->getParameter(1));
	case 105:
		return this->evaluateSkirmishSupplySourceSafe(condition, condition->getParameter(0), condition->getParameter(1));
	case 106:
		return this->evaluateSkirmishSupplySourceAttacked(condition->getParameter(0));
	case 107:
		return this->evaluateSkirmishStartPosition(condition->getParameter(0), condition->getParameter(1));
	case 108:
		return condition->getParameter(1)->getInt() <= 0;
	case 109:
		return Rva003E4B83Get(condition->getParameter(0));
	case 104:
		return this->evaluatePlayerLostObjectType(condition->getParameter(0), condition->getParameter(1));
	case 120:
		return Rva003E4EA5Get(condition->getParameter(0));
	case 132:
		return Rva003E7FD5Get(condition->getParameter(0));
	case 111:
		return this->evaluateCounterCounter(condition);
	case 112:
		return this->evaluateCounterSeconds(condition);
	case 113:
		return this->evaluateDistanceBetweenObjects(condition);
	case 114:
		return this->evaluateDistanceBetweenTeams(condition);
	case 115:
		return this->rva003E4D93(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 116:
		return this->evaluateTeamCachedFloatCompare(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 117:
		return Rva003E4E6AGet(condition->getParameter(0));
	case 118:
		return this->rva003E7F3A(condition->getParameter(0), condition->getParameter(1));
	case 123:
		return this->evaluateTeamIsLedByUnit(condition->getParameter(0), condition->getParameter(1));
	case 124:
		return this->evaluatePlayerCompareLightPoints(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 125:
		return this->evaluateHasCommandPointsToBuildTeam(condition->getParameter(0), condition->getParameter(1));
	case 126:
		return this->evaluateHasCommandPointsToBuildUnit(condition->getParameter(0), condition->getParameter(1));
	case 127:
		return this->evaluateCanBuildAtBase(condition->getParameter(0), condition->getParameter(1));
	case 169:
		return this->evaluateCanBuildObjectTypeAtBase(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 128:
		return this->evaluatePlayerHasKilledKindOfUnits(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 129:
		return this->evaluatePlayerHasKilledTypeUnits(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 130:
		return this->evaluateNamedDestroyedByType(condition->getParameter(0), condition->getParameter(1));
	case 134:
		return this->rva003E63CD(condition, condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 135:
		return this->rva003E3EC3(condition->getParameter(0));
	case 142:
		return ((bool (__cdecl *)(void))Rva003E4C77Get)();
	case 136:
		return this->evaluateNamedCanPathToWaypoint(condition->getParameter(0), condition->getParameter(1));
	case 137:
		return this->rva003E5105(condition->getParameter(0), condition->getParameter(1));
	case 139:
		return this->evaluateTeamCanPathToWaypoint(condition->getParameter(0), condition->getParameter(1));
	case 140:
		return this->evaluateTeamCanPathToNamed(condition->getParameter(0), condition->getParameter(1));
	case 143:
		return this->rva003E859E(condition->getParameter(0), condition->getParameter(1));
	case 144:
		return this->rva003E514F(condition->getParameter(0), (CondA003E514F *)condition->getParameter(1), (CondB003E514F *)condition->getParameter(2));
	case 145:
		return this->rva003E52EB(condition->getParameter(0), (CondA003E52EB *)condition->getParameter(1), (CondB003E52EB *)condition->getParameter(2));
	case 146:
		return this->rva003E8E23(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 162:
		return Rva003E537DCheck(condition->getParameter(0));
	case 163:
		return this->rva003EA12A(condition->getParameter(0));
	case 164:
		return this->rva003EA228(condition->getParameter(0), true);
	case 165:
		return this->rva003EA228(condition->getParameter(0), false);
	case 166:
		return ((bool (__stdcall *)(char))bfmeGo939D)(condition->getParameter(0)->getInt() != 0);
	case 201:
		return this->evaluateGameModeActive(condition->getParameter(0));
	case 168:
		return this->evaluateNumPlayersInGame((CondA003E53C8 *)condition->getParameter(0), (CondB003E53C8 *)condition->getParameter(1));
	case 174:
		return this->rva003E8D01(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 175:
		return (this->*(bool (ScriptConditions::*)(Parameter *, Cond003E5D95 *))&ScriptConditions::rva003E5D95)(condition->getParameter(0), (Cond003E5D95 *)condition->getParameter(1));
	case 176:
		return this->rva003E85E0(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 177:
		return this->rva003E86A3(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 178:
		return this->rva003E8785(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2));
	case 179:
		return this->rva003E8863(condition->getParameter(0), condition->getParameter(1), condition->getParameter(2), condition->getParameter(3));
	case 180:
		return this->evaluateUnitHasToggledWeapon(condition->getParameter(0), condition->getParameter(1));
	case 182:
		return this->rva003E8C24(condition->getParameter(0), condition->getParameter(1));
	case 181:
		return this->evaluateAnyUnitsUsingBloodthirsty(condition->getParameter(0));
	case 183:
		return this->rva003E8B47(condition->getParameter(0), condition->getParameter(1));
	case 184:
		return Rva003E8FEE(condition->getParameter(0));
	case 185:
		return Rva003E9029(&condition->getParameter(0)->getString());
	case 186:
		return this->evaluateHasEvaEventPlayedInLastNSeconds(condition->getParameter(0)->getString(), condition->getParameter(1)->getReal());
	case 187:
		return this->evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(condition->getParameter(0), condition->getParameter(1)->getReal(), &condition->getParameter(2)->getString(), condition->getParameter(3)->getInt(), condition->getParameter(4)->getInt());
	case 195:
		return this->evaluateHasDelayedCarryoverUnitOfType(condition->getParameter(0)->getString(), condition->getParameter(1));
	case 196:
		return Rva0056815AAny();
	case 197:
		return ((bool (__cdecl *)(void))Rva0043C99AGet)();
	case 198:
		return g_Va00E04450 != 0;
	case 199:
		return this->evaluatePlayerIsInPlanningMode(condition->getParameter(0));
	default:
		return false;
	}
}
