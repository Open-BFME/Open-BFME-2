// Target facts: constructor RVA 0x00305933 installs the nine-slot table VA 0x00C078F0 at +0 and clears the int at +4 and bools at +8/+9. W3D constructor 0x00063517 calls it and starts its own fields at +0x0C/+0x10; factory 0x00042004 allocates 0x14 for W3D, establishing a 0x0C manager base with four-byte alignment. Names for these fields and the lock accessors come from Zero Hour GhostObject.h.
// Target facts: destructor 0x0049B47C restores Snapshot table VA 0x00BBB554; manager slot 0 (0x004A10FD) and W3D destructor 0x0006422F call it. The different constructor/destructor tables reflect the empty derived destructor and inlined Snapshot teardown. Slot 2 (0x00305947) returns "GhostObjectManager" at VA 0x00C07914, identifying this class independently of the shared destructor fold.
// Target facts: slots 1/2/3 are loadPostProcess 0x000B3FD0, GetSnapshotName 0x00305947 and xfer 0x0030594D; 4 is empty reset, 5 the +4 setter 0x002B230F, and 6/7/8 are purecall. W3D table VA 0x00BC59B8 resolves 4/5/6/7/8 to 0x00063C48/0x00063537/0x000635AB/0x00063B1E/0x001DB09D. Zero Hour names reset, setLocalPlayerIndex and updateOrphanedObjects; 0x00063B1E returns a GhostObject and pops one Object argument. The walk at 0x0030596C calls slot 8 for the list head (getFirst); W3D's slot 8 returns +0x10. No slots follow: string data starts at VA 0x00C07914 and VA 0x00BC59DC.
#pragma once

#ifndef __BFME2_GHOSTOBJECTMANAGER_H_
#define __BFME2_GHOSTOBJECTMANAGER_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class GhostObject;
class Object;

class GhostObjectManager : public Snapshot
{
public:
    GhostObjectManager();
    virtual ~GhostObjectManager();

    virtual void reset() {}
    virtual void setLocalPlayerIndex(int index) { m_localPlayer = index; }
    virtual void updateOrphanedObjects(int *playerIndexList, int numNonLocalPlayers) = 0;
    virtual GhostObject *addGhostObject(Object *object) = 0;
    virtual GhostObject *getFirst() = 0;

    int getLocalPlayerIndex() const { return m_localPlayer; }
    void lockGhostObjects(bool enableLock) { m_lockGhostObjects = enableLock; }
    void saveLockGhostObjects(bool enableLock) { m_saveLockGhostObjects = enableLock; }

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

    int m_localPlayer;
    bool m_lockGhostObjects;
    bool m_saveLockGhostObjects;
};

extern GhostObjectManager *TheGhostObjectManager;

#endif
