// LivingWorldLogic: target layout and out-of-line BFME2 declarations.
// Target facts (code addresses are RVAs; tables are VAs):
// Constructor 0x002B93B3 calls SubsystemInterface's 0x001B4E63 at 0x002B93C8, installs Snapshot's 0x00BBB554 at +0xC at 0x002B93D2, and installs observer base tables 0x00C77F44/0x00BFDF68/0x00BFDF8C at +0x10/+0x14/+0x18 at 0x002B9414..0x002B9421. The final stores at 0x002B9432..0x002B944C install 0x00BFE2E4/0x00BFE2D4/0x00BFE2C4/0x00BFE2B4/0x00BFE2A4 at +0/+0xC/+0x10/+0x14/+0x18. Destructor 0x002B964F installs those same five derived tables at 0x002B9668..0x002B9681; its 0x002B97FB..0x002B9808 restores the observer bases, 0x002B9892 restores Snapshot, and 0x002B9899 calls the SubsystemInterface destructor. Base and derived tables describe different lifetime stages, not alternative layouts.
// Table 0x00BFE2E4 has fourteen slots: 0=0x002BAEE5 (deleting destructor calling 0x002B964F); 1=init 0x002B98AD; 2=SubsystemInterface::loadIniFilesFromLegend 0x001B5384; 3/8/12=0x000B3FD0 (ret); 4/11=0x005CB9FF (false, ret 4); 5=0x0047A699 (false); 6=0x000D43D0 (zero); 7/13=0x0047A69C (ret 4); 9=reset 0x002B2535; 10=update 0x002BD9B4. The next word is class-name text, not a fifteenth slot. The registered parent's BFME_SUBSYSTEM_SLOTS form supplies the inherited slots.
// Snapshot's four-slot table 0x00BFE2D4 is 0x002B9647 (subtract 0xC, jump to deleting destructor), loadPostProcess 0x002BC5D3, GetSnapshotName 0x002B9641 (returns the LivingWorldLogic string at 0x00BFE31C), xfer 0x002BC653. The three observer tables each have four callbacks and no destructor slot: +0x10 has ret4, event1_1 0x002B64C7, ret4, ret8; +0x14 has OnRegionChangedOwnership 0x002BA82B, ret12, ret8, ret8; +0x18 has rva002BA3F2 0x002BA3F2, rva002BA654 0x002BA654, 0x002B2A95, ret4. Their bodies receive the adjusted secondary-base this. The Vslots classes below are structural views; equal folded base tables do not identify them with another registered observer type.
// Seven calls to 0x00330757 at 0x002B93DC..0x002B940C construct 0x10-byte listener storage at +0x1C/+0x2C/+0x3C/+0x4C/+0x5C/+0x6C/+0x7C. Their original template/base identities remain unproved, so this storage is opaque. Vector-header construction at 0x002B9453/0x002B94A0/0x002B94BB/0x002B94CA/0x002B952A/0x002B9539/0x002B9548/0x002B9575/0x002B9584 establishes twelve-byte storage at +0x8C/+0xBC/+0xCC/+0xD8/+0x10C/+0x118/+0x124/+0x148/+0x154. List +0xF0 and tree headers +0x130/+0x13C are constructed at 0x002B94F6/0x002B9557/0x002B9566. Element and template types are not inferred from folded constructors.
// GameEngine::init pushes 0x17C at 0x0022F2EF, calls scalar new at 0x0022F2F4 and constructs LivingWorldLogic at 0x0022F307. Constructor stores at 0x002B9458..0x002B95C5 and 0x002B95EE..0x002B9601 establish the scalar offsets and byte flags below, ending at +0x178 (four bytes). The destructor releases the +0x160 reference at 0x002B9712 and clears the +0x178 owner at 0x002B96FF. Scalar names stay neutral. ValidatePlayers 0x002B38D2 establishes the player-pointer role at +0x98; the region-manager construction 0x002B95E5 and store 0x002B95F5 establish +0xB0. The shared xfer block 0x002BB2B7 transfers +0x164 through Xfer's unsigned-int slot +0x78 at 0x002BB404.
// Method names and parameter class/struct spellings below follow the matched LivingWorldLogic ledger rows; lifetime and other rowed bodies are declared without inline definitions. AddDelayedRegionVictory 0x002B9B42 and CheckTurnPhaseTransitions 0x002BD23E have private (AAE) ledger identities; the caller at 0x002BAF01 accesses the former as friend Rva002BAF01, and LivingWorldRegionManager::CheckForBattles 0x0020FDDF calls it at 0x0020FF29.
// Out-of-line method: reset at 0x002B2535.
// Out-of-line method: rva002B27B5 at 0x002B27B5.
// Out-of-line method: rva002B2834 at 0x002B2834.
// Out-of-line method: AdjustArmyMoveTargetPos at 0x002B2858.
// Out-of-line method: armyMoveRequest at 0x002B28B1.
// Out-of-line method: rva002B29BD at 0x002B29BD.
// Out-of-line method: rva002B2A0A at 0x002B2A0A.
// Out-of-line method: rva002B2C12 at 0x002B2C12.
// Out-of-line method: rva002B2E77 at 0x002B2E77.
// Out-of-line method: canBuildUnit at 0x002B3325.
// Out-of-line method: rva002B3416 at 0x002B3416.
// Out-of-line method: rva002B3484 at 0x002B3484.
// Out-of-line method: rva002B37FF at 0x002B37FF.
// Out-of-line method: rva002B3833 at 0x002B3833.
// Out-of-line method: ValidatePlayers at 0x002B38D2.
// Out-of-line method: AdjustArmyTargetLocations at 0x002B3BCF.
// Out-of-line method: MarkTroopForUpgrades at 0x002B3FD3.
// Out-of-line method: CancelTroopUpgrades at 0x002B4026.
// Out-of-line method: rva002B479F at 0x002B479F.
// Out-of-line method: getStartingMoney at 0x002B47B1.
// Out-of-line method: rva002B47C3 at 0x002B47C3.
// Out-of-line method: rva002B4948 at 0x002B4948.
// Out-of-line method: rva002B49A8 at 0x002B49A8.
// Out-of-line method: rva002B4B83 at 0x002B4B83.
// Out-of-line method: EnforceArmyRegionOwnership at 0x002B4C35.
// Out-of-line method: CalcAttackingDirection at 0x002B4F6C.
// Out-of-line method: AutoMarkUnitsForUpgrades at 0x002B5334.
// Out-of-line method: IsCurrentTurnPhaseFinished at 0x002B5390.
// Out-of-line method: rva002B5A5F at 0x002B5A5F.
// Out-of-line method: rva002B5AF7 at 0x002B5AF7.
// Out-of-line method: rva002B5CBB at 0x002B5CBB.
// Out-of-line method: WillPlayerBeEliminatedIfHeOrSheLosesThisRegion at 0x002B5CFB.
// Out-of-line method: ShowEndGameSplashScreen at 0x002B5D36.
// Out-of-line method: event1_1 at 0x002B64C7.
// Out-of-line method: spawnArmy at 0x002B65B7.
// Out-of-line method: rva002B676D at 0x002B676D.
// Out-of-line method: rva002B693F at 0x002B693F.
// Out-of-line method: CreateEmptyGarrisonArmy at 0x002B6A04.
// Out-of-line method: CanMoveArmyMember_internal at 0x002B6B5B.
// Out-of-line method: CanMoveArmyMembers_internal at 0x002B6BCF.
// Out-of-line method: GetArmoryToUpgradeTroop at 0x002B6DC4.
// Out-of-line method: GetNumUpgradeableTroopsInRegionForPlayer at 0x002B6E8A.
// Out-of-line method: AwardOwnershipSetsToPlayers at 0x002B7582.
// Out-of-line method: rva002B768F at 0x002B768F.
// Out-of-line method: rva002B77B2 at 0x002B77B2.
// Out-of-line method: rva002B77F7 at 0x002B77F7.
// Out-of-line method: rva002B783C at 0x002B783C.
// Out-of-line method: PrepareBattleForLoading at 0x002B792E.
// Out-of-line method: processArmyDestroyList at 0x002B7BBB.
// Out-of-line method: RemovePlayer at 0x002B7DE6.
// Out-of-line method: rva002B83E5 at 0x002B83E5.
// Out-of-line method: rva002B84C8 at 0x002B84C8.
// Out-of-line method: rva002B84CD at 0x002B84CD.
// Out-of-line method: UseGenericSpawnArmyForPlayer at 0x002B8660.
// Out-of-line method: spawnCity at 0x002B86F1.
// Out-of-line method: rva002B88EC at 0x002B88EC.
// Out-of-line method: rva002B89E1 at 0x002B89E1.
// Out-of-line method: rva002B8DDE at 0x002B8DDE.
// Out-of-line method: CanMoveArmyMember at 0x002B8F8B.
// Out-of-line method: GetSnapshotName at 0x002B9641.
// Out-of-line method: init at 0x002B98AD.
// Out-of-line method: spawnBuilding at 0x002B99F8.
// Out-of-line method: rva002B9A90 at 0x002B9A90.
// Out-of-line method: AddDelayedRegionVictory at 0x002B9B42.
// Out-of-line method: XferDelayedRegionVictories at 0x002B9BB7.
// Out-of-line method: rva002B9DC7 at 0x002B9DC7.
// Out-of-line method: PrepareRetreats at 0x002B9FDB.
// Out-of-line method: rva002BA3F2 at 0x002BA3F2.
// Out-of-line method: rva002BA654 at 0x002BA654.
// Out-of-line method: OnRegionChangedOwnership at 0x002BA82B.
// Out-of-line method: AddPlayer at 0x002BA8F1.
// Out-of-line method: XferPlayers at 0x002BAA3D.
// Out-of-line method: HandleSwapArmyMembersMessage at 0x002BAC49.
// Out-of-line method: LetAIResolveRegionAwardDispute at 0x002BAF5D.
// Out-of-line method: OnBattleComplete at 0x002BAF7E.
// Out-of-line method: rva002BB15F at 0x002BB15F.
// Out-of-line method: rva002BB2B7 at 0x002BB2B7.
// Out-of-line method: GameLogic_tacticalBattleComplete at 0x002BC1DA.
// Out-of-line method: loadPostProcess at 0x002BC5D3.
// Out-of-line method: xfer at 0x002BC653.
// Out-of-line method: SetUpAutoResolveBattle at 0x002BC971.
// Out-of-line method: rva002BCCFB at 0x002BCCFB.
// Out-of-line method: CheckHeadToHeadBattles at 0x002BCE24.
// Out-of-line method: CheckTurnPhaseTransitions at 0x002BD23E.
// Out-of-line method: EndTurn at 0x002BD36D.
// Out-of-line method: AdvanceTurnPhase at 0x002BD3D6.
// Out-of-line method: rva002BD544 at 0x002BD544.
// Out-of-line method: StartAutoResolveBattle at 0x002BD603.
// Out-of-line method: AutoResolveBattle at 0x002BD64F.
// Out-of-line method: UpdateTurnPhase at 0x002BD6B0.
// Out-of-line method: rva002BD90D at 0x002BD90D.
// Out-of-line method: update at 0x002BD9B4.
// Out-of-line method: logicMessageDispatcher at 0x002BDB4C.
// Out-of-line method: rva0047A69C at 0x0047A69C.
#ifndef BFME2_LIVINGWORLDLOGIC_H
#define BFME2_LIVINGWORLDLOGIC_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

namespace _STL {
template<class T> class allocator;
template<class T, class A> class vector;
}
class LivingWorldRegion;
class LivingWorldPlayer;
class LivingWorldRegionManager;
class Rva004E0632;
class ArmySummaryEntry;
class Rva003F287F;
class Coord2D;
class Rva00318C32Ret;
class SpawnArmy;
class GameMessage;
class LivingWorldBattle;
class Rva002E0687;
class Rva0020E89C;
class Rva003F1241;
struct LivingWorldArmy;
struct Parent0057605D;
struct Parent00575EEA;
struct Parent00575E4E;
struct Rva002B8660Army;
struct Rva002B8660Player;
struct LivingWorldBuildingNuggetSpawnArmy;
struct Rva002B2858Coord;
struct Rva002B6A04Player;
struct Rva002B99F8Request;
struct Rva002B4C35Player;
struct SetupPlayer;
struct SetupArmy;
struct SetupRecord52;
struct SetupSimulation44;
struct Rva002B89BBInfo;
struct Rva002BA8F1Input;
struct Rva002BA8F1Slot;

class LivingWorldLogicVslots10 {
public:
    virtual void slot00(int);
    virtual void event1_1(int);
    virtual void slot02(int);
    virtual void slot03(int, int);
};

class LivingWorldLogicVslots14 {
public:
    virtual void OnRegionChangedOwnership(LivingWorldRegion *, int, int);
    virtual void slot01(int, int, int);
    virtual void slot02(int, int);
    virtual void slot03(int, int);
};

class LivingWorldLogicVslots18 {
public:
    virtual void rva002BA3F2(const Rva002E0687 *);
    virtual void rva002BA654(const Rva002E0687 *, Rva0020E89C *, Rva003F1241 *);
    virtual void slot02(int, int, int);
    virtual void slot03(int);
};

class LivingWorldLogic : public SubsystemInterface, public Snapshot,
    public LivingWorldLogicVslots10, public LivingWorldLogicVslots14, public LivingWorldLogicVslots18 {
public:
    LivingWorldLogic();
    virtual ~LivingWorldLogic();
    virtual void init();
    virtual void reset();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *);
    virtual void event1_1(int);
    virtual void rva002BA3F2(const Rva002E0687 *);
    virtual void rva002BA654(const Rva002E0687 *, Rva0020E89C *, Rva003F1241 *);
    void rva002B29BD();
    int getStartingMoney();
    void rva002B2E77(int);
    void ShowEndGameSplashScreen();
    bool WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(int, int);
    int rva002B479F();
    void rva002B2A0A();
    void rva002B84C8();
    void rva002BB2B7(Xfer *);
    void rva002B8DDE(int);
    void AddPlayer(Rva002BA8F1Input *, bool, int, Rva002BA8F1Slot *);
    void logicMessageDispatcher(GameMessage*,void*);
    void rva0047A69C(const AsciiString &name);
    virtual void OnRegionChangedOwnership(LivingWorldRegion *region, int oldOwnerID, int newOwnerID);
    const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region);
    void UpdateTurnPhase();
    void AdjustArmyTargetLocations();
    void PrepareRetreats();
    void CheckHeadToHeadBattles();
    void ValidatePlayers();
    void rva002B693F(void *keys);
    void rva002B9DC7();
    void rva002BB15F();
    void RemovePlayer(LivingWorldPlayer*);
    unsigned int rva002B77B2();
    unsigned int rva002B77F7();
    int rva002B783C(LivingWorldArmy *army, Rva003F287F *from, Rva003F287F *to, Coord2D *direction);
    void rva002B5AF7();
    virtual void update();
    void rva002B768F();
    bool rva002B3484(Parent0057605D*);
    bool rva002B3416(Parent00575EEA*);
    void rva002B676D();
    void rva002B88EC();
    bool rva002B5A5F(Parent00575E4E*);
    bool rva002B4B83();
    bool EndTurn();
    bool AdvanceTurnPhase();
    bool IsCurrentTurnPhaseFinished();
    void processArmyDestroyList();
    void MarkTroopForUpgrades(int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
    void CancelTroopUpgrades(int entryID, LivingWorldArmy *army);
    void StartAutoResolveBattle(int battle);
    void rva002BD90D(unsigned int flags, int battle);
    bool rva002B89E1(int battle);
    void rva002BD544(int campaign);
    void rva002B84CD(int campaign);
    void rva002B47C3();
    void rva002B83E5();
    void rva002B49A8();
    void AutoResolveBattle(int battle);
    void AutoMarkUnitsForUpgrades();
    void CalcAttackingDirection(const _STL::vector<int, _STL::allocator<int> > &path, Coord2D *direction);
    bool CanMoveArmyMember(LivingWorldArmy *army, int entryID, int target);
    void HandleSwapArmyMembersMessage(const GameMessage *msg);
    void LetAIResolveRegionAwardDispute(int regionID, const _STL::vector<int, _STL::allocator<int> > &players, unsigned int flags);
    Rva002B8660Army *UseGenericSpawnArmyForPlayer(int a, Rva002B8660Player *player);
    bool CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, bool checkRoom);
    bool CanMoveArmyMembers_internal(LivingWorldArmy *army, const _STL::vector<int, _STL::allocator<int> > &entryIDs, LivingWorldArmy *target, int *commandPoints);
    bool canBuildUnit(LivingWorldBuildingNuggetSpawnArmy *nugget, int token);
    int rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target);
    void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, int player, int *countA, int *countB);
    void EnforceArmyRegionOwnership();
    bool rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target);
    Rva002B2858Coord AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos);
    void armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, int flags);
    void rva002B2834(LivingWorldArmy *army, int flags);
    void XferDelayedRegionVictories(Xfer *xfer);
    void XferPlayers(Xfer *xfer);
    void AwardOwnershipSetsToPlayers();
    void spawnCity(SpawnArmy *city);
    LivingWorldArmy *spawnArmy(SpawnArmy *spawn, Rva002B6A04Player *player, bool flag);
    LivingWorldArmy *CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region);
    void *rva002B4948(void *player, void *region, void *arg);
    void spawnBuilding(const struct Rva002B99F8Request *request);
    bool rva002B5CBB(const struct Rva002B4C35Player *player);
    void GameLogic_tacticalBattleComplete();
    void OnBattleComplete(class LivingWorldBattle *battle);
    void rva002B9A90(int regionID, const _STL::vector<int, _STL::allocator<int> > &players, unsigned int flags);
    void rva002B37FF(class LivingWorldBattle *battle);
    void PrepareBattleForLoading(class LivingWorldBattle *battle);
    void SetUpAutoResolveBattle(const _STL::vector<struct SetupPlayer *, _STL::allocator<struct SetupPlayer *> > *armies, struct SetupPlayer *battleValue, const _STL::vector<struct SetupArmy *, _STL::allocator<struct SetupArmy *> > *units, void *region, _STL::vector<struct SetupRecord52, _STL::allocator<struct SetupRecord52> > *a, _STL::vector<struct SetupSimulation44, _STL::allocator<struct SetupSimulation44> > *b);
    void rva002BCCFB(class LivingWorldBattle *battle, int a, int b);
    void rva002B3833(LivingWorldBattle*,struct Rva002B89BBInfo*);
    unsigned char field1C[0x70];
    unsigned int field8C[3];
    LivingWorldPlayer *field98;
    int field9C, fieldA0, fieldA4, fieldA8, fieldAC;
    LivingWorldRegionManager *fieldB0;
    bool fieldB4, fieldB5, fieldB6;
    int fieldB8;
    unsigned int fieldBC[3];
    bool fieldC8, fieldC9;
    unsigned int fieldCC[3];
    unsigned int fieldD8[3];
    int fieldE4;
    bool fieldE8, fieldE9;
    int fieldEC;
    unsigned int fieldF0;
    int fieldF4, fieldF8, fieldFC;
    unsigned int field100, field104;
    bool field108, field109, field10A, field10B;
    unsigned int field10C[3];
    unsigned int field118[3];
    unsigned int field124[3];
    unsigned int field130[3];
    unsigned int field13C[3];
    unsigned int field148[3];
    unsigned int field154[3];
    void *field160;
    unsigned int field164;
    bool field168, field169;
    int field16C, field170;
    bool field174, field175, field176, field177;
    void *field178;

private:
    friend class Rva002BAF01;
    friend class LivingWorldRegionManager;
    void AddDelayedRegionVictory(Rva003F287F *, int, unsigned int);
    void CheckTurnPhaseTransitions();
};

extern LivingWorldLogic *TheLivingWorldLogic;

#endif
