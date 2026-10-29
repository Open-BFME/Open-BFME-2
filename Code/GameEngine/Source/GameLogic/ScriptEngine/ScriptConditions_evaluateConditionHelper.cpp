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

class Parameter
{
public:
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	float getReal() const { return m_real; }
	const AsciiString *getString() const { return &m_string; }

private:
	int m_pad[2];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	int getType() const { return m_type; }
	int getNumParameters() const { return m_numParms; }
	Parameter *getParameter(int ix) const
	{
		return (ix >= 0 && ix < m_numParms) ? m_parms[ix] : 0;
	}

private:
	int m_pad0;
	int m_type;
	int m_numParms;
	Parameter *m_parms[13];
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

class ScriptConditions
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
	virtual bool evaluateCondition(Condition *condition);
protected:
	virtual bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, bool);
public:
	bool evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(Parameter *, float, const AsciiString *, int, int);
	bool evaluateEnemySighted(const AsciiString &, Parameter *, Parameter *);
	bool rva003E5CB1(Parameter *, Parameter *);
	bool rva003E6835(Parameter *, Parameter *, Parameter *);
	bool rva003E6ED0(Parameter *, const AsciiString *, Parameter *, bool, bool);
	bool rva003E83AF(Parameter *, Parameter *);
	bool evaluateTypeSighted(const AsciiString &, Parameter *, Parameter *);
	bool evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *, Parameter *, Parameter *, Parameter *);

protected:
	bool evaluateConditionHelper(Condition *c);
	bool evaluatePlayerHasUnitKindInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasComparisonPercentPower(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasComparisonValueExcessPower(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerCompareLightPoints(Parameter *, Parameter *, Parameter *);
	bool evaluateCanBuildObjectTypeAtBase(Parameter *, Parameter *, Parameter *);
	bool evaluateNamedCanPathToWaypoint(Parameter *, Parameter *);
	bool rva003E5105(Parameter *, Parameter *);
	bool rva003E514F(Parameter *, CondA003E514F *, CondB003E514F *);
	bool rva003E52EB(Parameter *, CondA003E52EB *, CondB003E52EB *);
	unsigned char rva003E5D95(Parameter *, Cond003E5D95 *);
	bool evaluateTeamCachedFloatCompare(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E7F3A(Parameter *, Parameter *);
	bool evaluateTeamIsLedByUnit(Parameter *, Parameter *);
	bool evaluateHasCommandPointsToBuildTeam(Parameter *, Parameter *);
	bool evaluateTeamCanPathToWaypoint(Parameter *, Parameter *);
	bool evaluateTeamCanPathToNamed(Parameter *, Parameter *);
	bool evaluateAllBuildFacilitiesDestroyed(Parameter *);
	bool evaluateAllDestroyed(Parameter *);
	bool evaluateAudioHasCompleted(Parameter *);
	bool evaluateBridgeBroken(Parameter *);
	bool evaluateBridgeRepaired(Parameter *);
	bool evaluateBuildingEntered(Parameter *, Parameter *);
	bool evaluateBuiltByPlayer(Condition *, Parameter *, Parameter *);
	bool evaluateCanBuildAtBase(Parameter *, Parameter *);
	bool evaluateCanPurchaseScience(Parameter *, Parameter *);
	bool evaluateCounterCounter(Condition *);
	bool evaluateCounterSeconds(Condition *);
	bool evaluateDistanceBetweenObjects(Condition *);
	bool evaluateDistanceBetweenTeams(Condition *);
	bool evaluateGameModeActive(Parameter *);
	bool evaluateHasCommandPointsToBuildUnit(Parameter *, Parameter *);
	bool evaluateHasDelayedCarryoverUnitOfType(const AsciiString &, Parameter *);
	bool evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &, float);
	bool evaluateHasUnits(Parameter *);
	bool evaluateIsBuildingEmpty(Parameter *);
	bool evaluateIsDestroyed(Parameter *);
	bool evaluateMusicHasCompleted(Parameter *, Parameter *);
	bool evaluateNamedAttackedByPlayer(Parameter *, Parameter *);
	bool evaluateNamedAttackedByType(Parameter *, Parameter *);
	bool evaluateNamedCreated(Parameter *);
	bool evaluateNamedDestroyedByType(Parameter *, Parameter *);
	bool evaluateNamedEnteredArea(Parameter *, Parameter *);
	bool evaluateNamedExitedArea(Parameter *, Parameter *);
	bool evaluateNamedInsideArea(Parameter *, Parameter *);
	bool evaluateNamedOutsideArea(Parameter *, Parameter *);
	bool evaluateNamedOwnedByPlayer(Parameter *, Parameter *);
	bool evaluateNamedReachedWaypointsEnd(Parameter *, Parameter *);
	bool evaluateNamedSelected(Condition *, Parameter *);
	bool evaluateNamedUnitDestroyed(Parameter *);
	bool evaluateNamedUnitDying(Parameter *);
	bool evaluateNamedUnitExists(Parameter *);
	bool evaluateNamedUnitRankLevel(Parameter *, Parameter *);
	bool evaluateNamedUnitTotallyDead(Parameter *);
	bool evaluateNumPlayersInGame(CondA003E53C8 *, CondB003E53C8 *);
	bool evaluatePlayerDestroyedNOrMoreBuildings(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasKilledKindOfUnits(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasKilledTypeUnits(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasNOrFewerBuildings(Parameter *, Parameter *);
	bool evaluatePlayerHasNumberObjectsWithModelCondition(Parameter *, CondA003E5F73 *, CondB003E5F73 *, CondC003E5F73 *);
	bool evaluatePlayerHasNumberUnitsDistanceFromObject(Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasPower(Parameter *);
	bool evaluatePlayerIsInPlanningMode(Parameter *);
	bool evaluatePlayerLostObjectType(Parameter *, Parameter *);
	bool evaluatePlayerSpecialPowerFromUnitComplete(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerSpecialPowerFromUnitMidway(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerSpecialPowerFromUnitTriggered(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerUnitCondition(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluateScienceAcquired(Parameter *, Parameter *);
	bool evaluateSciencePurchasePoints(Parameter *, Parameter *);
	bool evaluateSkirmishNamedAreaExists(Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *, Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *, Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasPrereqsToBuild(Parameter *, Parameter *);
	bool evaluateSkirmishPlayerIsFaction(Parameter *, Parameter *);
	bool evaluateSkirmishPlayerIsOutsideArea(Condition *, Parameter *, Parameter *);
	bool evaluateSkirmishStartPosition(Parameter *, Parameter *);
	bool evaluateSkirmishUnownedFactionUnitComparison(Parameter *, Parameter *, Parameter *);
	bool evaluateSpeechHasCompleted(Parameter *);
	bool evaluateTeamAttackedByPlayer(Parameter *, Parameter *);
	bool evaluateTeamAttackedByType(Parameter *, Parameter *);
	bool evaluateTeamCountCompare(Parameter *, Parameter *, Parameter *);
	unsigned char evaluateTeamCreated(Parameter *);
	bool evaluateTeamEnteredAreaEntirely(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamEnteredAreaPartially(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamExitedAreaEntirely(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamExitedAreaPartially(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamHasObjectStatus(Parameter *, Parameter *, bool);
	bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamOutsideAreaEntirely(Parameter *, Parameter *, Parameter *);
	bool evaluateTeamOwnedByPlayer(Parameter *, Parameter *);
	bool evaluateTeamReachedWaypointsEnd(Parameter *, Parameter *);
	bool evaluateTeamStateIs(Parameter *, Parameter *);
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);
	bool evaluateUnitHasEmptied(Parameter *);
	bool evaluateUnitHasObjectStatus(Parameter *, Parameter *);
	bool evaluateUnitHealth(Parameter *, Parameter *, Parameter *);
	bool evaluateUpgradeFromUnitComplete(Parameter *, Parameter *, Parameter *);
	bool evaluateVideoHasCompleted(Parameter *);
	bool rva003E3EC3(Parameter *);
	bool rva003E4519(Parameter *);
	bool evaluateSkirmishSupplySourceSafe(Condition *, Parameter *, Parameter *);
	bool evaluateSkirmishSupplySourceAttacked(Parameter *);
	bool rva003E4D93(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E51D9(Parameter *, Parameter *);
	bool rva003E5267(Parameter *, Parameter *);
	bool evaluatePlayerHasNOrFewerFactionBuildings(Parameter *, Parameter *);
	bool evaluatePlayerHasNOrFewerBases(Parameter *, Parameter *);
	bool evaluatePlayerHasUnitTypeInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, bool);
	bool rva003E63CD(Condition *, Parameter *, Parameter *, Parameter *);
	bool evaluateNamedDiscovered(Parameter *, Parameter *);
	bool evaluateTeamDiscovered(Parameter *, Parameter *);
	bool rva003E6BC5(Condition *, Parameter *);
	bool rva003E859E(Parameter *, Parameter *);
	bool rva003E85E0(Parameter *, Parameter *, Parameter *);
	bool evaluateAnyUnitsUsingBloodthirsty(Parameter *);
	bool rva003E8D01(Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerHasCredits(Parameter *, Parameter *, Parameter *);
	bool evaluateSkirmishSpecialPowerIsReady(Parameter *, Parameter *);
	bool evaluateSkirmishValueInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluateSkirmishPlayerHasUnitsInArea(Condition *, Parameter *, Parameter *);
	bool evaluateNamedBaseUnpackableForPlayer(Parameter *, Parameter *);
	bool rva003E8E23(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E59B0(Parameter *, Parameter *, Parameter *, bool);
	bool rva003EA12A(Parameter *);
	bool rva003EA228(Parameter *, bool);
	bool evaluateSkirmishCanFireSpecialPowerOnTeam(Parameter *, Parameter *, Parameter *);
	bool rva003E86A3(Parameter *, Parameter *, Parameter *);
	bool rva003E8785(Parameter *, Parameter *, Parameter *);
	bool rva003E8863(Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluateUnitHasToggledWeapon(Parameter *, Parameter *);
	bool rva003E8C24(Parameter *, Parameter *);
	bool rva003E8B47(Parameter *, Parameter *);
};

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
		return Rva003E9029(condition->getParameter(0)->getString());
	case 186:
		return this->evaluateHasEvaEventPlayedInLastNSeconds(*condition->getParameter(0)->getString(), condition->getParameter(1)->getReal());
	case 187:
		return this->evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(condition->getParameter(0), condition->getParameter(1)->getReal(), condition->getParameter(2)->getString(), condition->getParameter(3)->getInt(), condition->getParameter(4)->getInt());
	case 195:
		return this->evaluateHasDelayedCarryoverUnitOfType(*condition->getParameter(0)->getString(), condition->getParameter(1));
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
