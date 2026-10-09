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
	int getInt() const { return m_int; }
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
extern UnknownE03138 *g_00E03138;

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
bool Rva0056815A(void);

bool __stdcall Rva003E41CBGet(Parameter *);
int __cdecl Rva003E468FCheck(void);
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
	virtual void slot14();
	virtual bool slot15(Parameter *, Parameter *, Parameter *, bool);
	bool evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(Parameter *, float, const AsciiString *, int, int);
	bool rva003E56C5(const AsciiString &, Parameter *, Parameter *);
	bool rva003E5CB1(Parameter *, Parameter *);
	bool rva003E6835(Parameter *, Parameter *, Parameter *);
	bool rva003E6ED0(Parameter *, const AsciiString *, Parameter *, bool, bool);
	bool rva003E83AF(Parameter *, Parameter *);
	bool rva003EA3AB(const AsciiString &, Parameter *, Parameter *);
	bool rva003EA566(Parameter *, Parameter *, Parameter *, Parameter *);

protected:
	bool evaluateConditionHelper(Condition *c);
	bool rva003E64A6(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E46B4(Parameter *, Parameter *, Parameter *);
	bool rva003E477F(Parameter *, Parameter *, Parameter *);
	bool rva003E4F79(Parameter *, Parameter *, Parameter *);
	bool rva003E5017(Parameter *, Parameter *, Parameter *);
	bool rva003E50B4(Parameter *, Parameter *);
	bool rva003E5105(Parameter *, Parameter *);
	bool rva003E514F(Parameter *, CondA003E514F *, CondB003E514F *);
	bool rva003E52EB(Parameter *, CondA003E52EB *, CondB003E52EB *);
	unsigned char rva003E5D95(Parameter *, Cond003E5D95 *);
	bool rva003E7E54(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E7F3A(Parameter *, Parameter *);
	bool rva003E803D(Parameter *, Parameter *);
	bool rva003E80DA(Parameter *, Parameter *);
	bool rva003E84C5(Parameter *, Parameter *);
	bool rva003E8535(Parameter *, Parameter *);
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
	bool rva003E4A63(Condition *, Parameter *, Parameter *);
	bool rva003E4AE4(Parameter *);
	bool rva003E4D93(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E51D9(Parameter *, Parameter *);
	bool rva003E5267(Parameter *, Parameter *);
	bool rva003E586B(Parameter *, Parameter *);
	bool rva003E58F0(Parameter *, Parameter *);
	bool rva003E61A4(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, bool);
	bool rva003E63CD(Condition *, Parameter *, Parameter *, Parameter *);
	bool rva003E6A2B(Parameter *, Parameter *);
	bool rva003E6AA9(Parameter *, Parameter *);
	bool rva003E6BC5(Condition *, Parameter *);
	bool rva003E859E(Parameter *, Parameter *);
	bool rva003E85E0(Parameter *, Parameter *, Parameter *);
	bool rva003E8AA9(Parameter *);
	bool rva003E8D01(Parameter *, Parameter *, Parameter *);
	bool rva003E3F59(Parameter *, Parameter *, Parameter *);
	bool rva003E9062(Parameter *, Parameter *);
	bool rva003E719C(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E782D(Condition *, Parameter *, Parameter *);
	bool rva003E4565(Parameter *, Parameter *);
	bool rva003E8E23(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E59B0(Parameter *, Parameter *, Parameter *, bool);
	bool rva003EA12A(Parameter *);
	bool rva003EA228(Parameter *, bool);
	bool rva003E91F6(Parameter *, Parameter *, Parameter *);
	bool rva003E86A3(Parameter *, Parameter *, Parameter *);
	bool rva003E8785(Parameter *, Parameter *, Parameter *);
	bool rva003E8863(Parameter *, Parameter *, Parameter *, Parameter *);
	bool rva003E89A9(Parameter *, Parameter *);
	bool rva003E8C24(Parameter *, Parameter *);
	bool rva003E8B47(Parameter *, Parameter *);
};

bool ScriptConditions::evaluateConditionHelper(Condition *c)
{
	switch (c->getType()) {
	case 5:
		return this->evaluateAllDestroyed(c->getParameter(0));
	case 6:
		return this->evaluateAllBuildFacilitiesDestroyed(c->getParameter(0));
	case 7:
		return this->evaluateTeamInsideAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 13:
		return this->evaluateNamedInsideArea(c->getParameter(0), c->getParameter(1));
	case 8:
		return this->evaluateIsDestroyed(c->getParameter(0));
	case 170:
		return this->evaluateTeamCountCompare(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 172:
		return this->evaluateNamedUnitRankLevel(c->getParameter(0), c->getParameter(1));
	case 15:
		return this->evaluateNamedUnitDestroyed(c->getParameter(0));
	case 56:
		return this->evaluateNamedUnitDying(c->getParameter(0));
	case 57:
		return this->evaluateNamedUnitTotallyDead(c->getParameter(0));
	case 16:
		return this->evaluateNamedUnitExists(c->getParameter(0));
	case 10:
		return this->evaluateHasUnits(c->getParameter(0));
	case 9:
		return TheTacticalView->isCameraMovementFinished();
	case 189:
		return Rva003E4ED5Get(c->getParameter(0));
	case 190:
		return Rva003E4F05Get(c->getParameter(0));
	case 191:
		return Rva003E4F3BGet(c->getParameter(0));
	case 192:
		return Rva003E4F6BGet();
	case 11:
		return this->evaluateTeamStateIs(c->getParameter(0), c->getParameter(1));
	case 12:
		return this->evaluateTeamStateIsNot(c->getParameter(0), c->getParameter(1));
	case 14:
		return this->evaluateNamedOutsideArea(c->getParameter(0), c->getParameter(1));
	case 17:
		return this->evaluateTeamInsideAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 18:
		return this->evaluateTeamOutsideAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 19:
		return this->evaluateNamedAttackedByType(c->getParameter(0), c->getParameter(1));
	case 20:
		return this->evaluateTeamAttackedByType(c->getParameter(0), c->getParameter(1));
	case 21:
		return this->evaluateNamedAttackedByPlayer(c->getParameter(0), c->getParameter(1));
	case 22:
		return this->evaluateTeamAttackedByPlayer(c->getParameter(0), c->getParameter(1));
	case 23:
		return this->evaluateBuiltByPlayer(c, c->getParameter(0), c->getParameter(1));
	case 24:
		return this->evaluateNamedCreated(c->getParameter(0));
	case 25:
		return (this->*(bool (ScriptConditions::*)(Parameter *))&ScriptConditions::evaluateTeamCreated)(c->getParameter(0));
	case 26:
		return this->rva003E3F59(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 54:
		return this->evaluateBridgeRepaired(c->getParameter(0));
	case 55:
		return this->evaluateBridgeBroken(c->getParameter(0));
	case 27:
		return this->rva003E6A2B(c->getParameter(0), c->getParameter(1));
	case 28:
		return this->rva003E6AA9(c->getParameter(0), c->getParameter(1));
	case 51:
		return this->evaluateBuildingEntered(c->getParameter(0), c->getParameter(1));
	case 52:
		if (c->getNumParameters() < 3)
			return false;
		return this->rva003E56C5(*(const AsciiString *)c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 133:
		return this->rva003E6835(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 77:
		return this->rva003EA3AB(*(const AsciiString *)c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 78:
		return this->evaluateIsBuildingEmpty(c->getParameter(0));
	case 30:
		return this->evaluateNamedOwnedByPlayer(c->getParameter(0), c->getParameter(1));
	case 31:
		return this->evaluateTeamOwnedByPlayer(c->getParameter(0), c->getParameter(1));
	case 32:
		return this->evaluatePlayerHasNOrFewerBuildings(c->getParameter(1), c->getParameter(0));
	case 79:
		return this->rva003E586B(c->getParameter(1), c->getParameter(0));
	case 131:
		return this->rva003E58F0(c->getParameter(1), c->getParameter(0));
	case 33:
		return this->evaluatePlayerHasPower(c->getParameter(0));
	case 47:
		return !this->evaluatePlayerHasPower(c->getParameter(0));
	case 34:
		return this->evaluateNamedReachedWaypointsEnd(c->getParameter(0), c->getParameter(1));
	case 35:
		return this->evaluateTeamReachedWaypointsEnd(c->getParameter(0), c->getParameter(1));
	case 200:
		return this->rva003E6BC5(c, c->getParameter(0));
	case 37:
		return this->evaluateNamedSelected(c, c->getParameter(0));
	case 38:
		return this->evaluateNamedEnteredArea(c->getParameter(0), c->getParameter(1));
	case 39:
		return this->evaluateNamedExitedArea(c->getParameter(0), c->getParameter(1));
	case 40:
		return this->evaluateTeamEnteredAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 121:
		return this->rva003E4565(c->getParameter(0), c->getParameter(1));
	case 41:
		return this->evaluateTeamEnteredAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 42:
		return this->evaluateTeamExitedAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 43:
		return this->evaluateTeamExitedAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 147:
		return this->rva003E51D9(c->getParameter(0), c->getParameter(1));
	case 148:
		return this->rva003E6ED0(c->getParameter(0), (const AsciiString *)c->getParameter(1), 0, true, false);
	case 149:
		return this->rva003E6ED0(c->getParameter(0), (const AsciiString *)c->getParameter(1), 0, true, true);
	case 150:
		return this->rva003E6ED0(c->getParameter(0), (const AsciiString *)c->getParameter(1), 0, false, false);
	case 151:
		return this->rva003E6ED0(c->getParameter(0), (const AsciiString *)c->getParameter(1), 0, false, true);
	case 152:
		return this->rva003E6ED0(c->getParameter(0), 0, c->getParameter(1), true, false);
	case 153:
		return this->rva003E6ED0(c->getParameter(0), 0, c->getParameter(1), true, true);
	case 154:
		return this->rva003E6ED0(c->getParameter(0), 0, c->getParameter(1), false, false);
	case 155:
		return this->rva003E6ED0(c->getParameter(0), 0, c->getParameter(1), false, true);
	case 156:
		return this->rva003E59B0(c->getParameter(0), c->getParameter(1), 0, true);
	case 157:
		return this->rva003E59B0(c->getParameter(0), c->getParameter(1), 0, false);
	case 158:
		return this->rva003E59B0(c->getParameter(0), 0, c->getParameter(1), true);
	case 159:
		return this->rva003E59B0(c->getParameter(0), 0, c->getParameter(1), false);
	case 138:
		return this->rva003E5CB1(c->getParameter(0), c->getParameter(1));
	case 141:
		return this->rva003E83AF(c->getParameter(0), c->getParameter(1));
	case 44:
		return g_00E03138->isLocalAlliedVictory();
	case 45:
		return g_00E03138->isLocalAlliedDefeat();
	case 46:
		return ((bool (__cdecl *)(void))Rva003E468FCheck)();
	case 36:
		return Rva003E41CBGet(c->getParameter(0));
	case 48:
		return this->evaluateVideoHasCompleted(c->getParameter(0));
	case 49:
		return this->evaluateSpeechHasCompleted(c->getParameter(0));
	case 50:
		return this->evaluateAudioHasCompleted(c->getParameter(0));
	case 53:
		return this->evaluateUnitHealth(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 61:
		return this->evaluatePlayerSpecialPowerFromUnitTriggered(c->getParameter(0), c->getParameter(1), 0);
	case 64:
		return this->evaluatePlayerSpecialPowerFromUnitTriggered(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 63:
		return this->evaluatePlayerSpecialPowerFromUnitMidway(c->getParameter(0), c->getParameter(1), 0);
	case 66:
		return this->evaluatePlayerSpecialPowerFromUnitMidway(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 62:
		return this->evaluatePlayerSpecialPowerFromUnitComplete(c->getParameter(0), c->getParameter(1), 0);
	case 65:
		return this->evaluatePlayerSpecialPowerFromUnitComplete(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 100:
		return this->evaluateScienceAcquired(c->getParameter(0), c->getParameter(1));
	case 102:
		return this->evaluateCanPurchaseScience(c->getParameter(0), c->getParameter(1));
	case 101:
		return this->evaluateSciencePurchasePoints(c->getParameter(0), c->getParameter(1));
	case 173:
		return this->rva003E4519(c->getParameter(0));
	case 69:
		return this->evaluateUpgradeFromUnitComplete(c->getParameter(0), c->getParameter(1), 0);
	case 70:
		return this->evaluateUpgradeFromUnitComplete(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 58:
		return this->evaluatePlayerUnitCondition(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 71:
		return this->evaluatePlayerDestroyedNOrMoreBuildings(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 74:
		{
		Parameter *p4;
		if (c->getNumParameters() < 5)
			return false;
		p4 = c->getParameter(4);
		return this->rva003E61A4(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), p4, 0, false);
		}
	case 188:
		{
		Parameter *p4;
		if (c->getNumParameters() < 5)
			return false;
		p4 = c->getParameter(4);
		return this->rva003E61A4(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), p4, 0, true);
		}
	case 110:
		{
		Parameter *p4;
		Parameter *p5;
		if (c->getNumParameters() < 6)
			return false;
		p5 = c->getParameter(5);
		p4 = c->getParameter(4);
		return this->rva003E61A4(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), p4, p5, false);
		}
	case 194:
		return TheFormationAssistant->m_flag34();
	case 75:
		{
		Parameter *p4;
		if (c->getNumParameters() < 5)
			return false;
		p4 = c->getParameter(4);
		return this->rva003E64A6(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), p4);
		}
	case 160:
		return this->evaluatePlayerHasNumberObjectsWithModelCondition(c->getParameter(0), (CondA003E5F73 *)c->getParameter(1), (CondB003E5F73 *)c->getParameter(2), (CondC003E5F73 *)c->getParameter(3));
	case 161:
		return this->evaluatePlayerHasNumberUnitsDistanceFromObject(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), c->getParameter(4));
	case 76:
		return this->evaluateUnitHasEmptied(c->getParameter(0));
	case 83:
		return this->rva003E46B4(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 84:
		return this->rva003E477F(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 85:
		return this->rva003E9062(c->getParameter(0), c->getParameter(1));
	case 171:
		return this->rva003E91F6(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 80:
		return this->evaluateUnitHasObjectStatus(c->getParameter(0), c->getParameter(1));
	case 193:
		return this->rva003E5267(c->getParameter(0), c->getParameter(1));
	case 81:
		return this->evaluateTeamHasObjectStatus(c->getParameter(0), c->getParameter(1), true);
	case 82:
		return this->evaluateTeamHasObjectStatus(c->getParameter(0), c->getParameter(1), false);
	case 86:
		return this->rva003E719C(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 87:
		return this->evaluateSkirmishPlayerIsFaction(c->getParameter(0), c->getParameter(1));
	case 88:
		return this->rva003EA566(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 89:
		return this->slot15(c->getParameter(0), c->getParameter(1), c->getParameter(2), true);
	case 90:
		return this->slot15(c->getParameter(0), c->getParameter(1), c->getParameter(2), false);
	case 91:
		return this->evaluateSkirmishUnownedFactionUnitComparison(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 92:
		return this->evaluateSkirmishPlayerHasPrereqsToBuild(c->getParameter(0), c->getParameter(1));
	case 93:
		return this->evaluateSkirmishPlayerHasComparisonGarrisoned(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 94:
		return this->evaluateSkirmishPlayerHasComparisonCapturedUnits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 95:
		return this->evaluateSkirmishNamedAreaExists(c->getParameter(0), c->getParameter(1));
	case 96:
		return this->rva003E782D(c, c->getParameter(0), c->getParameter(1));
	case 97:
		return this->evaluateSkirmishPlayerHasBeenAttackedByPlayer(c->getParameter(0), c->getParameter(1));
	case 98:
		return this->evaluateSkirmishPlayerIsOutsideArea(c, c->getParameter(0), c->getParameter(1));
	case 99:
		return this->evaluateSkirmishPlayerHasDiscoveredPlayer(c->getParameter(0), c->getParameter(1));
	case 103:
		return this->evaluateMusicHasCompleted(c->getParameter(0), c->getParameter(1));
	case 105:
		return this->rva003E4A63(c, c->getParameter(0), c->getParameter(1));
	case 106:
		return this->rva003E4AE4(c->getParameter(0));
	case 107:
		return this->evaluateSkirmishStartPosition(c->getParameter(0), c->getParameter(1));
	case 108:
		return c->getParameter(1)->getInt() <= 0;
	case 109:
		return Rva003E4B83Get(c->getParameter(0));
	case 104:
		return this->evaluatePlayerLostObjectType(c->getParameter(0), c->getParameter(1));
	case 120:
		return Rva003E4EA5Get(c->getParameter(0));
	case 132:
		return Rva003E7FD5Get(c->getParameter(0));
	case 111:
		return this->evaluateCounterCounter(c);
	case 112:
		return this->evaluateCounterSeconds(c);
	case 113:
		return this->evaluateDistanceBetweenObjects(c);
	case 114:
		return this->evaluateDistanceBetweenTeams(c);
	case 115:
		return this->rva003E4D93(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 116:
		return this->rva003E7E54(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 117:
		return Rva003E4E6AGet(c->getParameter(0));
	case 118:
		return this->rva003E7F3A(c->getParameter(0), c->getParameter(1));
	case 123:
		return this->rva003E803D(c->getParameter(0), c->getParameter(1));
	case 124:
		return this->rva003E4F79(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 125:
		return this->rva003E80DA(c->getParameter(0), c->getParameter(1));
	case 126:
		return this->evaluateHasCommandPointsToBuildUnit(c->getParameter(0), c->getParameter(1));
	case 127:
		return this->evaluateCanBuildAtBase(c->getParameter(0), c->getParameter(1));
	case 169:
		return this->rva003E5017(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 128:
		return this->evaluatePlayerHasKilledKindOfUnits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 129:
		return this->evaluatePlayerHasKilledTypeUnits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 130:
		return this->evaluateNamedDestroyedByType(c->getParameter(0), c->getParameter(1));
	case 134:
		return this->rva003E63CD(c, c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 135:
		return this->rva003E3EC3(c->getParameter(0));
	case 142:
		return ((bool (__cdecl *)(void))Rva003E4C77Get)();
	case 136:
		return this->rva003E50B4(c->getParameter(0), c->getParameter(1));
	case 137:
		return this->rva003E5105(c->getParameter(0), c->getParameter(1));
	case 139:
		return this->rva003E84C5(c->getParameter(0), c->getParameter(1));
	case 140:
		return this->rva003E8535(c->getParameter(0), c->getParameter(1));
	case 143:
		return this->rva003E859E(c->getParameter(0), c->getParameter(1));
	case 144:
		return this->rva003E514F(c->getParameter(0), (CondA003E514F *)c->getParameter(1), (CondB003E514F *)c->getParameter(2));
	case 145:
		return this->rva003E52EB(c->getParameter(0), (CondA003E52EB *)c->getParameter(1), (CondB003E52EB *)c->getParameter(2));
	case 146:
		return this->rva003E8E23(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 162:
		return Rva003E537DCheck(c->getParameter(0));
	case 163:
		return this->rva003EA12A(c->getParameter(0));
	case 164:
		return this->rva003EA228(c->getParameter(0), true);
	case 165:
		return this->rva003EA228(c->getParameter(0), false);
	case 166:
		return ((bool (__stdcall *)(char))bfmeGo939D)(c->getParameter(0)->getInt() != 0);
	case 201:
		return this->evaluateGameModeActive(c->getParameter(0));
	case 168:
		return this->evaluateNumPlayersInGame((CondA003E53C8 *)c->getParameter(0), (CondB003E53C8 *)c->getParameter(1));
	case 174:
		return this->rva003E8D01(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 175:
		return (this->*(bool (ScriptConditions::*)(Parameter *, Cond003E5D95 *))&ScriptConditions::rva003E5D95)(c->getParameter(0), (Cond003E5D95 *)c->getParameter(1));
	case 176:
		return this->rva003E85E0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 177:
		return this->rva003E86A3(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 178:
		return this->rva003E8785(c->getParameter(0), c->getParameter(1), c->getParameter(2));
	case 179:
		return this->rva003E8863(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
	case 180:
		return this->rva003E89A9(c->getParameter(0), c->getParameter(1));
	case 182:
		return this->rva003E8C24(c->getParameter(0), c->getParameter(1));
	case 181:
		return this->rva003E8AA9(c->getParameter(0));
	case 183:
		return this->rva003E8B47(c->getParameter(0), c->getParameter(1));
	case 184:
		return Rva003E8FEE(c->getParameter(0));
	case 185:
		return Rva003E9029(c->getParameter(0)->getString());
	case 186:
		return this->evaluateHasEvaEventPlayedInLastNSeconds(*c->getParameter(0)->getString(), c->getParameter(1)->getReal());
	case 187:
		return this->evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(c->getParameter(0), c->getParameter(1)->getReal(), c->getParameter(2)->getString(), c->getParameter(3)->getInt(), c->getParameter(4)->getInt());
	case 195:
		return this->evaluateHasDelayedCarryoverUnitOfType(*c->getParameter(0)->getString(), c->getParameter(1));
	case 196:
		return Rva0056815A();
	case 197:
		return ((bool (__cdecl *)(void))Rva0043C99AGet)();
	case 198:
		return g_Va00E04450 != 0;
	case 199:
		return this->evaluatePlayerIsInPlanningMode(c->getParameter(0));
	default:
		return false;
	}
}
