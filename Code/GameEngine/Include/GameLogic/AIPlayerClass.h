// Target facts: AIPlayer's constructor (RVA 0x004F04FC, vptr store 0x004F0508) installs VA 0x00C62DC8 at +0. Its destructor (0x004F07E6) restores that table at 0x004F07F7, calls clearTeamsInQueue (0x004F05D6), then restores Snapshot's VA 0x00BBB554 at 0x004F0809. The latter table is the base teardown table, not a competing AIPlayer table. AIPlayer has a virtual destructor: slot 0 targets its deleting destructor (0x004F111C), which calls 0x004F07E6 and conditionally deletes. Player::setPlayerType pushes 0x78 at 0x002A9A74 before new and the constructor call at 0x002A9A8D; the derived constructor (0x004EF3A3) begins its own fields at +0x78.
// Target fields: constructor 0x004F04FC writes queue heads +4/+8, Player pointer +0x0C, flags +0x10/+0x11, timers +0x14/+0x18/+0x1C/+0x20/+0x24, frame +0x28, difficulty +0x2C, skillset +0x30, three floats +0x34..+0x3C, flag +0x40, float +0x44, two repair IDs +0x48/+0x4C, dozer ID +0x50, three origin floats +0x54..+0x5C, count +0x60, flags +0x64/+0x65 and four-byte fields +0x68/+0x6C/+0x70/+0x74. isSupplySourceAttacked (0x004F1138; stores 0x004F1150/0x004F117C and object-ID store 0x004F124F) proves scan frame +0x6C and attacked ID +0x70; updateBridgeRepair (0x004F418A; timer accesses 0x004F41A2/0x004F41B0) proves bridge timer +0x68. Player::getAiBaseCenter (0x002A9C26) copies +0x34 and reads +0x40. Zero Hour AIPlayer.h supplies corresponding field and method names; +0x74 remains neutral. The out-of-line row named setAIDifficulty (0x00210C87) writes +0x30, not +0x2C.
// Target slots: VA 0x00C62DC8 holds 27 code pointers, ending at the AIPlayer name literal VA 0x00C62E34 returned by slot 2 (0x004F05BA). Snapshot occupies slots 0..3 (destructor, empty post-load 0x000B3FD0, name, xfer 0x004F0DDE). Slots 4..10 target 0x004F1D38, 0x004F4927, 0x000B3FD0, 0x004F4962, 0x004F33EC, 0x004F2464 and 0x004F437E; slots 11..15 target 0x0047A699, 0x000D43D0, 0x0050B5F1, 0x004F2F66 and 0x00210C87. Player queries 0x002A9B7B/0x002A9C0D prove slots 11/13. Slots 16..26 target 0x004F2FC4, 0x004F1653, 0x004F48D8, 0x004F31B6, 0x004F0C85, 0x004F288C, 0x004F35A5, 0x004F3DB1, 0x004F2063, 0x004F1566 and 0x004EF4A1. Ledger rows prove the named signatures; Zero Hour proves newMap, getAiEnemy and selectSkillset, while slot 26 remains neutral. Queue methods are rowed at 0x004F03DF/0x004EF373, 0x004F03EF/0x004EF383, 0x004F040F/0x004F0479, 0x004F042F/0x004F0499 and 0x004F0456/0x004F04C0. Other declarations follow AIPlayer's ledger rows at 0x004F08A8, 0x004F0819, 0x004F1138, 0x004F2ABC, 0x004F2C14, 0x004F1B8C, 0x004F1256, 0x004F09CF, 0x004F0B42, 0x004F13D8, 0x004F19D3, 0x004F29E9, 0x004F1801, 0x004F37B0, 0x004F46A9, 0x004F418A, 0x004F21D5 and 0x004F2BEE.
#pragma once

#ifndef BFME2_AIPLAYERCLASS_H
#define BFME2_AIPLAYERCLASS_H

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../Libraries/Include/Lib/Coord3D.h"

class AsciiString;
class BuildListInfo;
class Object;
class Player;
struct Region2D;
class SpecialPowerTemplate;
class Team;
class TeamInQueue;
class TeamPrototype;
class ThingTemplate;
class Waypoint;
class WorkOrder;
enum GameDifficulty;
enum ObjectID;

// Target fact: the constructor writes the two queue heads after the vptr and before +0x30, which cl
// schedules only for constructed subobjects; as plain pointers it hoists +0x30 above the vptr store.
// Each head reads and assigns as the pointer it holds.
struct AIPlayerQueueHead
{
    AIPlayerQueueHead() : m_head(0) {}
    operator TeamInQueue *() const { return m_head; }
    AIPlayerQueueHead &operator=(TeamInQueue *head) { m_head = head; return *this; }
    TeamInQueue *m_head;
};

class AIPlayer : public Snapshot
{
    friend class Player;
public:
    AIPlayer(Player *player);
    virtual ~AIPlayer();

    virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *pos, int playerNdx, float weaponRadius);
    virtual void update();
    virtual void newMap();
    virtual void onUnitProduced(Object *factory, Object *unit);
    virtual void onStructureProduced(Object *factory, Object *structure);
    virtual void buildSpecificAITeam(TeamPrototype *teamProto, bool priorityBuild);
    virtual void recruitSpecificAITeam(TeamPrototype *teamProto, float recruitRadius, const Coord3D *pos);
    virtual bool isSkirmishAI();
    virtual Player *getAiEnemy();
    virtual bool checkBridges(Object *unit, Waypoint *way);
    virtual void repairStructure(ObjectID structure);
    virtual void selectSkillset(int skillset);

    bool getBaseCenter(Coord3D *pos) const { *pos = m_baseCenter; return m_baseCenterSet; }
    void setAIDifficulty(GameDifficulty difficulty);
    void buildUpgrade(const AsciiString &upgrade);
    void aiPreTeamDestroy(const Team *team);
    bool isSupplySourceAttacked();
    bool isLocationSafe(const Coord3D *pos, const ThingTemplate *thing);
    void guardSupplyCenter(Team *team, int minSupplies);
    static void getPlayerStructureBounds(Region2D *bounds, int playerNdx);

    bool isInList_TeamBuildQueue(TeamInQueue *team) const;
    bool isInList_TeamReadyQueue(TeamInQueue *team) const;
    void prependTo_TeamBuildQueue(TeamInQueue *team);
    void prependTo_TeamReadyQueue(TeamInQueue *team);
    void removeFrom_TeamBuildQueue(TeamInQueue *team);
    void removeFrom_TeamReadyQueue(TeamInQueue *team);
    typedef void (*RemoveAllProc_TeamBuildQueue)(TeamInQueue *team);
    typedef void (*RemoveAllProc_TeamReadyQueue)(TeamInQueue *team);
    void removeAll_TeamBuildQueue(RemoveAllProc_TeamBuildQueue callback = 0);
    void removeAll_TeamReadyQueue(RemoveAllProc_TeamReadyQueue callback = 0);
    void reverse_TeamBuildQueue();
    void flip();
    void clearTeamsInQueue();

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
    virtual void checkReadyTeams();
    virtual void checkQueuedTeams();
public:
    virtual void rva004F48D8();
protected:
    virtual void doUpgradesAndSkills();
    virtual Object *findDozer(const Coord3D *pos);
    virtual void queueDozer();
    virtual bool selectTeamToBuild();
    virtual bool selectTeamToReinforce(int minPriority);
    virtual bool startTraining(WorkOrder *order, bool busyOK, AsciiString teamName);
    virtual bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);
    virtual void vslot26();

    static int getPlayerSuperweaponValue(Coord3D *center, int playerNdx, float radius);
    Object *findFactory(const ThingTemplate *thing, bool busyOK, int *buildIndex);
    bool isPossibleToBuildTeam(TeamPrototype *proto, bool requireIdleFactory, bool &needMoney);
    bool rva004F13D8(TeamPrototype *proto);
    bool dozerInQueue();
    void checkForSupplyCenter(BuildListInfo *info, Object *building);
    void computeCenterAndRadiusOfBase(Coord3D *center, float *radius);
    void queueSupplyTruck();
    void queueUnits();
    void updateBridgeRepair();
    Object *findSupplyCenter(int minSupplies);
    bool rva004F2BEE(int minSupplies);

    AIPlayerQueueHead m_teamBuildQueue;
    AIPlayerQueueHead m_teamReadyQueue;
    Player *m_player;
    bool m_readyToBuildTeam;
    bool m_readyToBuildStructure;
    int m_teamTimer;
    int m_structureTimer;
    int m_teamSeconds;
    int m_buildDelay;
    int m_teamDelay;
    unsigned int m_frameLastBuildingBuilt;
    GameDifficulty m_difficulty;
    int m_skillsetSelector;
    Coord3D m_baseCenter;
    bool m_baseCenterSet;
    float m_baseRadius;
    ObjectID m_structuresToRepair[2];
    ObjectID m_repairDozer;
    Coord3D m_repairDozerOrigin;
    int m_structuresInQueue;
    bool m_dozerQueuedForRepair;
    bool m_dozerIsRepairing;
    int m_bridgeTimer;
    unsigned int m_supplySourceAttackCheckFrame;
    ObjectID m_attackedSupplyCenter;
    unsigned int m_field74;
};

typedef char AIPlayerRetailSize[(sizeof(AIPlayer) == 0x78) ? 1 : -1];

#endif
