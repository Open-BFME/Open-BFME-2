// Target facts (code addresses are RVAs; tables are VAs): this placeholder calls LivingWorldLogic on TheLivingWorldLogic (0x00DFEF10). Its find bodies 0x002B51F8/0x002B6AEC read player-vector words at +0x8C/+0x90 and player id/name at +0x14/+0x20; GetPlayerAtIndex is 0x002B52A8. LivingWorldLogic's name getter 0x002B9641 returns "LivingWorldLogic" at 0x00BFE31C. GameEngine::init allocates 0x17C at 0x0022F2EF and calls its constructor at 0x0022F307. This is a bounded view of that polymorphic object, not a one-byte class.
// Target facts: constructor 0x002B93B3 calls SubsystemInterface's constructor 0x001B4E63 and installs Snapshot's base table 0x00BBB554 at +0xC, then derived tables 0x00BFE2E4/0x00BFE2D4 at +0/+0xC and observer tables 0x00BFE2C4/0x00BFE2B4/0x00BFE2A4 at +0x10/+0x14/+0x18. Destructor 0x002B964F installs the same derived tables before restoring base tables. The primary table has 14 inherited slots; Snapshot has destructor, loadPostProcess (0x002BC5D3), GetSnapshotName (0x002B9641), xfer (0x002BC653). The observer tables each have four callbacks without a destructor. Their subobjects and seven 0x10-byte listener blocks (+0x1C through +0x7C) remain opaque here; no observer conversions or lifetime definitions are supplied.
// Target facts: remaining nonvirtual declarations follow matched ledger bodies at 0x002B2579, 0x002B2B2D, 0x002B2B3F, 0x002B2B94, 0x002B3187, 0x002B323C, 0x002B35F7, 0x002B3669, 0x002B36F3, 0x002B3740, 0x002B38F7, 0x002B39CF, 0x002B488E, 0x002B4929, 0x002B5256, 0x002B85EC, 0x002B8D06, 0x002B8DFC. All rowed calls remain out of line. Finds 0x002B51F8/0x002B6AEC establish the player pointer range at +0x8C/+0x90; constructor 0x002B9453 initializes its twelve-byte header. setLocal 0x002B38F7 establishes the player pointer at +0x98. Constructor 0x002B95E5 calls LivingWorldRegionManager at 0x0021042D and stores it at +0xB0 at 0x002B95F5; 0x002B9487..0x002B949A establish byte flags +0xB4/+0xB5/+0xB6 and dword +0xB8. The dword at +0xF4 is initialized at 0x002B95FB and read at 0x005E9141. The +0xFC dword is initialized at 0x002B9601 and loaded by row 0x003F1AFF. Field names remain neutral.
#ifndef BFME2_RVA002BA8F1LOGIC_H
#define BFME2_RVA002BA8F1LOGIC_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include Rva002BA8F1Logic.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error Rva002BA8F1Logic requires Snapshot's name slot.
#endif
#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT)
#error Rva002BA8F1Logic requires lowercase Snapshot slots and the const name getter.
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace _STL {
template<class T> class allocator;
template<class T, class A> class vector;
}
class Rva002E2903Player;
class Rva0040D701ArmySummary;
class LivingWorldRegionManager;
class ModuleData;
struct Rva002B2579Result;
struct Rva002B3740Item;
struct Rva002B3187Elem;
struct Rva002B488EResult;
struct Rva002B85ECFilter;

class Rva002BA8F1Logic : public SubsystemInterface, public Snapshot
{
public:
    virtual ~Rva002BA8F1Logic();
    Rva002E2903Player *find(int, unsigned int *);
    Rva002E2903Player *find(const AsciiString &, unsigned int *);
    Rva002E2903Player *GetPlayerAtIndex(int);
    Rva002B2579Result *rva002B2579(int);
    Rva002B3740Item *rva002B2B2D();
    bool rva002B2B3F();
    void rva002B2B94();
    Rva002B3187Elem *rva002B3187(int);
    void rva002B323C(_STL::vector<Rva0040D701ArmySummary *, _STL::allocator<Rva0040D701ArmySummary *> > *, int);
    void rva002B35F7();
    bool rva002B3669();
    void rva002B36F3();
    bool rva002B3740();
    void setLocal(Rva002E2903Player *);
    void rva002B39CF();
    Rva002B488EResult *rva002B488E(int);
    Rva002B488EResult *rva002B4929(int);
    int rva002B5256(bool);
    void rva002B85EC(Rva002B85ECFilter *, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *);
    void rva002B8D06(Xfer *, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *);
    void rva002B8DFC(Xfer *, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *);

    unsigned char field10[0x8C - 0x10];
    Rva002E2903Player **field8C;
    Rva002E2903Player **field90;
    Rva002E2903Player **field94;
    Rva002E2903Player *m_98;
    unsigned char field9C[0xB0 - 0x9C];
    LivingWorldRegionManager *m_B0;
    bool m_b4, m_b5, fieldB6;
    unsigned char padB7;
    int fieldB8;
    unsigned char fieldBC[0xF4 - 0xBC];
    int m_xF4;
    unsigned char fieldF8[0xFC - 0xF8];
    int m_FC;
    unsigned char field100[0x17C - 0x100];
};

#endif
