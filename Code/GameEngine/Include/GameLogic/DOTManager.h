/* Target facts (addresses are RVAs unless marked VA): constructor 0x0043B6D7 stores VA 0x00C3D5F0 at +0 (0x0043B6EF) and constructs the tree at +4 through 0x0043B69C (0x0043B6EC/0x0043B6F5). Destructor 0x0043B660 stores the same table (0x0043B671), destroys +4 through 0x0043B4B4 (0x0043B67B/0x0043B67E), then restores Snapshot VA 0x00BBB554 (0x0043B686). The restored table belongs to base teardown, not a second DOTManager type. VA 0x00C3D5F0 has four slots: deleting destructor 0x0043B709, empty post-load 0x000B3FD0, const name getter 0x0043B696 and DoXfer 0x0043B920. The getter returns the DOTManager literal immediately following the table at VA 0x00C3D600. This proves the polymorphic Snapshot-derived identity shared with the unregistered Rva0043B660 placeholder.
GameLogic::init pushes 0x10 at 0x002440C0, allocates at 0x002440C2 and calls this constructor at 0x002440D8 without adjusting the returned pointer; it stores the result at GameLogic+0x174 (0x002440E9). The object therefore occupies 0x10 bytes. Tree initialization 0x0043B214 calls header allocation 0x0043B1C9 and clears its count at +4 (0x0043B224), establishing object header pointer +4 and count +8; DoXfer reads both at 0x0043B944/0x0043B9AE. Storage +0x0C..+0x0F remains opaque. Wrappers 0x0043B725/0x0043B72D adjust this by +4 before clear/erase. Ledger rows establish update 0x0043B73D, rva0043B2A4Clear 0x0043B2A4, rva0043B278 0x0043B278, rva0043B8C0 0x0043B8C0 and virtual DoXfer 0x0043B920. Their ObjectID/int/value-pointer signatures are retained; no method body is emitted here. */
#ifndef BFME2_CANONICAL_DOTMANAGER_H
#define BFME2_CANONICAL_DOTMANAGER_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS)
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

enum ObjectID;
class Rva0043B163;

class DOTManager : public Snapshot
{
public:
    DOTManager();
    virtual ~DOTManager();
    // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
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

    void rva0043B725();
    unsigned int rva0043B72D(int);
    void update();
    void rva0043B2A4Clear(ObjectID, int);
    void rva0043B278(ObjectID, int);
    void rva0043B8C0(int, const Rva0043B163 *);

private:
    unsigned char field04[0x0C];
};

#endif
