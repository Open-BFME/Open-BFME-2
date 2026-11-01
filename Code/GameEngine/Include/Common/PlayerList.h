// PlayerList target facts (code addresses are RVAs; tables are VAs): constructor 0x002A7F80 calls SubsystemInterface 0x001B4E63 at 0x002A7F94, constructs Snapshot at +0xC with 0x00BBB554 at 0x002A7F9E, then installs primary 0x00BFD618 at 0x002A7FA9 and secondary 0x00BFD604 at 0x002A7FAF. Destructor 0x002A79A9 installs the same derived tables at 0x002A79BC/0x002A79C2, restores Snapshot's base table at 0x002A7A09 and calls SubsystemInterface's 0x001B4E74 at 0x002A7A10; its final 0x00BD77A0 store belongs to the parent. Allocation 0x0022F62F pushes 0x68 before calling operator new at 0x0022F631 and this constructor at 0x0022F644, proving sizeof 0x68. Parent fields are byte +4 and AsciiString +8 (0x001B4E6B/0x001B4E6F). Constructor stores local +0x10 and count +0x14 at 0x002A7FB6/0x002A7FB9, then twenty Player pointers at +0x18 (0x002A7FBC..0x002A7FEE); getNthPlayer 0x002A7A29 bounds at twenty and indexes +0x18; findPlayerWithNameKey 0x002A7A41 reads count +0x14; setLocalPlayer 0x002A7B34 reads/writes +0x10. Zero Hour PlayerList.h proves m_local, m_playerCount, m_players and the three accessor names.
// Target tables: primary 0x00BFD618 has seventeen entries, ending at the PlayerList string at 0x00BFD65C: 0=0x002A7ED5 (deleting destructor calling 0x002A79A9), 1=0x002A7EF1 (init), 2=0x001B5384 (parent loadIniFilesFromLegend), 3/8/12=0x000B3FD0, 4/11=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7/13=0x0047A69C, 9=0x002A7AA0 (reset), 10=0x002A7AB6 (update), 14=0x002A8008 (newGame), 15=0x002A7AE6 (newMap), 16=0x002A7ACE (unnamed operation). Slots 2-8/11-13 equal parent table 0x00BD77A0; parent slots 1/9/10 are purecall. Snapshot table 0x00BFD604 has four entries and a zero terminator: 0=0x002A7ECD (subtracts 0xC, jumps to 0x002A7ED5), 1=0x000B3FD0 (load postprocess), 2=0x002A7A23 (returns PlayerList literal), 3=0x002A7D63 (DoXfer). The registered Snapshot header proves these slots' roles. DoXfer uses a secondary-base receiver: count +8 and array +0xC at 0x002A7D77/0x002A7DB4 correspond to complete-object +0x14/+0x18.
// Out-of-line ledger rows: constructor 0x002A7F80, destructor 0x002A79A9, init 0x002A7EF1, reset 0x002A7AA0, update 0x002A7AB6, newGame 0x002A8008, newMap 0x002A7AE6, rva002A7ACE 0x002A7ACE, getNthPlayer 0x002A7A29, findPlayerWithNameKey 0x002A7A41, Rva002A7A6F 0x002A7A6F, rva002A7AFE 0x002A7AFE, setLocalPlayer 0x002A7B34, updateTeamStates 0x002A7B1C, getPlayerFromMask 0x002A7B91, getEachPlayerFromMask 0x002A7BC9, rva002A7C0B 0x002A7C0B, getPlayersWithRelationship 0x002A7C70, rva002A7D30 0x002A7D30, createClonedAllyFor 0x002A7F2A, rva002A8306 0x002A8306, validateTeam 0x002A851D and DoXfer 0x002A7D63. Their declarations preserve ledger signatures; lifetime bodies stay out of line.
#ifndef BFME2_PLAYERLIST_H
#define BFME2_PLAYERLIST_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include PlayerList.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#ifndef __SNAPSHOT_H_
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

enum NameKeyType;
class MapObject;
class Player;
class Team;

class PlayerList : public SubsystemInterface, public Snapshot {
public:
    PlayerList();
    virtual ~PlayerList();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void newGame();
    virtual void newMap();
    virtual void rva002A7ACE();

    int getPlayerCount() const { return m_playerCount; }
    Player *getLocalPlayer() { return m_local; }
    Player *getNeutralPlayer() { return m_players[0]; }
    Player *getNthPlayer(int index);
    Player *findPlayerWithNameKey(NameKeyType key);
    Player *Rva002A7A6F(int value);
    void rva002A7AFE(void *value);
    void setLocalPlayer(Player *player);
    void updateTeamStates();
    Player *getPlayerFromMask(int mask);
    Player *getEachPlayerFromMask(int &mask);
    int rva002A7C0B(bool flag);
    int getPlayersWithRelationship(int sourceIndex, unsigned int allowedRelationships, bool reverse);
    int rva002A7D30();
    Player *createClonedAllyFor(void *source);
    void rva002A8306(bool forward);
    Team *validateTeam(AsciiString owner, MapObject *object);

    Player *m_local;
    int m_playerCount;
    Player *m_players[20];

protected:
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
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif
};

extern PlayerList *ThePlayerList;

#endif
