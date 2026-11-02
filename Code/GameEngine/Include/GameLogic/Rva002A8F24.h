// Target facts (code addresses are RVAs; table and string addresses are VAs):
// Constructor 0x002A9725 calls SubsystemInterface 0x001B4E63, stores Snapshot's 0x00BBB554 at +0x0C, then 0x00BFDB94 at +0 and 0x00BFDB84 at +0x0C. Destructor 0x002A921B installs the same pair before restoring the base tables at 0x002A92C9 and 0x001B4E74. These are successive base/class lifetime states, not competing class tables. Allocation 0x0022F8FA requests 0x944 bytes and calls this constructor at 0x0022F912.
// Primary table 0x00BFDB94 has fourteen SubsystemInterface slots: 0 = deleting destructor 0x002A93F5, 1 = empty init 0x000B3FD0, 2 = 0x001B5384, 3 = 0x000B3FD0, 4 = 0x005CB9FF, 5 = 0x0047A699, 6 = 0x000D43D0, 7 = 0x0047A69C, 8 = 0x000B3FD0, 9 = reset 0x002A9072, 10 = update 0x002A8E7B, 11 = 0x005CB9FF, 12 = 0x000B3FD0, 13 = 0x0047A69C. Snapshot table 0x00BFDB84 has four slots: deleting thunk 0x002A92EA (this -= 0x0C), empty loadPostProcess 0x000B3FD0, name getter 0x002A92E4 returning "SkirmishAIManager" at 0x00BFDBCC, and xfer 0x002A8C44. The two bases occupy +0..+0x0F. The member constructor called at 0x002A975C receives this+0x10: its stores at 0x002A8D78, 0x002A8DC5, 0x002A8DD8 and 0x002A8E3B prove float +0x850, byte +0x860, float +0x870 and float +0x884. Retail consumers confirm float +0x850 at 0x0033A757 and 0x0026F062, byte +0x860 at 0x004E93D0 and float +0x884 at 0x00573742. Lookup 0x002A8AB1 scans four-byte pointers between +0x914 and +0x918. Other storage stays opaque. The method declarations below retain the ledger spellings and the two existing 0x002A8F24 caller spellings recorded at retail calls 0x0050537A and 0x005052A5.

#ifndef CANONICAL_RVA002A8F24_H
#define CANONICAL_RVA002A8F24_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class Object;
class Player;
class Rva004E9600;
struct Rva002A8AB1Record;
struct Rva002A8AE4Record;
struct Rva002A8B59Data;
struct Rva002A8F24Record;
struct Rva0050535AStore;

class Rva002A8F24 : public SubsystemInterface, public Snapshot
{
public:
    Rva002A8F24(); // 0x002A9725
    virtual ~Rva002A8F24(); // 0x002A921B
    virtual void init(); // 0x000B3FD0
    virtual void reset(); // 0x002A9072
    virtual void update(); // 0x002A8E7B
    virtual void loadPostProcess(); // 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // 0x002A92E4
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer); // 0x002A8C44

    Rva002A8AB1Record *rva002A8AB1(void *owner); // 0x002A8AB1
    Rva002A8AE4Record *rva002A8AE4(void *owner); // 0x002A8AE4
    Rva004E9600 *rva002A8B24(void *owner); // 0x002A8B24
    Rva002A8B59Data *rva002A8B59(void *owner); // 0x002A8B59
    void *rva002A8B73(void *owner, int key); // 0x002A8B73
    void *rva002A8F24(Player *player); // 0x002A8F24
    Rva0050535AStore **rva002A8F24(void *owner); // 0x002A8F24
    Rva002A8F24Record *rva002A8F24Record(void *owner); // 0x002A8F24
    void UnRegister(Object *object); // 0x002A8F56
    void rva002A9365(Object *object); // 0x002A9365
    void findPreSpawnedObjects(); // 0x002A9411
    void *addNewAIForPlayer(Player *player); // 0x002A9476
    void rva002A95F9(); // 0x002A95F9

    unsigned char m_pad10[0x840];
    float field_850;
    unsigned char m_pad854[0x0C];
    bool field_860;
    unsigned char m_pad861[0x0F];
    float field_870;
    unsigned char m_pad874[0x10];
    float field_884;
    unsigned char m_pad888[0x8C];
    Rva004E9600 **field_914;
    Rva004E9600 **field_918;
    unsigned char m_pad91C[0x28];
};

#endif
