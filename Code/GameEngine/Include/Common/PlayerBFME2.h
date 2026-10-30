#pragma once
// Player: canonical BFME2 header (hand-written; header_adopt_lane's
// generator emits no virtuals, and this class is polymorphic).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
// Named PlayerBFME2.h: Zero Hour headers include "Common/Player.h", so a
// Code/GameEngine/Include/Common/Player.h would shadow it for every unit with
// that directory on its include path.
//
// Target facts, read off game.dat (code addresses are RVAs, tables VAs):
//  - The ctor 0x002B0F3C stores the Snapshot base table 0x00BBB554 at +0 and
//    Rva002B0F3CIface's table 0x00BE2B78 at +4, constructs Rva00380200 (ctor
//    0x00380523) at +8, then stores Player's tables 0x00BFDF3C (+0),
//    0x00BFDF30 (+4) and 0x00BFDF18 (+8). Its own members start at +0x34
//    (8 + sizeof(Rva00380200)); it stores the int argument at +0x54. The
//    dtor 0x002B11A7 stores the same three tables. No /GR: the tables are
//    packed with no RTTI locator between them, which fixes their slot counts.
//  - 0x00BFDF3C, eight slots (the "Player" literal its slot 2 returns follows
//    slot 7): ??_G 0x002B14CF, then Snapshot's three (0x000B3FD0 empty,
//    0x002B117C returns that literal, 0x002B1522 the DoXfer row), then
//    Player's own virtuals computeSuperweaponTarget, checkBridges,
//    getAiBaseCenter, repairStructure (rows spelled U), in that order.
//    0x00BFDF30 fills Rva002B0F3CIface's three slots; 0x00BFDF18 holds the
//    ??_E thunk 0x002B1182 (sub ecx,8; jmp ??_G) and Player's overrides of
//    Rva00380200's slots 1-5.
//  - PlayerList allocates 0x758 bytes before the ctor call (0x002A7FBF):
//    sizeof 0x758, checked below.
//  - Data offsets from Player::init 0x002AF729, which stores the template at
//    +0x34, replaces +0x278 (build list), +0x2DC (AI), +0x2E4 and +0x2E8,
//    zeroes +0x2E0 and +0x2EC, sets +0x50 and +0x5C (= 1), and stores one
//    template colour into both +0x280 and +0x284, Zero Hour's
//    Player::init order (m_color, m_playerNightColor); setDefaultTeam
//    0x002ABC7E stores the team at +0x2EC. init also sets the bytes +0x338
//    and +0x339 to 1, +0x33A and +0x33B to 0, +0x33C to 1 and +0x33D to 0:
//    allowedToBuild 0x002ABE24 tests +0x339 then +0x338 (Zero Hour's
//    m_canBuildBase, m_canBuildUnits), isPlayerObserver 0x002AA223 reads
//    +0x33A (m_observer), setUnitsShouldHunt 0x002AE9B8 writes +0x33D
//    (m_unitsShouldHunt). +0x33C, defaulting to 1 between them, takes Zero
//    Hour's m_listInScoreScreen by that order (an inference; its out-of-line
//    setter 0x002A9D98 and getter 0x002A9DA5 still carry placeholder rows).
//
// Members: every Player row of reverse/functions.csv with the access,
// constness and parameter types its decorated name states, except
//  - countObjects, findClosestByKindOf, findClosestToPosByKindOf (BitFlags,
//    which some units define as a non-template), hasAnyRequiredSciences,
//    rva002AC425 and one rva002AB894 spelling (STL vector parameters);
//  - the out-of-line non-const getDefaultTeam (0x0046F7E4): 28 views inline
//    the const accessor instead, and both cannot be offered without moving
//    every non-const caller onto the out-of-line copy. (That row's body reads
//    +0x160, not +0x2EC, so its identity is doubtful anyway.)
// The Zero Hour inline accessors the views inline are included for the named
// members. Data: names where the views agree on offset and type, opaque
// elsewhere. Data access is not modeled (all public); it has no codegen effect.
#ifndef CANONICAL_PLAYER_H
#define CANONICAL_PLAYER_H

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Source/Common/Rva002B0F3CIface.h"
#include "../../Source/Common/Rva00380200.h"

class AcademyStats;
class AIGroup;
class AIPlayer;
class AsciiString;
class BfmeFixedStorage0004543D;
class BfmeTab1026;
class BuildListInfo;
struct Coord3D;
class CreateAHeroData;
class Dict;
class GameMessage;
class Object;
class Player;
class PlayerTemplate;
class ResourceGatheringManager;
class Rva001FDE3F;
struct Rva002A7588In;
class Rva002AA14DBonuses;
struct Rva002AB894List;
class Rva002AE4C5;
class Rva004B5A65Owner;
class SpecialPowerTemplate;
class Team;
class TeamPrototype;
class ThingTemplate;
class TunnelTracker;
class Upgrade;
class UpgradeTemplate;
class Waypoint;
class Xfer;
enum BattlePlanStatus;
enum CommandSourceType;
enum NameKeyType;
enum ObjectID;
enum PlayerType;
enum Relationship;
enum ScienceAvailabilityType;
enum ScienceType;
enum UpgradeStatusType;

class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200
{
public:
	Player(int playerIndex);						// 0x002B0F3C
	virtual ~Player();								// 0x002B11A7 (??_G 0x002B14CF, ??_E 0x002B1182)

	// Zero Hour inline accessors.
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	int getPlayerIndex() const { return m_playerIndex; }
	unsigned int getPlayerMask() const { return 1 << m_playerIndex; }
	int getPlayerType() const { return m_playerType; }
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
	void setCanBuildUnits(bool canProduce) { m_canBuildUnits = canProduce; }
	bool getCanBuildUnits() const { return m_canBuildUnits; }
	void setCanBuildBase(bool canProduce) { m_canBuildBase = canProduce; }
	bool getCanBuildBase() const { return m_canBuildBase; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	int getPlayerColor() const { return m_color; }
	BuildListInfo *getBuildList() const { return m_buildList; }
	int getMpStartIndex() const { return m_mpStartIndex; }
	ResourceGatheringManager *getResourceGatheringManager() const { return m_resourceGatheringManager; }
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }

	AsciiString getBaseSide() const;	// 0x0004F833
	AcademyStats *getAcademyStats();	// 0x000B6464
	bool isPlayerDead() const;	// 0x0028A7D8
	void accumulateRTSBattleStatsIntoLivingWorldScoreKeeper();	// 0x002A9994
	void rva002A99FA();	// 0x002A99FA
	void setPlayerType(PlayerType, bool);	// 0x002A9A18
	void addCommandPoints(Rva002A7588In *);	// 0x002A9B35
	void removeCommandPoints(Rva002A7588In *);	// 0x002A9B58
	bool isSkirmishAIPlayer();	// 0x002A9B7B
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *, Coord3D *, int, float);	// 0x002A9B92
	virtual bool checkBridges(Object *, Waypoint *);	// 0x002A9C0D
	virtual bool getAiBaseCenter(Coord3D *);	// 0x002A9C26
	virtual void repairStructure(ObjectID);	// 0x002A9C48
	void onUnitCreated(Object *, Object *);	// 0x002A9C5F
	bool rva002A9CA4(int);	// 0x002A9CA4
	bool rva002A9CB8();	// 0x002A9CB8
	void onStructureConstructionComplete(Object *, Object *, bool);	// 0x002A9D02
	bool isLocalPlayer() const;	// 0x002A9D89
	int getSupplyBoxValue();	// 0x002A9DAC
	void rva002A9E25(float);	// 0x002A9E25
	int ScaleMoney(int);	// 0x002A9E36
	bool hasPrereqsForScience(ScienceType) const;	// 0x002A9EAC
	bool rva002A9ED9(const SpecialPowerTemplate *);	// 0x002A9ED9
	unsigned char rva002AA00C(ThingTemplate *, int);	// 0x002AA00C
	Upgrade *findUpgrade(const UpgradeTemplate *);	// 0x002AA031
	bool hasRadar() const;	// 0x002AA08E
	bool doesObjectQualifyForBattlePlan(Object *) const;	// 0x002AA0DE
	void getCurrentSelectionAsAIGroup(AIGroup *);	// 0x002AA164
	bool isPlayerObserver() const;	// 0x002AA223
	bool rva002AA245() const;	// 0x002AA245
	void onStructureCreated(Object *, Object *);	// 0x002AA559
	bool addSkillPointsForDamage(Object *, const Object *, float);	// 0x002AA5E1
	bool addSkillPointsForKill(const Object *, const Object *);	// 0x002AA6DE
	void rva002AA756(int);	// 0x002AA756
	void deleteUpgradeList();	// 0x002AA7E6
	const ThingTemplate *rva002AA857(int);	// 0x002AA857
	bool rva002AA8EF(const UpgradeTemplate *) const;	// 0x002AA8EF
	void addRadar(bool);	// 0x002AA91F
	void removeRadar(bool);	// 0x002AA9C2
	void disableRadar();	// 0x002AAA65
	void enableRadar();	// 0x002AAAF9
	void rva002AABBC();	// 0x002AABBC
	void addToBuildList(Object *);	// 0x002AAEC5
	void addToPriorityBuildList(const AsciiString &, Coord3D *, float);	// 0x002AAF72
	void healAllObjects();	// 0x002AB06A
	int iterateObjects(int (*)(Object *, void *), void *) const;	// 0x002AB08B
	void countObjectsByThingTemplate(int, const ThingTemplate *const *, bool, int *, bool) const;	// 0x002AB0C5
	int countBuildings();	// 0x002AB10F
	Object *findClosestObjectToPosWithValidLivingWorldArmyID(const void *) const;	// 0x002AB22A
	bool rva002AB260(bool) const;	// 0x002AB260
	bool rva002AB295(BfmeFixedStorage0004543D, bool) const;	// 0x002AB295
	bool rva002AB2D9(BfmeTab1026 *, bool) const;	// 0x002AB2D9
	bool rva002AB312() const;	// 0x002AB312
	bool rva002AB341(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D) const;	// 0x002AB341
	bool rva002AB390(BfmeTab1026 *) const;	// 0x002AB390
	bool hasAnyObjects(bool) const;	// 0x002AB3C5
	bool rva002AB3FA() const;	// 0x002AB3FA
	void updateTeamStates();	// 0x002AB429
	void doBountyForKill(const Object *, const Object *);	// 0x002AB63D
	bool hasScience(ScienceType) const;	// 0x002AB7D5
	bool rva002AB82D(CreateAHeroData *) const;	// 0x002AB82D
	bool rva002AB855(CreateAHeroData *) const;	// 0x002AB855
	bool rva002AB87D(const UpgradeTemplate *) const;	// 0x002AB87D
	bool rva002AB894(const Rva002AB894List &) const;	// 0x002AB894
	void onPowerBrownOutChange(bool);	// 0x002AB8D0
	void rva002AB8FB(Object *, bool);	// 0x002AB8FB
	void setUnitsVisionSpied(bool, int);	// 0x002ABA3D
	void rva002ABA9B();	// 0x002ABA9B
	void rva002ABAA6();	// 0x002ABAA6
	void rva002ABAB3();	// 0x002ABAB3
	void setDefaultTeam();	// 0x002ABC7E
	int rva002ABCF0(unsigned char, int *);	// 0x002ABCF0
	int rva002ABD1D(int, int);	// 0x002ABD1D
	void removeTeamFromList(TeamPrototype *);	// 0x002ABD48
	void setObjectsEnabled(const AsciiString &, bool);	// 0x002ABD93
	bool allowedToBuild(const ThingTemplate *) const;	// 0x002ABE24
	bool isCapableOfPurchasingScience(ScienceType) const;	// 0x002ABE86
	ScienceAvailabilityType getScienceAvailabilityTypeFromString(const AsciiString &);	// 0x002ABEC9
	bool canBuild(const ThingTemplate *) const;	// 0x002ABEF1
	Relationship getRelationship(const Player *) const;	// 0x002AC3E0
	bool rva002AC43F(int *);	// 0x002AC43F
	bool rva002AC4D4(int *);	// 0x002AC4D4
	Object *findNaturalCommandCenter();	// 0x002AC60A
	Object *rva002AC629();	// 0x002AC629
	void rva002AC673();	// 0x002AC673
	void applyBattlePlanBonusesForObject(Object *) const;	// 0x002AC917
	void removeBattlePlanBonusesForObject(Object *) const;	// 0x002AC92B
	void applyBattlePlanBonusesForPlayerObjects(const Rva002AA14DBonuses *);	// 0x002AC9BF
	void processCreateTeamGameMessage(int, const GameMessage *);	// 0x002ACA86
	void processSelectTeamGameMessage(int, GameMessage *);	// 0x002ACAFB
	void processAddTeamGameMessage(int, GameMessage *);	// 0x002ACBA8
	void setCurrentlySelectedAIGroup(AIGroup *);	// 0x002ACC53
	void addAIGroupToCurrentSelection(AIGroup *);	// 0x002ACCA3
	void rva002ACD09(void *, int);	// 0x002ACD09
	float getProductionCostChangeBasedOnTemplate(const ThingTemplate *, bool);	// 0x002ACD6B
	int getProductionCostChangeByObjectFilterID(void *);	// 0x002ACE2B
	Relationship getRelationship(const Team *) const;	// 0x002AD0C6
	Relationship getRelationship(const Object *) const;	// 0x002AD11E
	void rva002AD1FD();	// 0x002AD1FD
	void rva002AD25B(const AsciiString &);	// 0x002AD25B
	void becomingTeamMember(Object *, bool);	// 0x002AD4EC
	int rva002AD629(const AsciiString &);	// 0x002AD629
	bool attemptToPurchaseScience(ScienceType);	// 0x002AD826
	bool grantScience(ScienceType);	// 0x002AD85E
	bool forcePurchaseScience(ScienceType);	// 0x002AD883
	void setScienceAvailability(ScienceType, ScienceAvailabilityType);	// 0x002AD8C9
	void onUpgradeCompleted(const UpgradeTemplate *, int);	// 0x002AD93A
	void onUpgradeRemoved(const UpgradeTemplate *, int);	// 0x002AD9FD
	void removeUpgrade(const UpgradeTemplate *, int);	// 0x002ADAC3
	void changeBattlePlan(BattlePlanStatus, int, Rva002AA14DBonuses *);	// 0x002ADB4F
	void rva002ADC03(Rva004B5A65Owner *, int);	// 0x002ADC03
	float getProductionCostChangeBasedOnUpgradeDiscount(AsciiString) const;	// 0x002ADC82
	void becomingLocalPlayer(bool);	// 0x002ADFF2
	void addTeamToList(TeamPrototype *);	// 0x002AE228
	void rva002AE252();	// 0x002AE252
	void rva002AE2ED(Player *);	// 0x002AE2ED
	Upgrade *addUpgrade(const UpgradeTemplate *, UpgradeStatusType, int);	// 0x002AE329
	void rva002AE475(void *);	// 0x002AE475
	void update();	// 0x002AE770
	void rva002AE8CF(const AsciiString *, float, int);	// 0x002AE8CF
	void rva002AE930(const AsciiString *);	// 0x002AE930
	void setUnitsShouldHunt(bool, CommandSourceType);	// 0x002AE9B8
	void transferAssetsFromThat(Player *, bool);	// 0x002AEA9F
	void garrisonAllUnits(CommandSourceType);	// 0x002AEEA7
	void ungarrisonAllUnits(CommandSourceType);	// 0x002AF037
	void setUnitsShouldIdleOrResume(bool);	// 0x002AF0C5
	void initPlayerUpgrades();	// 0x002AF19B
	void rva002AF236(Xfer *, Rva001FDE3F *);	// 0x002AF236
	void rva002AF33B(Xfer *, Rva002AE4C5 *);	// 0x002AF33B
	void rva002AF614(void *);	// 0x002AF614
	void init(const PlayerTemplate *);	// 0x002AF729
	void initFromDict(const Dict *);	// 0x002AFCDF
	bool cloneFrom(Player *);	// 0x002B07A9
	void initBuildableHeroes();	// 0x002B0B96
	void newMap();	// 0x002B0D00
	void onStructureUndone(Object *);	// 0x0047A69C
	int getPlayerNightColor() const;	// 0x00509D29

	// Rva002B0F3CIface and Rva00380200 slots Player fills.
	virtual bool islot00(ScienceType) const;		// 0x002B118A
	virtual int islot01() const;					// 0x0030D377
	virtual void islot02(CreateAHeroData *, bool *);	// 0x002B1192
	virtual bool rva0038037C(int);					// 0x002A9FA0
	virtual void rslot02(int);						// 0x002A9F5E
	virtual void rslot03();							// 0x002AE318
	virtual void rslot04(const void *);				// 0x002AD7E9
	virtual bool rslot05();							// 0x002A9F53

	// Snapshot slots, spelled the way the unit selected Snapshot.h's; Player's
	// slot 3 row is DoXfer(Xfer *).
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();					// 0x000B3FD0
#else
	virtual void loadPostProcess();					// 0x000B3FD0
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;	// 0x002B117C
#endif
#else
	virtual void crc(Xfer *xfer);					// 0x002B117C
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);				// 0x002B1522
#endif
#else
	virtual void xfer(Xfer *xfer);					// 0x002B1522
#endif

private:
	bool addScience(ScienceType science);			// 0x002AD661, private (A)

public:
	const PlayerTemplate *m_playerTemplate;			// +0x34
	unsigned char m_opaque38[0x4C - 0x38];			// +0x38 display name, handicap
	unsigned char m_opaque4C[4];					// +0x4C AsciiString m_playerName
	NameKeyType m_playerNameKey;					// +0x50
	int m_playerIndex;								// +0x54
	unsigned char m_opaque58[4];					// +0x58 AsciiString m_side
	int m_playerType;								// +0x5C
	unsigned char m_opaque60[0x278 - 0x60];			// +0x60
	BuildListInfo *m_buildList;						// +0x278
	int m_27C;										// +0x27C
	int m_color;									// +0x280
	int m_playerNightColor;							// +0x284
	unsigned char m_opaque288[0x2DC - 0x288];		// +0x288
	AIPlayer *m_ai;									// +0x2DC
	int m_mpStartIndex;								// +0x2E0
	ResourceGatheringManager *m_resourceGatheringManager;	// +0x2E4
	TunnelTracker *m_tunnelSystem;					// +0x2E8
	Team *m_defaultTeam;							// +0x2EC
	unsigned char m_opaque2F0[0x338 - 0x2F0];		// +0x2F0 (+0x32C team prototype list)
	bool m_canBuildUnits;							// +0x338
	bool m_canBuildBase;							// +0x339
	bool m_observer;								// +0x33A
	unsigned char m_opaque33B[1];					// +0x33B
	bool m_listInScoreScreen;						// +0x33C
	bool m_unitsShouldHunt;							// +0x33D
	unsigned char m_opaque33E[0x758 - 0x33E];		// +0x33E
};													// sizeof 0x758
typedef char CanonicalPlayerSizeCheck[sizeof(Player) == 0x758 ? 1 : -1];

#endif // CANONICAL_PLAYER_H
