#pragma once
// ScriptConditions: canonical BFME2 header (hand-written; header_adopt_lane's
// generator emits no virtuals, and its contract left slot 1 undecided while
// the private views flatten the base, so it reads sizeof 4 and no base).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
//
// Target facts, read off game.dat:
//  - The ctor 0x003E5513 calls SubsystemInterface's ctor 0x001B4E63 and stores
//    vftable 0x00C35B38; ScriptEngine::init news 0xC bytes for it, so sizeof is
//    SubsystemInterface's 12 bytes and ScriptConditions adds no data.
//  - The dtor 0x003E5525 stores 0x00C35B38, calls reset 0x003E3C66, stores
//    0x00C35AE0 and calls ~SubsystemInterface 0x001B4E74: ZH's
//    ScriptConditions::~ScriptConditions() { reset(); } over the inline
//    ~ScriptConditionsInterface (its out-of-line copy is 0x003E3BD4).
//  - Table 0x00C35AE0 (ScriptConditionsInterface) has 18 slots: the fourteen of
//    SubsystemInterface with 1, 9 and 10 pure, then four pure slots 14-17.
//  - Table 0x00C35B38 (ScriptConditions) has the same 18 slots: 0 ??_G
//    0x003E5DCD, 1 init (the folded empty body 0x000D20D6), 9 reset 0x003E3C66,
//    10 update (the folded empty body 0x000B3FD0), 14 evaluateCondition
//    0x003EC8D4, 15 evaluateSkirmishCommandButtonIsReady 0x003E73E7, 16
//    evaluateTeamIsContained 0x003E70AC, 17 the gate condition 0x003E4921; the
//    other slots keep SubsystemInterface's default bodies.
//  - Slot 17 is called virtually: ScriptEngine's sequential-script pass calls
//    TheScriptConditions->[vptr+0x44]. Its row is decorated as the non-virtual
//    ?rva003E4921@ScriptConditions@@QAE_NPAVParameter@@@Z and
//    reverse/data_ledger.csv keys two static locals by that decoration, so the
//    slot is declared here as slot17 beside the non-virtual rva003E4921; a unit
//    that emits the vftable binds slot17 to the row (as ScriptConditions_ctor.cpp
//    binds init with /alternatename).
//
// The base is the 14-slot SubsystemInterface of subsystem_bfme2, the same
// header the canonical ScriptEngine and ScriptActions derive from.
//
// Members: every ScriptConditions row of reverse/functions.csv, with the access
// and parameter types its decorated name states (I = protected, Q = public,
// M = protected virtual, U = public virtual). Addresses are target RVAs.
#ifndef CANONICAL_SCRIPTCONDITIONS_H
#define CANONICAL_SCRIPTCONDITIONS_H

// subsystem_interface.h spells loadIniFilesFromLegend's return Bool; the
// canonical ScriptEngine and ScriptActions headers declare the same typedef.
typedef bool Bool;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

class Condition;
class Parameter;
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

class ScriptConditionsInterface : public SubsystemInterface
{
public:
	virtual ~ScriptConditionsInterface() { }

	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

	virtual Bool evaluateCondition(Condition *pCondition) = 0;								// slot 14
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *pSkirmishPlayerParm, Parameter *pTeamParm,
		Parameter *pCommandButtonParm, Bool allReady) = 0;									// slot 15
	virtual Bool evaluateTeamIsContained(Parameter *pTeamParm, Bool allContained) = 0;		// slot 16
	virtual Bool slot17(Parameter *pParm) = 0;												// slot 17
};

class ScriptConditions : public ScriptConditionsInterface
{
public:
	ScriptConditions();								// 0x003E5513
	virtual ~ScriptConditions();					// 0x003E5525 (slot 0: ??_G 0x003E5DCD)

	virtual void init();							// slot 1, 0x000D20D6
	virtual void reset();							// slot 9, 0x003E3C66
	virtual void update();							// slot 10, 0x000B3FD0

	virtual Bool evaluateCondition(Condition *pCondition);		// slot 14, 0x003EC8D4
	virtual Bool slot17(Parameter *pParm);						// slot 17, 0x003E4921

	int rva003E40AF(int);	// 0x003E40AF
	bool rva003E4921(Parameter *);	// 0x003E4921
	bool evaluateEnemySighted(const AsciiString &, Parameter *, Parameter *);	// 0x003E56C5
	bool rva003E5CB1(Parameter *, Parameter *);	// 0x003E5CB1
	bool rva003E6835(Parameter *, Parameter *, Parameter *);	// 0x003E6835
	bool rva003E6ED0(Parameter *, const AsciiString *, Parameter *, bool, bool);	// 0x003E6ED0
	bool rva003E83AF(Parameter *, Parameter *);	// 0x003E83AF
	bool evaluateTypeSighted(const AsciiString &, Parameter *, Parameter *);	// 0x003EA3AB
	bool evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003EA566
	bool evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt(Parameter *, float, const AsciiString *, int, int);	// 0x003EA764

protected:
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *pSkirmishPlayerParm, Parameter *pTeamParm,
		Parameter *pCommandButtonParm, Bool allReady);			// slot 15, 0x003E73E7
	virtual Bool evaluateTeamIsContained(Parameter *pTeamParm, Bool allContained);	// slot 16, 0x003E70AC

	bool evaluateAllDestroyed(Parameter *);	// 0x003E3C89
	bool evaluateAllBuildFacilitiesDestroyed(Parameter *);	// 0x003E3D10
	bool evaluateBridgeBroken(Parameter *);	// 0x003E3D95
	bool evaluateBridgeRepaired(Parameter *);	// 0x003E3DC6
	bool evaluateNamedUnitDestroyed(Parameter *);	// 0x003E3DF7
	bool evaluateNamedUnitExists(Parameter *);	// 0x003E3E2F
	bool evaluateNamedUnitDying(Parameter *);	// 0x003E3E54
	bool evaluateNamedUnitTotallyDead(Parameter *);	// 0x003E3E89
	bool rva003E3EBA();	// 0x003E3EBA
	bool rva003E3EC3(Parameter *);	// 0x003E3EC3
	bool evaluateNamedCreated(Parameter *);	// 0x003E3F41
	bool evaluatePlayerHasCredits(Parameter *, Parameter *, Parameter *);	// 0x003E3F59
	bool evaluateBuildingEntered(Parameter *, Parameter *);	// 0x003E3FFE
	bool evaluateIsBuildingEmpty(Parameter *);	// 0x003E4079
	bool evaluateNamedOwnedByPlayer(Parameter *, Parameter *);	// 0x003E40D2
	bool evaluatePlayerHasNOrFewerBuildings(Parameter *, Parameter *);	// 0x003E4132
	bool evaluatePlayerHasPower(Parameter *);	// 0x003E417D
	bool evaluateVideoHasCompleted(Parameter *);	// 0x003E41E3
	bool evaluateSpeechHasCompleted(Parameter *);	// 0x003E41FB
	bool evaluateAudioHasCompleted(Parameter *);	// 0x003E4213
	bool evaluatePlayerSpecialPowerFromUnitTriggered(Parameter *, Parameter *, Parameter *);	// 0x003E422B
	bool evaluatePlayerSpecialPowerFromUnitMidway(Parameter *, Parameter *, Parameter *);	// 0x003E42A1
	bool evaluatePlayerSpecialPowerFromUnitComplete(Parameter *, Parameter *, Parameter *);	// 0x003E4317
	bool evaluateUpgradeFromUnitComplete(Parameter *, Parameter *, Parameter *);	// 0x003E438D
	bool evaluateScienceAcquired(Parameter *, Parameter *);	// 0x003E4403
	bool evaluateCanPurchaseScience(Parameter *, Parameter *);	// 0x003E446F
	bool evaluateSciencePurchasePoints(Parameter *, Parameter *);	// 0x003E44D1
	bool rva003E4519(Parameter *);	// 0x003E4519
	bool evaluateNamedBaseUnpackableForPlayer(Parameter *, Parameter *);	// 0x003E4565
	bool evaluatePlayerHasComparisonPercentPower(Parameter *, Parameter *, Parameter *);	// 0x003E46B4
	bool evaluatePlayerHasComparisonValueExcessPower(Parameter *, Parameter *, Parameter *);	// 0x003E477F
	bool evaluatePlayerDestroyedNOrMoreBuildings(Parameter *, Parameter *, Parameter *);	// 0x003E4810
	bool evaluateUnitHasEmptied(Parameter *);	// 0x003E4860
	bool evaluateSkirmishPlayerHasPrereqsToBuild(Parameter *, Parameter *);	// 0x003E49B8
	bool evaluateSkirmishSupplySourceSafe(Condition *, Parameter *, Parameter *);	// 0x003E4A63
	bool evaluateSkirmishSupplySourceAttacked(Parameter *);	// 0x003E4AE4
	bool evaluateSkirmishStartPosition(Parameter *, Parameter *);	// 0x003E4B2A
	bool evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *, Parameter *);	// 0x003E4BFA
	bool evaluateDistanceBetweenObjects(Condition *);	// 0x003E4C8D
	bool rva003E4D93(Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E4D93
	bool evaluatePlayerCompareLightPoints(Parameter *, Parameter *, Parameter *);	// 0x003E4F79
	bool evaluateCanBuildObjectTypeAtBase(Parameter *, Parameter *, Parameter *);	// 0x003E5017
	bool evaluateNamedCanPathToWaypoint(Parameter *, Parameter *);	// 0x003E50B4
	bool rva003E5105(Parameter *, Parameter *);	// 0x003E5105
	bool rva003E514F(Parameter *, CondA003E514F *, CondB003E514F *);	// 0x003E514F
	bool rva003E51D9(Parameter *, Parameter *);	// 0x003E51D9
	bool rva003E5267(Parameter *, Parameter *);	// 0x003E5267
	bool rva003E52EB(Parameter *, CondA003E52EB *, CondB003E52EB *);	// 0x003E52EB
	bool evaluateNumPlayersInGame(CondA003E53C8 *, CondB003E53C8 *);	// 0x003E53C8
	bool evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &, float);	// 0x003E543A
	bool evaluatePlayerIsInPlanningMode(Parameter *);	// 0x003E54B4
	bool evaluateUnitHealth(Parameter *, Parameter *, Parameter *);	// 0x003E5587
	bool evaluatePlayerHasNOrFewerFactionBuildings(Parameter *, Parameter *);	// 0x003E586B
	bool evaluatePlayerHasNOrFewerBases(Parameter *, Parameter *);	// 0x003E58F0
	bool rva003E59B0(Parameter *, Parameter *, Parameter *, bool);	// 0x003E59B0
	bool evaluateUnitHasObjectStatus(Parameter *, Parameter *);	// 0x003E5AE9
	bool evaluateCanBuildAtBase(Parameter *, Parameter *);	// 0x003E5B11
	bool evaluatePlayerHasKilledKindOfUnits(Parameter *, Parameter *, Parameter *);	// 0x003E5C04
	unsigned char rva003E5D95(Parameter *, Cond003E5D95 *);	// 0x003E5D95
	bool evaluateIsDestroyed(Parameter *);	// 0x003E5DE9
	bool evaluateTeamCountCompare(Parameter *, Parameter *, Parameter *);	// 0x003E5E2F
	bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);	// 0x003E5E7D
	bool evaluateNamedInsideArea(Parameter *, Parameter *);	// 0x003E5EFF
	bool evaluatePlayerHasNumberObjectsWithModelCondition(Parameter *, CondA003E5F73 *, CondB003E5F73 *, CondC003E5F73 *);	// 0x003E5F73
	bool evaluatePlayerHasNumberUnitsDistanceFromObject(Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E609F
	bool evaluatePlayerHasUnitTypeInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *, bool);	// 0x003E61A4
	bool rva003E63CD(Condition *, Parameter *, Parameter *, Parameter *);	// 0x003E63CD
	bool evaluatePlayerHasUnitKindInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E64A6
	bool evaluateNamedOutsideArea(Parameter *, Parameter *);	// 0x003E66D5
	bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);	// 0x003E66EA
	bool evaluateTeamOutsideAreaEntirely(Parameter *, Parameter *, Parameter *);	// 0x003E674C
	bool evaluateTeamAttackedByPlayer(Parameter *, Parameter *);	// 0x003E6784
	unsigned char evaluateTeamCreated(Parameter *);	// 0x003E6803
	bool evaluateNamedDiscovered(Parameter *, Parameter *);	// 0x003E6A2B
	bool evaluateTeamDiscovered(Parameter *, Parameter *);	// 0x003E6AA9
	bool evaluateTeamOwnedByPlayer(Parameter *, Parameter *);	// 0x003E6B57
	bool rva003E6BC5(Condition *, Parameter *);	// 0x003E6BC5
	bool evaluateNamedEnteredArea(Parameter *, Parameter *);	// 0x003E6D0A
	bool evaluateNamedExitedArea(Parameter *, Parameter *);	// 0x003E6D60
	bool evaluateTeamEnteredAreaEntirely(Parameter *, Parameter *, Parameter *);	// 0x003E6DAA
	bool evaluateTeamEnteredAreaPartially(Parameter *, Parameter *, Parameter *);	// 0x003E6E0C
	bool evaluateTeamExitedAreaEntirely(Parameter *, Parameter *, Parameter *);	// 0x003E6E6E
	bool evaluateTeamExitedAreaPartially(Parameter *, Parameter *, Parameter *);	// 0x003E704A
	bool evaluateTeamHasObjectStatus(Parameter *, Parameter *, bool);	// 0x003E712A
	bool evaluateSkirmishValueInArea(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E719C
	bool evaluateSkirmishUnownedFactionUnitComparison(Parameter *, Parameter *, Parameter *);	// 0x003E749E
	bool evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *, Parameter *, Parameter *);	// 0x003E7597
	bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *, Parameter *, Parameter *);	// 0x003E76E4
	bool evaluateSkirmishNamedAreaExists(Parameter *, Parameter *);	// 0x003E77FF
	bool evaluateSkirmishPlayerHasUnitsInArea(Condition *, Parameter *, Parameter *);	// 0x003E782D
	bool evaluateSkirmishPlayerIsOutsideArea(Condition *, Parameter *, Parameter *);	// 0x003E79AF
	bool evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *, Parameter *);	// 0x003E79F5
	bool evaluateMusicHasCompleted(Parameter *, Parameter *);	// 0x003E7AFC
	bool evaluateDistanceBetweenTeams(Condition *);	// 0x003E7B56
	bool evaluateCounterCounter(Condition *);	// 0x003E7CBA
	bool evaluateCounterSeconds(Condition *);	// 0x003E7D83
	bool evaluateTeamCachedFloatCompare(Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E7E54
	bool rva003E7F3A(Parameter *, Parameter *);	// 0x003E7F3A
	bool evaluateTeamIsLedByUnit(Parameter *, Parameter *);	// 0x003E803D
	bool evaluateHasCommandPointsToBuildTeam(Parameter *, Parameter *);	// 0x003E80DA
	bool evaluateHasCommandPointsToBuildUnit(Parameter *, Parameter *);	// 0x003E81E8
	bool evaluatePlayerHasKilledTypeUnits(Parameter *, Parameter *, Parameter *);	// 0x003E82E2
	bool evaluateTeamCanPathToWaypoint(Parameter *, Parameter *);	// 0x003E84C5
	bool evaluateTeamCanPathToNamed(Parameter *, Parameter *);	// 0x003E8535
	bool rva003E859E(Parameter *, Parameter *);	// 0x003E859E
	bool rva003E85E0(Parameter *, Parameter *, Parameter *);	// 0x003E85E0
	bool rva003E86A3(Parameter *, Parameter *, Parameter *);	// 0x003E86A3
	bool rva003E8785(Parameter *, Parameter *, Parameter *);	// 0x003E8785
	bool rva003E8863(Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E8863
	bool evaluateUnitHasToggledWeapon(Parameter *, Parameter *);	// 0x003E89A9
	bool evaluateAnyUnitsUsingBloodthirsty(Parameter *);	// 0x003E8AA9
	bool rva003E8B47(Parameter *, Parameter *);	// 0x003E8B47
	bool rva003E8C24(Parameter *, Parameter *);	// 0x003E8C24
	bool rva003E8D01(Parameter *, Parameter *, Parameter *);	// 0x003E8D01
	bool rva003E8E23(Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E8E23
	bool evaluateSkirmishSpecialPowerIsReady(Parameter *, Parameter *);	// 0x003E9062
	bool evaluateSkirmishCanFireSpecialPowerOnTeam(Parameter *, Parameter *, Parameter *);	// 0x003E91F6
	bool evaluateGameModeActive(Parameter *);	// 0x003E92B2
	bool evaluateNamedUnitRankLevel(Parameter *, Parameter *);	// 0x003E92DF
	bool evaluateHasUnits(Parameter *);	// 0x003E9373
	bool evaluateTeamStateIs(Parameter *, Parameter *);	// 0x003E9471
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);	// 0x003E94E5
	bool evaluateNamedAttackedByType(Parameter *, Parameter *);	// 0x003E9556
	bool evaluateTeamAttackedByType(Parameter *, Parameter *);	// 0x003E95FF
	bool evaluateNamedAttackedByPlayer(Parameter *, Parameter *);	// 0x003E96F5
	bool evaluateBuiltByPlayer(Condition *, Parameter *, Parameter *);	// 0x003E977E
	bool evaluateNamedReachedWaypointsEnd(Parameter *, Parameter *);	// 0x003E992C
	bool evaluateTeamReachedWaypointsEnd(Parameter *, Parameter *);	// 0x003E9A1F
	bool evaluateNamedSelected(Condition *, Parameter *);	// 0x003E9B6A
	bool evaluatePlayerUnitCondition(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);	// 0x003E9C3B
	bool evaluateSkirmishPlayerIsFaction(Parameter *, Parameter *);	// 0x003E9E62
	bool evaluatePlayerLostObjectType(Parameter *, Parameter *);	// 0x003E9EB0
	bool evaluateNamedDestroyedByType(Parameter *, Parameter *);	// 0x003EA076
	bool rva003EA12A(Parameter *);	// 0x003EA12A
	bool rva003EA228(Parameter *, bool);	// 0x003EA228
	bool evaluateHasDelayedCarryoverUnitOfType(const AsciiString &, Parameter *);	// 0x003EA87C
	bool evaluateConditionHelper(Condition *);	// 0x003EA9AF
};

#endif // CANONICAL_SCRIPTCONDITIONS_H
