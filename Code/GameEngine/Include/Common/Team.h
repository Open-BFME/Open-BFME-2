// Target facts: TeamPrototype ctor RVA 0x003A3299 stores VA 0x00C1AE94 at +0 (0x003A32C5); dtor RVA 0x003A33CD stores the same table (0x003A33E1), then Snapshot's VA 0x00BBB554 at 0x003A349B. There is one Snapshot base and no MemoryPoolObject base.
// Table VA 0x00C1AE94 has four entries: deleting dtor RVA 0x003A38B1, loadPostProcess 0x000B3FD0, GetSnapshotName() const 0x003A33A1 (returns "TeamPrototype" at VA 0x00C1AEA4), and xfer(Xfer*) 0x003A3E74. Allocations at RVA 0x003A3D16, 0x003A4093 and 0x003A42BA request 0x338 bytes before calls to the ctor.
// Ctor stores prove factory +4, player +8, id +0xC, strings +0x10/+0x14/+0x20/+0x318, flags +0x18, bytes +0x1C/+0x28/+0x31C..0x31E/+0x324, frame +0x320, coordinate +0x328 and list head +0x334; its vector construction proves 32 four-byte strings at +0xAC and memset proves 32 script pointers at +0x2C. The TeamTemplateInfo member at +0x12C spans 0x1EC bytes; its ctor 0x003A26E6 writes byte +0xEA and dwords +0xEC/+0xF0/+0xF4/+0xF8 (prototype +0x216/+0x218/+0x21C/+0x220/+0x224). Retail 0x0026910E tests +0x216, 0x0020639C compares +0x218, and priority methods 0x0039D72D..0x0039D75E use +0x21C/+0x220/+0x224. Zero Hour Common/Team.h supplies their corresponding member names and the matching ID, flag, script, list and accessor names. Rowed methods are declared out of line; iterate_TeamInstanceList retains only Zero Hour's declaration pending a shared iterator ABI.
#pragma once

#ifndef BFME2_COMMON_TEAM_H
#define BFME2_COMMON_TEAM_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT)
#error TeamPrototype requires Snapshot's lowercase methods and const name getter
#endif

class AsciiString;
class BfmeFixedStorage0004543D;
class BfmeTab1026;
struct Coord3D;
class Dict;
class Object;
class Player;
class Rva0039D769;
class Script;
class Team;
class TeamFactory;
class ThingTemplate;
template <int N> class BitFlags;
template <class T> class DLINK_ITERATOR;

class TeamPrototype : public Snapshot
{
public:
    TeamPrototype(TeamFactory *, const AsciiString &, const AsciiString &, Player *, bool, Dict *, int);
    void addToLists();
    void rva003A0CD1();
    void rva003A2C0D(Player *, const AsciiString &, bool, Dict *);
    void increaseAIPriorityForSuccess();
    void decreaseAIPriorityForFailure();
    void rva0039D747(int);
    void rva0039D754(int);
    void rva003A0D0A();
    void addUnitInfo(const Rva0039D769 &);
    void rva003A0E08(const Rva0039D769 &);
    Script *getGenericScript(int, AsciiString *);
    bool evaluateProductionCondition();
    void updateState();
    void teamAboutToBeDeleted(Team *);
    Team *findTeamByID(unsigned int);
    int countTeamInstances();
    void countObjectsByThingTemplate(int, const ThingTemplate *const *, bool, int *, bool) const;
    int countBuildings();
    int countObjects(BitFlags<116>, BitFlags<116>);
    void healAllObjects();
    int rva0039ED9C(int (*)(Object *, void *), void *);
    bool rva0039EDE1(bool);
    bool rva0039EE21(BfmeFixedStorage0004543D, bool);
    bool rva0039EE70(BfmeTab1026 *, bool);
    bool hasAnyUnits() const;
    bool hasAnyBuildings(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);
    bool rva0039EF46(BfmeTab1026 *);
    bool hasAnyObjects(bool);
    bool hasAnyBuildFacility() const;
    void damageTeamMembers(float);
    void moveTeamTo(Coord3D);
    bool isInList_TeamInstanceList(Team *) const;
    void prependTo_TeamInstanceList(Team *);
    void removeFrom_TeamInstanceList(Team *);
    void removeAll_TeamInstanceList(void (*)(Team *));
    DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;

    unsigned int getID() const { return m_id; }
    const AsciiString &getName() const { return *(const AsciiString *)m_opaque14; }
    bool getIsSingleton() const { return (m_flags & 1) != 0; }
    Player *getControllingPlayer() const { return m_owningPlayer; }
    void friend_setOwningPlayer(Player *player) { m_owningPlayer = player; }
    Team *getFirstItemIn_TeamInstanceList() const { return m_dlinkhead_TeamInstanceList; }

protected:
    virtual ~TeamPrototype();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *);

public:
    TeamFactory *m_factory;
    Player *m_owningPlayer;
    unsigned int m_id;
    unsigned char m_opaque10[4];
    unsigned char m_opaque14[4];
    int m_flags;
    bool m_productionConditionAlwaysFalse;
    unsigned char m_pad1D[3];
    unsigned char m_opaque20[4];
    Script *m_productionConditionScript;
    bool m_retrievedGenericScripts;
    unsigned char m_pad29[3];
    Script *m_genericScriptsToRun[32];
    unsigned char m_opaqueAC[0x80];
    unsigned char m_opaque12C[0x216 - 0x12C];
    bool m_attackCommonTarget;
    unsigned char m_pad217;
    int m_maxInstances;
    int m_productionPriority;
    int m_productionPrioritySuccessIncrease;
    int m_productionPriorityFailureDecrease;
    unsigned char m_opaque228[0x2C4 - 0x228];
    int m_2C4;  // stored by TeamFactory::initTeamForTacticalAI 0x003A2FD4
    unsigned char m_opaque2C8[0x2D8 - 0x2C8];
    int m_2D8;  // stored by 0x003A2FD4; read by AITacticsGenerator 0x005059A1 and 0x00505A56 through Team+0x30
    unsigned char m_opaque2DC[0x318 - 0x2DC];
    unsigned char m_opaque318[4];
    bool m_field31C;
    bool m_field31D;
    bool m_field31E;
    unsigned char m_pad31F;
    unsigned int m_frame320;
    bool m_field324;
    unsigned char m_pad325[3];
    float m_coordinate328[3];
    Team *m_dlinkhead_TeamInstanceList;
};

typedef char TeamPrototypeSizeCheck[sizeof(TeamPrototype) == 0x338 ? 1 : -1];

#endif
