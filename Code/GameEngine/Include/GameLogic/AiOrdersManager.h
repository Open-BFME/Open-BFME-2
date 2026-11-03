// Target facts: BFME2 AiOrdersManager, sizeof 0x38, with virtual functions.
// RVA 0x0022F098 allocates 0x38; 0x0022F0AD calls ctor 0x00355B61 and
// 0x0022F0CF registers the result at TheAiOrdersManager (VA 0x00E01E18).
// The ctor calls SubsystemInterface (0x001B4E63) at +0, stores Snapshot's
// VA 0x00BBB554 at +0x0C, then VA 0x00C14E14 at +0 and VA 0x00C14E04 at +0x0C.
// The primary table has 14 slots; slot 0 is deleting dtor RVA 0x00355BBE,
// which calls dtor 0x00355BDA. Slot 9 is reset (0x00355141); all other
// entries equal SubsystemInterface's VA 0x00BD77A0 except init/update's empty
// RVA 0x000B3FD0. The parent's slot names and signatures are inherited.
// The secondary table has four slots: adjusting dtor 0x00355BB6 (this -= 0x0C),
// loadPostProcess 0x000B3FD0, name getter 0x00354EF6, and xfer 0x00355770.
// The getter returns VA 0x00C14DE4, the literal "AiOrdersManager".
// Dtor 0x00355BDA destroys +0x24 then +0x10 via 0x00355257, restores only
// Snapshot's base table at +0x0C, and calls SubsystemInterface's 0x001B4E74.
// That teardown store is a base table, not a second AiOrdersManager table.
// Ctor calls 0x00355B42 at +0x10 and +0x24 establish two 0x14-byte map members;
// reset 0x00355141 clears both. Finders 0x00355155/0x0035516C use +0x10/+0x24.
// Xfer 0x00355770 receives the Snapshot subobject and serializes its +4/+0x18,
// which are complete-object +0x10/+0x24. The member types remain opaque.
// Nonvirtual declarations retain the signatures of the AiOrdersManager ledger
// rows at RVAs 0x00355183, 0x0035519E, 0x003551D3, 0x00355201, 0x0035530F,
// 0x00355358, 0x0035538C, 0x00355472, 0x0035560B, 0x00355664, 0x003557B7,
// 0x003558A3, 0x003558D6, 0x00355949 and 0x003559B5. All bodies stay out of line.
#pragma once
#ifndef CANONICAL_AIORDERSMANAGER_H
#define CANONICAL_AIORDERSMANAGER_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

struct Coord3D;
class CreateAHeroData;
class GroupOrder;
class Rva0036E346;
namespace _STL {
    template<class T> class allocator;
    template<class T, class Allocator> class list;
}

class AiOrdersManager : public SubsystemInterface, public Snapshot
{
public:
    AiOrdersManager();
    virtual ~AiOrdersManager();
    virtual void init();
    virtual void reset();
    virtual void update();

    void clearOrders(int, int);
    void rva0035519E(int);
    void rva003551D3(int);
    void rva00355201(int, void *, GroupOrder *);
    void rva0035530F(int, void *);
    void rva00355358(int, void *);
    void *rva0035538C(const Coord3D &, int,
        const _STL::list<CreateAHeroData *, _STL::allocator<CreateAHeroData *> > *);
    void *rva00355472(const Coord3D &, int, GroupOrder *);
    int cloneOrderForPatrol(int);
    void rva00355664(const Coord3D &, int, GroupOrder *);
    void addOrderToObjectQueues(int, GroupOrder *);
    void registerOrder(int, GroupOrder *);
    void rva003558D6(int, Rva0036E346 *, int, const Coord3D &, float, bool);
    void rva00355949(int, Rva0036E346 *, const Coord3D &, bool, bool);
    void rva003559B5(int, Rva0036E346 *, int);

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
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

private:
    unsigned char field10[0x14];
    unsigned char field24[0x14];
};

typedef char AiOrdersManagerSizeCheck[sizeof(AiOrdersManager) == 0x38 ? 1 : -1];

#endif
