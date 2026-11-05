// AI: canonical BFME2 interface and target layout.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x002FEA85 calls SubsystemInterface's 0x001B4E63 at 0x002FEA98, stores Snapshot's base table 0x00BBB554 at +0xC (0x002FEAA1), then installs AI's tables 0x00C073D0 at +0 and 0x00C073C0 at +0xC (0x002FEAB3/0x002FEAB9). Destructor 0x002FEBB7 restores those same AI tables at 0x002FEBC9/0x002FEBCF, restores the Snapshot base table at 0x002FEC31 and calls the SubsystemInterface destructor at 0x002FEC38. The base tables describe base construction and destruction, not another AI layout.
// Primary table 0x00C073D0 has the parent's fourteen slots: 0=0x002FED37 (deleting destructor calling 0x002FEBB7), 1=init 0x002FD7D7, 2=SubsystemInterface::loadIniFilesFromLegend 0x001B5384, 3/8/12=0x000B3FD0 (ret), 4/11=0x005CB9FF (false, ret 4), 5=0x0047A699 (false, ret), 6=0x000D43D0 (zero, ret), 7/13=0x0047A69C (ret 4), 9=reset 0x002FEB3A, 10=update 0x002FD7DC. Slots 2-8/11-13 equal the parent's table 0x00BD77A0. The following table 0x00C07408 is installed by the named-list constructor 0x002FED8D at 0x002FEDA9.
// Snapshot table 0x00C073C0 has four slots: 0=0x002FEB32 (subtracts 0xC from this and jumps to 0x002FED37), 1=0x000B3FD0 (empty loadPostProcess), 2=GetSnapshotName 0x002FEB2C, 3=xfer 0x002FE799. Snapshot's registered header supplies this order through BFME_SNAPSHOT_NAME_SLOT.
// Constructor stores the Pathfinder result of 0x002F6E22 at +0x10 (0x002FEB1D), constructs the group list at +0x14 through 0x004EC36C (0x002FEAC0), stores the TAiData result of 0x002FE382 at +0x18 (0x002FEAFB), and clears dwords +0x1C/+0x20 (0x002FEAC5/0x002FEAC9). Destructor calls list cleanup 0x004EC395 on +0x14 at 0x002FEC26. Where STLport's list header precedes this one, +0x14 is Zero Hour's list<AIGroup *> m_groupList, whose ledger rows are the base constructor 0x004EC36C, the base destructor 0x004EC395 and push_back 0x0005548F (createGroup); elsewhere the same four bytes are the opaque field14. sizeof AI is 0x24: constructor writes reach +0x23, and GameEngine::init pushes 0x24 at 0x0022F3A9 and calls AI's constructor at 0x0022F3BE. Zero Hour's AI.h supplies m_pathfinder, m_groupList, m_aiData, m_nextGroupID and m_nextFormationID names and the pathfinder, getAiData and getNextGroupID accessors. AIGroup's constructor increments TheAI+0x1C at 0x0036E534..0x0036E53E.
// Out-of-line ledger rows: createGroup 0x002FEC4B, destroyGroup 0x002FE712, findClosestAlly 0x002FDBC4, findClosestRepulsor 0x002FDC9A, findClosestEnemy 0x002FFFA3 (six arguments), rva002FEEAD 0x002FEEAD, rva002FF8DD 0x002FF8DD, rva002FE193 0x002FE193, getAdjustedVisionRangeForObject 0x002FDD0A, newOverride 0x002FFDC3, addSideInfo 0x002FDB44, parseAiDataDefinition 0x002FFF72, parseSideInfo 0x002FE940, parseAttackPriority 0x002FFD03, parseSkillSet 0x002FE0F1 and parseScience 0x002FD791. Lifetime bodies are declared out of line.
#ifndef BFME2_AI_H
#define BFME2_AI_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class AIGroup;
class AttackPriorityInfo;
class INI;
class Object;
class PartitionFilter;
class Pathfinder;
class PolygonTrigger;
class Rva002FE620;
class TAiData;

class AI : public SubsystemInterface, public Snapshot {
public:
    AI();
    virtual ~AI();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void loadPostProcess() {}
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    Pathfinder *pathfinder() { return m_pathfinder; }
    Pathfinder *pathfinder() const { return m_pathfinder; }
    const TAiData *getAiData() { return m_aiData; }
    const TAiData *getAiData() const { return m_aiData; }
    unsigned int getNextGroupID() { return ++m_nextGroupID; }

    AIGroup *createGroup();
    void destroyGroup(AIGroup *group);
    Object *findClosestAlly(const Object *me, float range, unsigned int qualifiers);
    Object *findClosestRepulsor(const Object *me, float range);
    Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers,
                            const AttackPriorityInfo *info, PartitionFilter *filter, int extra);
    int rva002FEEAD(Object *me, float range, unsigned int qualifiers);
    Object *rva002FF8DD(const PolygonTrigger *area, Object *owner, const AttackPriorityInfo *info);
    static bool rva002FE193(Object *owner, Object *nemesis);
    static float getAdjustedVisionRangeForObject(const Object *object, int factorsToConsider);
    void newOverride();
    void addSideInfo(Rva002FE620 *info);
    static void parseAiDataDefinition(INI *ini);
    static void parseSideInfo(INI *ini, void *instance, void *store, const void *userData);
    static void parseAttackPriority(INI *ini, void *instance, void *store, const void *userData);
    static void parseSkillSet(INI *ini, void *instance, void *store, const void *userData);
    static void parseScience(INI *ini, void *instance, void *store, const void *userData);

    Pathfinder *m_pathfinder;
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<AIGroup *> m_groupList;
#else
    unsigned int field14;
#endif
    TAiData *m_aiData;
    unsigned int m_nextGroupID;
    unsigned int m_nextFormationID;
};

extern AI *TheAI;

#endif
