// Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
// Constructor 0x00213EEF calls SubsystemInterface 0x001B4E63, stores base tables 0x00BBB554 at +0x0C and 0x00BE5114 at +0x10, then installs 0x00BE5234, 0x00BE5224 and 0x00BE5220 at +0, +0x0C and +0x10. Destructor 0x00214405 installs the same three tables and restores the base tables before calling 0x001B4E74. The constructor is rowed as LivingWorldManager; GameEngine::init allocates 0x2D8 at 0x0022F2A8, calls it at 0x0022F2C0 and registers TheLivingWorldManager at 0x0022F2E7.
// Primary table 0x00BE5234 has 14 slots, followed by the LivingWorldManager string at 0x00BE526C. Its targets are 2146B8, 210D0D, 1B5384, B3FD0, 5CB9FF, 47A699, D43D0, 47A69C, B3FD0, 210D0D, 2123BE, 5CB9FF, B3FD0, 47A69C. Slots 1, 9 and 10 override SubsystemInterface init, reset and update. Slot 0 (0x002146B8) calls the out-of-line destructor 0x00214405.
// Snapshot table 0x00BE5224 has four slots: 0x00214058 subtracts 0x0C and jumps to the deleting destructor; 0x00210F27 uses secondary +0x25C (complete +0x268); 0x00214052 returns the class-name string; 0x00213D93 subtracts 0x0C before calling the complete object's rowed methods. The base's slot-2 name signature is selected below.
// The +0x10 base has one virtual slot and no virtual destructor: table 0x00BE5114 holds 0x001F01E8 (ret 0x10), and destructor 0x00210CC5 only restores that table. The derived table 0x00BE5220 holds 0x00211C68, whose ledger row proves OnSwapArmyMembers' four argument types; it does not use the incoming this pointer. The rowed OnSwapArmyMembers spelling is non-virtual and remains declared separately from slot00.
// The declared non-virtual methods are the LivingWorldManager ledger rows at 0x00210D68, 0x00210F96, 0x00210FC6, 0x0021100E, 0x00211142, 0x00211C68, 0x00212183, 0x0021219E, 0x00213171, 0x002133E0, 0x0021399A, 0x00213C6E, 0x00214060, 0x002140DB, 0x00214156, 0x0021427A and 0x002142EA. The out-of-line constructor has the ledger's LivingWorldManager spelling.
// Field +0x204 is the 0x14-byte Rva00056F61 table: CreateSound 0x0021399A looks names up there, the constructor builds it through 0x00213E11 and the destructor 0x00214405 calls its table destructor 0x002129DD at 0x0021467F. Fields +0x22C and +0x230 are a four-byte owning OpaqueRefElement4 and an int: the matched rows 0x00210FC6 (assigns both) and 0x0021100E (guards the reference, builds the audio event from both and clears it) access them, and the destructor's layout places them between the +0x218 table and the +0x234 buffer.
// Field +0x268 is a four-byte pointer: 0x00210D6B loads it, 0x00210D7A clears it and 0x00210DA4 stores the lookup result. Retail 0x003EFE2A and 0x003EFE50 load that same field from TheLivingWorldManager, then call the rowed LivingWorldRegionEffectsManager::SyncRegion at 0x003EF08B. Other data remains opaque; the 0x2D8 allocation fixes its complete extent.

#pragma once

#ifndef CANONICAL_LIVINGWORLDMANAGER_H
#define CANONICAL_LIVINGWORLDMANAGER_H

// GameEngine::init only allocates and constructs the object, and its AsciiString cannot take this
// header's includes: that one unit defines this first.
#ifdef BFME_LIVINGWORLDMANAGER_ALLOCATION_ONLY

class LivingWorldManager
{
public:
    LivingWorldManager();

private:
    unsigned char m_bytes[0x2D8];
};

#else

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../GameClient/Rva00056F61.h"
#include "../Common/OpaqueRefElement4.h"

struct ArmySwapView;
struct ArmyMemberRangeView;
class Coord2D;
struct Rva00210FC6Ref;
class Rva00210F3D;
class Rva00213D93Target;
class Rva003F9FA9;
class Rva003FAE68Base;
class Rva00402BE3;
class Rva00402EFA;
class LivingWorldRegionEffectsManager;

// Empty for every consumer. The constructor unit defines it as `= 0`: its tables are the bridge's to
// supply, so they name no virtual body (LINK-073).
#ifndef BFME_LIVINGWORLDMANAGER_CTOR_PURE
#define BFME_LIVINGWORLDMANAGER_CTOR_PURE
#endif

class Rva00210CC5
{
public:
    ~Rva00210CC5();
    virtual void slot00(ArmySwapView *, const ArmyMemberRangeView &, ArmySwapView *, const ArmyMemberRangeView &) BFME_LIVINGWORLDMANAGER_CTOR_PURE;
};

class LivingWorldManager : public SubsystemInterface, public Snapshot, public Rva00210CC5
{
public:
    LivingWorldManager();
    virtual ~LivingWorldManager();
    virtual void init() BFME_LIVINGWORLDMANAGER_CTOR_PURE;
    virtual void reset() BFME_LIVINGWORLDMANAGER_CTOR_PURE;
    virtual void update() BFME_LIVINGWORLDMANAGER_CTOR_PURE;
    virtual void slot00(ArmySwapView *, const ArmyMemberRangeView &, ArmySwapView *, const ArmyMemberRangeView &) BFME_LIVINGWORLDMANAGER_CTOR_PURE;

    void SetUpRegionEffectsManager();
    void rva00210F96();
    void rva00210FC6(Rva00210FC6Ref, int);
    void rva0021100E();
    Rva00210F3D *rva00211142(Rva00210F3D *);
    void OnSwapArmyMembers(ArmySwapView *, const ArmyMemberRangeView &, ArmySwapView *, const ArmyMemberRangeView &);
    void rva00212183(void *, void *);
    void rva0021219E(Rva00213D93Target *);
    void CreateBeaconObject(int, const Coord2D *, int);
    void rva002133E0();
    Rva003FAE68Base *CreateSound(const AsciiString &);
    void rva00213C6E(Rva00213D93Target *);
    Rva003F9FA9 *rva00214060(const AsciiString &);
    Rva00402BE3 *rva002140DB(const AsciiString &);
    Rva00402EFA *rva00214156(const AsciiString &);
    void rva0021427A();
    void rva002142EA();

    // The constructor unit alone defines this before including the header: its members build through
    // the rowed constructors with private STL shims real-STLport consumers must not see (LINK-073).
#ifdef BFME_LIVINGWORLDMANAGER_CTOR_MEMBERS
    BFME_LIVINGWORLDMANAGER_CTOR_MEMBERS
#else
    unsigned char m_opaque14[0x204 - 0x14];
    Rva00056F61 m_sounds;
    unsigned char m_opaque218[0x22C - 0x218];
    OpaqueRefElement4 sound22c;
    int owner230;
    unsigned char m_opaque234[0x268 - 0x234];
    LivingWorldRegionEffectsManager *field268;
    unsigned char m_opaque26C[0x2D8 - 0x26C];
#endif

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess() BFME_LIVINGWORLDMANAGER_CTOR_PURE;
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *) BFME_LIVINGWORLDMANAGER_CTOR_PURE;
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *) BFME_LIVINGWORLDMANAGER_CTOR_PURE;
#endif
};

#endif

#endif
