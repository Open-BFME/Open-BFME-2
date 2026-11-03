// Target facts (code addresses are RVAs; tables and strings are VAs): Constructor 0x00268CAC stores 0x00BF9D60 at +0 (0x00268CBA), then constructs twelve-byte vector members at +4 and +0x10 through 0x00211E58 (calls 0x00268CC0/0x00268CCC). AIStateMachine::setGoalTeam and setGoalAIGroup allocate 0x1C bytes at 0x00350436/0x0035046B and call this constructor at 0x00350444/0x00350479. Squad is polymorphic, with one Snapshot base at +0 and no separate MemoryPoolObject storage.
// Table 0x00BF9D60 has four slots, followed by "Squad" at 0x00BF9D70: slot 0 is deleting destructor 0x0026AF6A, which calls 0x0026AF86 and conditionally deletes through 0x0002FD60; slot 1 is the empty RET 0x000B3FD0; slot 2 is getter 0x00268CD6 returning that string; slot 3 is Squad::xfer 0x004D6EC4. Destructor 0x0026AF86 frees +0x10 and +4 (0x0026AF97/0x0026AFAC) and restores Snapshot's 0x00BBB554 at 0x0026AFC1 after member teardown. This is the base lifetime table, not a second Squad table. Snapshot's registered header establishes loadPostProcess, GetSnapshotName and xfer as slots 1/2/3.
// Cache rebuilds 0x004D6CAC/0x004D6CF7 and xfer 0x004D6EC4 establish ObjectID vector +4 and Object* cache +0x10; assignment 0x00351761 calls vector assignments on those offsets. The rowed Squad accessors and contained-members method 0x004D6DF3 retain their ledger spellings. Zero Hour's GeneralsMD GameLogic/Squad.h supplies m_objectIDs, m_objectsCached and the remaining method names; BFME2 callers 0x002ACAFB/0x002ACBA8 pass a bool to getLiveObjects' body 0x004D6D4F, and call clear/add bodies 0x004D6C29/0x004D6C7C. Constructor, destructor and assignment remain out of line.
#pragma once
#ifndef CANONICAL_SQUAD_CLASS_H
#define CANONICAL_SQUAD_CLASS_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include <vector>

class AIGroup;
class Object;
class Team;
enum ObjectID;

class Squad : public Snapshot
{
public:
    Squad() throw();
    virtual ~Squad();
    Squad &operator=(const Squad &);

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

public:
    void addObject(Object *);
    void addObjectID(ObjectID);
    void removeObject(Object *);
    void clearSquad();
    const _STL::vector<Object *> &getAllObjects();
    const _STL::vector<Object *> &getLiveObjects(bool);
    int getSizeOfGroup() const;
    bool isOnSquad(const Object *) const;
    void squadFromTeam(const Team *, bool);
    void squadFromAIGroup(const AIGroup *, bool);
    void aiGroupFromSquad(AIGroup *);
    const _STL::vector<Object *> &getAllObjectsAndRemoveDead();
    const _STL::vector<Object *> &rva004D6CAC();
    void rva004D6DF3(Object *, bool);

    _STL::vector<ObjectID> m_objectIDs;
    _STL::vector<Object *> m_objectsCached;
};

#endif
