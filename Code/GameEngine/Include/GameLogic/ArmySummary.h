// Canonical BFME2 ArmySummary. Target facts use RVAs unless marked VA.
// Target facts: constructors 0x0040E3EE/0x0040E96D store VA 0x00C394F0 at +0; destructor 0x0040E499 restores Snapshot VA 0x00BBB554 at 0x0040E523 during base teardown, and ctor cleanup 0x007857FC calls Snapshot's folded destructor 0x0049B47C. These are successive lifetime tables, not competing ArmySummary tables. VA 0x00C394F0 has four code pointers, followed by the ArmySummary literal: deleting destructor 0x0040E81E, empty loadPostProcess 0x000B3FD0, const GetSnapshotName 0x0040E493, xfer 0x0040EE89. The class is polymorphic. Both constructors call 0x00330757 on +4 before installing their own vptr; its vector-base call 0x00211E58 and +0x0C index store establish the 0x10-byte nonvirtual listener base. Destructor cleanup 0x0078582C performs a nullable derived-to-base +4 adjustment before the listener teardown, independently establishing the secondary base. Constructor writes reach +0x64; copy 0x0040E96D, destructor 0x0040E499 and the 0x68-byte swap temporary at 0x003F40EF establish sizeof 0x68. Strings at +0x18/+0x20/+0x64 call StringBase<char> copy 0x000365F0 and release 0x00036410; byte +0x14 and scalar words +0x1C/+0x24..+0x3C/+0x58/+0x5C/+0x60 are copied separately. Initialization at 0x0040E47C/0x0040E481 uses float stores at +0x58/+0x5C. Containers at +0x40/+0x4C have three-pointer 0x0C-byte headers (ctor calls 0x0040E45E/0x0040E46A); copy 0x0040EA2D..0x0040EACE proves 8-byte key/reference entries at +0x40, query 0x0040CC3C proves 4-byte delayed IDs at +0x4C. Their storage stays opaque because the private element views disagree. Methods below follow the ledger spellings and signatures; copy 0x0040E96D, assignment 0x0040EAED and destructor 0x0040E499 remain out of line. No ArmySummary declaration exists in the supplied Zero Hour tree, so unproven field names remain neutral.
#ifndef BFME2_CANONICAL_ARMYSUMMARY_H
#define BFME2_CANONICAL_ARMYSUMMARY_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ArmySummaryEntry;
class INI;
class Object;
class ObjectTypes;
class Rva0040D8D6Listener;
class Rva004F6093Holder;
struct ArmySummaryEntryRef;
struct Coord3D;
struct Rva0040DC56Element;
struct Rva0040DD3ARef;
struct Rva0040E534Input;
struct Rva0040E88BSrc;
enum ObjectID;
template<class T> class Rva001EB984PoolAllocator;
namespace _STL {
template<class T> class allocator;
template<class T, class A> class list;
template<class T, class A> class vector;
}

class Rva0040D8D6List
{
public:
    ~Rva0040D8D6List();
    void forEach(void (Rva0040D8D6Listener::*)(void *, int), void *, int);
    void *field00;
    void *field04;
    void *field08;
    unsigned int field0C;
};

class ArmySummary : public Snapshot, public Rva0040D8D6List
{
public:
    ArmySummary(); // 0x0040E3EE
    ArmySummary(const ArmySummary &); // 0x0040E96D
    ArmySummary &operator=(const ArmySummary &); // 0x0040EAED
    virtual ~ArmySummary(); // 0x0040E499
    virtual void loadPostProcess(); // slot 1, 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // slot 2, 0x0040E493
#else
    virtual void crc(Xfer *xfer);
#endif

    void rva0040C985(int); // 0x0040C985
    float rva0040C9A4(); // 0x0040C9A4
    int rva0040C9F4(); // 0x0040C9F4
    void rva0040CA09(); // 0x0040CA09
    int rva0040CA24(); // 0x0040CA24
    void rva0040CA3A(int); // 0x0040CA3A
    ArmySummaryEntryRef GetEntry(int); // 0x0040CBD7
    bool HasDelayedCarryoverUnitOfTypes(ObjectTypes *); // 0x0040CC3C
    void rva0040CC8F(); // 0x0040CC8F
    bool getSpawnPositions(int, Coord3D *, Coord3D *, bool); // 0x0040CCC6
    bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes *); // 0x0040D701
    Rva0040DD3ARef RemoveEntry(int); // 0x0040DD3A
    void rva0040DE16(); // 0x0040DE16
    void rva0040DED9(); // 0x0040DED9
    void rva0040DF77(); // 0x0040DF77
    void LoadArmyEntry(Rva0040E534Input *, int, _STL::list<Object *, _STL::allocator<Object *> > *, int); // 0x0040E534
    void LoadArmyEntry(Rva0040E534Input *, int, _STL::list<Object *, Rva001EB984PoolAllocator<Object *> > *, int); // 0x0040E534
    ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes *); // 0x0040E589
    Rva0040DD3ARef rva0040E672(int); // 0x0040E672
    Rva0040DD3ARef rva0040E6A4(ArmySummaryEntry *); // 0x0040E6A4
    void GetEntries(_STL::vector<Rva0040DC56Element, _STL::allocator<Rva0040DC56Element> > &); // 0x0040E88B
    int AddArmyEntry(const Rva004F6093Holder &); // 0x0040ECCF
    void MergeUnitsFromArmy(ArmySummary &); // 0x0040ED4F
    static void parseArmyEntry(INI *, void *, void *, const void *); // 0x0040F077
    int AddArmyEntry(const ArmySummaryEntry &); // 0x0040F3D9
    void Load(bool, bool, int); // 0x0040F497

protected:
    virtual void xfer(Xfer *); // slot 3, 0x0040EE89

public:
    bool field14;
    unsigned char pad15[3];
    AsciiString field18;
    int field1C;
    AsciiString field20;
    int field24;
    int field28;
    int field2C;
    int field30;
    int field34;
    int field38;
    int field3C;
    Rva0040E88BSrc *field40;
    Rva0040E88BSrc *field44;
    Rva0040E88BSrc *field48;
    unsigned char field4C[0x0C];
    float field58;
    float field5C;
    int field60;
    AsciiString field64;
};

#endif
