#pragma once
// Target Player ABI: ctor RVA 2B0F3C and dtor 2B11A7 install
// BFDF3C at +0, BFDF30 at +4, BFDF18 at +8. Allocation 2A7FBF
// is 0x758. Primary slots 4..7 are the matched AI delegates.
// Named members carry the retail store or access that places them; the
// rest of the storage stays opaque and no donor layout is imported.
// Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Source/Common/Rva00380200.h"
#include "../GameLogic/Module/Rva003B0D7C.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class PlayerTemplate;
class Upgrade;
class UpgradeTemplate;
enum Relationship;
enum UpgradeStatusType;
class Player;
class Team;
class AIPlayer;
class Object;
class Waypoint;
class SpecialPowerTemplate;
class CreateAHeroData;
struct Coord3D;
enum ObjectID;
enum ScienceType;
class ThingTemplate;
class ResourceGatheringManager;
class TunnelTracker;
class PlayerRelationMap;
class TeamRelationMap;
class Rva002AA14DBonuses;
struct Rva002AB894List;
enum NameKeyType;
enum PlayerType;
class AIGroup;
class Squad;
class BuildListInfo;
struct PlayerTeamNode;
class BfmeFixedStorage0004543D;
class BfmeTab1026;
class Dict;
class GameMessage;
class Rva001FDE3F;
struct Rva002A7588In;
class Rva002AE4C5;
class Rva004B5A65Owner;
class TeamPrototype;
enum BattlePlanStatus;
enum CommandSourceType;
enum ScienceAvailabilityType;
// Structural name retained from the matched constructor. The original base
// identity is unknown. Table BE2B78 is three pure slots; Player's BFDF30
// contains 2B118A (this-4 to hasScience), 30D377 (Player+0x24 integer getter),
// and 2B1192 (this-4 to rva002AB855, AL stored through second argument).
class Rva002B0F3CIface {
public:
 virtual bool v0(ScienceType) const = 0;
 virtual int v1() const = 0;
 virtual void v2(CreateAHeroData *, bool *) const = 0;
};
class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200 {
public:
 Player(int);
 virtual ~Player();
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
 virtual void LoadPostProcess();
#else
 virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
 virtual const char *GetSnapshotName();
#else
 virtual const char *GetSnapshotName() const;
#endif
#else
 virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer &);
#else
 virtual void DoXfer(Xfer *);
#endif
#else
 virtual void xfer(Xfer *);
#endif
 virtual void computeSuperweaponTarget(const SpecialPowerTemplate *, Coord3D *, int, float);
 virtual bool checkBridges(Object *, Waypoint *);
 virtual bool getAiBaseCenter(Coord3D *);
 virtual void repairStructure(ObjectID);
 // Secondary-table overrides; names are structural, not recovered identities.
 virtual bool v0(ScienceType) const;
 virtual int v1() const;
 virtual void v2(CreateAHeroData *, bool *) const;
 virtual bool rva0038037C(int);
 virtual void rslot02(int);
 virtual void rslot03();
 virtual void rslot04(const void *);
 virtual bool rslot05();
 // Existing matched nonvirtual Player row signatures; no new layout or slots.
 Relationship getRelationship(const Player *) const;
 Relationship getRelationship(const Team *) const; // 0x002AD0C6
 float getProductionCostChangeBasedOnUpgradeDiscount(AsciiString) const;
 void becomingLocalPlayer(bool);
 int iterateObjects(int (*)(Object *, void *), void *) const;
 Upgrade *addUpgrade(const UpgradeTemplate *, UpgradeStatusType, int);
 void init(const PlayerTemplate *);
 void update();
 void rva002A99FA();
 void newMap();
 void updateTeamStates();
 void addRadar(bool disableProof);
 bool cloneFrom(Player *other);
 int getSupplyBoxValue();
 bool hasRadar() const;
 bool isPlayerObserver()const;
 void removeRadar(bool);
 void rva002A9E25(float newValue);
 bool rva002AA245() const;
 void rva002AA756(int delta);
 int rva002ABCF0(unsigned char flag, int *out);
 int rva002ABD1D(int kind, int limit);
 void rva002AE252();
 void onUnitCreated(Object *, Object *);
 bool rva002A9CA4(int);
 int getPlayerIndex() const { return m_playerIndex; }
 bool isLocalPlayer() const;
 bool isSkirmishAIPlayer();
 bool rva002A9CB8();
 const ThingTemplate *rva002AA857(int); // 0x002AA857
 void countObjectsByThingTemplate(int, const ThingTemplate *const *, bool, int *, bool) const; // 0x002AB0C5
 Object *findClosestObjectToPosWithValidLivingWorldArmyID(const void *) const; // 0x002AB22A
 bool hasScience(ScienceType) const; // 0x002AB7D5
 // Declared where the unit included STLport's <vector> first; Player.h itself includes no STL header.
#ifdef _STLP_INTERNAL_VECTOR_H
 bool hasAnyRequiredSciences(const _STL::vector<ScienceType> &) const; // 0x002AB7FD
 void rva002AC425(const _STL::vector<int> &); // 0x002AC425
#endif
 bool rva002AB87D(const UpgradeTemplate *) const; // 0x002AB87D
 bool rva002AB894(const Rva002AB894List &) const; // 0x002AB894
 void rva002ABAA6(); // 0x002ABAA6
 void rva002AD1FD(); // 0x002AD1FD
 void rva002AF614(void *); // 0x002AF614
 // Zero Hour inline accessors of the members proven below; retail inlines them.
 const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
 NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
 PlayerType getPlayerType() const { return m_playerType; }
 unsigned int getPlayerMask() const { return 1 << m_playerIndex; }
 int getPlayerColor() const { return m_color; }
 Team *getDefaultTeam() const { return m_defaultTeam; }
 void setCanBuildUnits(bool canProduce) { m_canBuildUnits = canProduce; }
 bool getCanBuildUnits() const { return m_canBuildUnits; }
 // Further matched Player rows, as their decorated names state.
 void accumulateRTSBattleStatsIntoLivingWorldScoreKeeper(); // 0x002A9994
 void setPlayerType(PlayerType, bool); // 0x002A9A18
 void addCommandPoints(Rva002A7588In *); // 0x002A9B35
 void removeCommandPoints(Rva002A7588In *); // 0x002A9B58
 void onStructureConstructionComplete(Object *, Object *, bool); // 0x002A9D02
 int ScaleMoney(int); // 0x002A9E36
 bool hasPrereqsForScience(ScienceType) const; // 0x002A9EAC
 bool rva002A9ED9(const SpecialPowerTemplate *); // 0x002A9ED9
 unsigned char rva002AA00C(ThingTemplate *, int); // 0x002AA00C
 Upgrade *findUpgrade(const UpgradeTemplate *); // 0x002AA031
 bool doesObjectQualifyForBattlePlan(Object *) const; // 0x002AA0DE
 void getCurrentSelectionAsAIGroup(AIGroup *); // 0x002AA164
 void onStructureCreated(Object *, Object *); // 0x002AA559
 bool addSkillPointsForDamage(Object *, const Object *, float); // 0x002AA5E1
 bool addSkillPointsForKill(const Object *, const Object *); // 0x002AA6DE
 void deleteUpgradeList(); // 0x002AA7E6
 bool rva002AA8EF(const UpgradeTemplate *) const; // 0x002AA8EF
 void disableRadar(); // 0x002AAA65
 void enableRadar(); // 0x002AAAF9
 void rva002AABBC(); // 0x002AABBC
 void addToBuildList(Object *); // 0x002AAEC5
 void addToPriorityBuildList(const AsciiString &, Coord3D *, float); // 0x002AAF72
 void healAllObjects(); // 0x002AB06A
 int countBuildings(); // 0x002AB10F
 bool rva002AB260(bool) const; // 0x002AB260
 bool rva002AB295(BfmeFixedStorage0004543D, bool) const; // 0x002AB295
 bool rva002AB2D9(BfmeTab1026 *, bool) const; // 0x002AB2D9
 bool rva002AB312() const; // 0x002AB312
 bool rva002AB341(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D) const; // 0x002AB341
 bool rva002AB390(BfmeTab1026 *) const; // 0x002AB390
 bool hasAnyObjects(bool) const; // 0x002AB3C5
 bool rva002AB3FA() const; // 0x002AB3FA
 void doBountyForKill(const Object *, const Object *); // 0x002AB63D
 bool rva002AB82D(CreateAHeroData *) const; // 0x002AB82D
 bool rva002AB855(CreateAHeroData *) const; // 0x002AB855
 void onPowerBrownOutChange(bool); // 0x002AB8D0
 void rva002AB8FB(Object *, bool); // 0x002AB8FB
 void setUnitsVisionSpied(bool, int); // 0x002ABA3D
 void rva002ABA9B(); // 0x002ABA9B
 void rva002ABAB3(); // 0x002ABAB3
 void setDefaultTeam(); // 0x002ABC7E
 void removeTeamFromList(TeamPrototype *); // 0x002ABD48
 void setObjectsEnabled(const AsciiString &, bool); // 0x002ABD93
 bool allowedToBuild(const ThingTemplate *) const; // 0x002ABE24
 bool isCapableOfPurchasingScience(ScienceType) const; // 0x002ABE86
 ScienceAvailabilityType getScienceAvailabilityTypeFromString(const AsciiString &); // 0x002ABEC9
 bool canBuild(const ThingTemplate *) const; // 0x002ABEF1
 bool rva002AC43F(int *); // 0x002AC43F
 bool rva002AC4D4(int *); // 0x002AC4D4
 Object *findNaturalCommandCenter(); // 0x002AC60A
 Object *rva002AC629(); // 0x002AC629
 void rva002AC673(); // 0x002AC673
 void applyBattlePlanBonusesForObject(Object *) const; // 0x002AC917
 void removeBattlePlanBonusesForObject(Object *) const; // 0x002AC92B
 void applyBattlePlanBonusesForPlayerObjects(const Rva002AA14DBonuses *); // 0x002AC9BF
 void processCreateTeamGameMessage(int, const GameMessage *); // 0x002ACA86
 void processSelectTeamGameMessage(int, GameMessage *); // 0x002ACAFB
 void processAddTeamGameMessage(int, GameMessage *); // 0x002ACBA8
 void setCurrentlySelectedAIGroup(AIGroup *); // 0x002ACC53
 void addAIGroupToCurrentSelection(AIGroup *); // 0x002ACCA3
 void rva002ACD09(void *, int); // 0x002ACD09
 float getProductionCostChangeBasedOnTemplate(const ThingTemplate *, bool); // 0x002ACD6B
 int getProductionCostChangeByObjectFilterID(void *); // 0x002ACE2B
 Relationship getRelationship(const Object *) const; // 0x002AD11E
 void rva002AD25B(const AsciiString &); // 0x002AD25B
 void becomingTeamMember(Object *, bool); // 0x002AD4EC
 int rva002AD629(const AsciiString &); // 0x002AD629
 bool attemptToPurchaseScience(ScienceType); // 0x002AD826
 bool grantScience(ScienceType); // 0x002AD85E
 bool forcePurchaseScience(ScienceType); // 0x002AD883
 void setScienceAvailability(ScienceType, ScienceAvailabilityType); // 0x002AD8C9
 void onUpgradeCompleted(const UpgradeTemplate *, int); // 0x002AD93A
 void onUpgradeRemoved(const UpgradeTemplate *, int); // 0x002AD9FD
 void removeUpgrade(const UpgradeTemplate *, int); // 0x002ADAC3
 void changeBattlePlan(BattlePlanStatus, int, Rva002AA14DBonuses *); // 0x002ADB4F
 void rva002ADC03(Rva004B5A65Owner *, int); // 0x002ADC03
 void addTeamToList(TeamPrototype *); // 0x002AE228
 void rva002AE2ED(Player *); // 0x002AE2ED
 void rva002AE475(void *); // 0x002AE475
 void rva002AE8CF(const AsciiString *, float, int); // 0x002AE8CF
 void rva002AE930(const AsciiString *); // 0x002AE930
 void setUnitsShouldHunt(bool, CommandSourceType); // 0x002AE9B8
 void transferAssetsFromThat(Player *, bool); // 0x002AEA9F
 void garrisonAllUnits(CommandSourceType); // 0x002AEEA7
 void ungarrisonAllUnits(CommandSourceType); // 0x002AF037
 void setUnitsShouldIdleOrResume(bool); // 0x002AF0C5
 void initPlayerUpgrades(); // 0x002AF19B
 void rva002AF236(Xfer *, Rva001FDE3F *); // 0x002AF236
 void rva002AF33B(Xfer *, Rva002AE4C5 *); // 0x002AF33B
 void initFromDict(const Dict *); // 0x002AFCDF
 void initBuildableHeroes(); // 0x002B0B96
 void onStructureUndone(Object *); // 0x0047A69C
 // Called at 9EDA5 and by AptInGameChat::OpenScreen; body 0x002AA231 tests +0x33A and +0x734.
 bool isPlayerActive() const;
private:
 bool addScience(ScienceType); // 0x002AD661, private (A)
public:
 const PlayerTemplate *m_playerTemplate; // init 2AF744 stores its PlayerTemplate argument
 unsigned char m_opaque38[0x4C - 0x38];
 AsciiString m_playerName; // init 2AFA09 clears it and 2AFB60 sets it; the dtor releases it at 2B13E9
 NameKeyType m_playerNameKey; // init 2AFB79 stores NameKeyGenerator::nameToKey's result
 int m_playerIndex; // constructor 2B0F94/97 stores the int argument at +54
 AsciiString m_side; // init 2AFA1D copies the template's side into it; the dtor releases it at 2B13DD
 PlayerType m_playerType; // setPlayerType 2A9A34 stores its PlayerType argument
 unsigned char m_opaque60[0x90 - 0x60];
 Rva003B0D7C m_money; // ctor 2B0FA5 stores the Money vtable 0xBE1AA0 at +0x90 and zeroes +0x94/+0x98
 Upgrade *m_upgradeList; // findUpgrade 2AA031 walks the Upgrade list from here
 int m_radarCount; // addRadar 2AA937 increments it, removeRadar 2AA9DA decrements it
 int m_disableProofRadarCount; // addRadar 2AA943 counts disable-proof radars here
 bool m_radarDisabled; // disableRadar 2AAA7F sets it, enableRadar 2AAB13 clears it
 unsigned char m_opaqueA9[0xAC - 0xA9];
 int m_bombardBattlePlans; // changeBattlePlan 2ADB72 adds the delta of status 1 here
 int m_holdTheLineBattlePlans; // changeBattlePlan 2ADB6A, status 2
 int m_searchAndDestroyBattlePlans; // changeBattlePlan 2ADB62, status 3
 Rva002AA14DBonuses *m_battlePlanBonuses; // 2AC9DA/2AC9F0 store a new Rva002AA14DBonuses
 unsigned char m_opaqueBC[0x278 - 0xBC];
 BuildListInfo *m_pBuildList; // ctor 2B1007 clears it; init 2AF7B1/2AF7C7 deletes the list and clears it
 unsigned char m_opaque27C[0x280 - 0x27C];
 int m_color; // becomingLocalPlayer 2AE017 passes it to RGBColor::setFromInt
 int m_nightColor; // init 2AFA9B; becomingLocalPlayer 2AE1AD picks it before +0x280
 unsigned char m_opaque288[0x2D0 - 0x288];
 // STLport containers are typed where the unit included their STLport header first;
 // elsewhere the same bytes stay opaque, so non-STLport includers compile unchanged.
#ifdef _STLP_INTERNAL_MAP_H
 _STL::map<int, int> m_productionVeterancyLevels; // rva002AD629 2AD643 finds a template's name key in it
#else
 unsigned char m_opaque2D0[0x2DC - 0x2D0];
#endif
 AIPlayer *m_ai; // retail delegates use +0x2DC
 int m_mpStartIndex; // initFromDict 2AFEAE stores Dict::getInt(TheKey_multiplayerStartIndex)
 ResourceGatheringManager *m_resourceGatheringManager; // initFromDict 2B0546/2B055B
 TunnelTracker *m_tunnelSystem; // initFromDict 2B058A/2B059D
 Team *m_defaultTeam; // setDefaultTeam 2ABCC2 stores TeamFactory::findTeam's result
#ifdef _STLP_INTERNAL_VECTOR_H
 _STL::vector<ScienceType> m_sciences; // hasScience 2AB7D5 searches it, addScience 2AD692 appends to it
 _STL::vector<ScienceType> m_sciencesDisabled; // setScienceAvailability 2AD8DA erases from it and appends to it
 _STL::vector<ScienceType> m_sciencesHidden; // setScienceAvailability 2AD8F5/2AD924 erases from it and appends to it
#else
 unsigned char m_opaque2F0[0x314 - 0x2F0];
#endif
 float m_cashBountyPercent; // init 2AF836 stores 0.0f; doBountyForKill 2AB6A1 multiplies the cost by it
 unsigned char m_opaque318[0x32C - 0x318];
 PlayerTeamNode *m_playerTeamPrototypes; // ctor 2B10A6 builds the list sentinel; addTeamToList 2AE228 walks it
 PlayerRelationMap *m_playerRelations; // init 2AF87A/2AF88F store a new PlayerRelationMap
 TeamRelationMap *m_teamRelations; // init 2AF8BB/2AF8C8 store a new TeamRelationMap
 bool m_canBuildUnits; // allowedToBuild 2ABE3D tests it for non-structures
 bool m_canBuildBase; // allowedToBuild 2ABE28 tests it for structures
 bool m_observer; // isPlayerObserver 2AA223 returns it
 bool m_isPreorder; // init 2AF8E3 clears it, initFromDict 2AFF3E sets it
 unsigned char m_opaque33C[0x33D - 0x33C];
 bool m_unitsShouldHunt; // setUnitsShouldHunt 2AE9C1 stores it
 unsigned char m_opaque33E[0x358 - 0x33E];
 int m_358[20]; // setUnitsVisionSpied 2ABA49 counts per player index; init 2AF916 clears 20 entries
 int m_3A8; // setUnitsVisionSpied 2ABA8B stores the mask of nonzero m_358 entries
 int m_3AC; // ctor 2B10AB stores -1; initFromDict 2B06E5 stores Dict::getInt(TheKey_livingWorldPlayerID)
 unsigned char m_opaque3B0[0x6F0 - 0x3B0];
 ObjectID m_6F0; // rva002AC629 2AC659 caches an object's ID here and passes it to findObjectByID
 unsigned char m_opaque6F4[0x708 - 0x6F4];
 Squad *m_squads[10]; // processCreateTeamGameMessage 2ACA94/2ACA9B bound the index by 10 and read it
 Squad *m_currentSelection; // getCurrentSelectionAsAIGroup 2AA164 reads it, the dtor deletes it
 unsigned char m_opaque734[0x758 - 0x734];
};
typedef char PlayerCanonicalSizeCheck[sizeof(Player) == 0x758 ? 1 : -1];
