// Target facts: BFME2 constructors RVA 0x003F6A3A/0x003F6F0D store VA 0x00C3709C at +0 and 0x00C37088 at +4; destructor RVA 0x003F6A91 restores the same pair before base teardown.
// Primary slots are RVA 0x003F6CDD (virtual deleting destructor), 0x003F4AD8, 0x003F6A8B (returns the class-name literal at VA 0x00C370AC), and 0x003F7023 (DoXfer). The literal ends the four-slot table. This class is polymorphic.
// Secondary slots at VA 0x00C37088 are RVA 0x003F59FE, 0x0050B238, and three 0x0047A69C entries; the first subtracts four from this and jumps to RemoveArmy (0x003F5647). Its registered listener base has five slots and a nonvirtual destructor.
// Constructor stores of VA 0x00C3702C and destructor stores of VA 0x00BBB554 are base lifetime tables: the former precedes the final +4 store and returns during teardown; the latter replaces +0 only after the +0x18 member and +8 list are destroyed.
// The +8 list constructor RVA 0x00330757 initializes three pointer words and +0x0C = -1; its teardown RVA 0x0007FAB3 frees the first pointer. Construction/teardown order proves bases Snapshot, list, listener, with the polymorphic listener placed at +4 and the list at +8.
// Allocation RVA 0x00210143 pushes 0x40 before operator new and constructor 0x003F6A3A. Constructors initialize +0x18 as a vector and four-byte fields +0x24/+0x28/+0x2C/+0x30/+0x34/+0x38/+0x3C; the default constructor uses MOVSS for +0x28/+0x2C and sets +0x38 = -1.
// RVA 0x003F458A and traversal 0x003F498A prove 0x1C-byte side elements at +0x18; 0x003F4D09 reads the pointer at +0x24. DoXfer 0x003F7023 transfers +0x28 as Coord2D and the subsequent words individually. Unproved field identities retain offset names.
// Out-of-line declarations follow ledger RVAs: constructors 0x003F6A3A/0x003F6F0D; destructor 0x003F6A91; accessors/traversals 0x003F4538/458A/459A/45DF/4634/4688/46A8/46C1/46F2/470E/4752/4798/47E6/4831/486C/48EF/48FE/4921/4944/498A/4A46/4AD8/4D09/4DA9/4DEE/4FAA/4FBD/4FD4; mutators 0x003F4E07/5397/5647/5BDB/6727/6DF9 and transfer 0x003F7023. Original names for the other primary-slot implementations remain unresolved.

#ifndef CANONICAL_LIVINGWORLDBATTLE_H
#define CANONICAL_LIVINGWORLDBATTLE_H

namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../Common/LivingWorldBattleListener.h"

#if !defined(BFME_SNAPSHOT_NAME_SLOT) || !defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || !defined(BFME_SNAPSHOT_REFERENCE_XFER)
#error LivingWorldBattle requires the registered Snapshot name and reference-transfer slot surface.
#endif

#include "../Common/Rva00330757Member.h"

struct LivingWorldBattleArmyView;
struct LivingWorldBattlePlayerView;
struct LivingWorldBattleCoord;
struct LivingWorldArmy;
class LivingWorldRegion;
struct Rva003F498AOuter;
struct Rva003F4E07Results;
class Rva003F498ACallback;
class Rva0020E20C;
enum ScienceType;

class LivingWorldBattle : public Snapshot, public Rva00330757Member, public LivingWorldBattleListener
{
public:
    class BattleSide;
    class BattlePlayer;

    LivingWorldBattle();
    LivingWorldBattle(int, int, const _STL::vector<LivingWorldBattleArmyView *, _STL::allocator<LivingWorldBattleArmyView *> > &,
        const _STL::vector<LivingWorldBattlePlayerView *, _STL::allocator<LivingWorldBattlePlayerView *> > &, const LivingWorldBattleCoord &);
    virtual ~LivingWorldBattle();
    virtual void LoadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void DoXfer(Xfer &);
    virtual void onArmyRemoved(void *);

    bool rva003F4538();
    int GetTeamNumberForSide(int);
    int rva003F459A();
    int rva003F45DF();
    Rva003F498AOuter *rva003F4634(void *);
    Rva003F498AOuter *rva003F4688(void *);
    int GetRetreatedPlayerCount(int);
    int GetRetreatedPlayerID(int, int);
    int *rva003F46F2(int, int);
    void rva003F470E(int, int, void *);
    int rva003F4752(void *);
    int rva003F4798(int, int);
    int rva003F47E6(int);
    int rva003F4831();
    bool rva003F486C(int);
    bool rva003F48EF(void *);
    int rva003F48FE(int, int, int);
    int rva003F4921(int, int, int);
    void rva003F4944(Rva003F498ACallback *);
    void rva003F498A(Rva003F498ACallback *);
    void rva003F4A46(int, int, Rva0020E20C *const &);
    void rva003F4AD8();
    void *rva003F4D09();
    void *rva003F4DA9();
    void *rva003F4DEE(void *);
    void ComputeBattleResultsForPlayersAfterAutoBattle(Rva003F4E07Results *);
    int rva003F4FAA(int, void *);
    void *rva003F4FBD(void *);
    int GetResolutionOptions();
    void rva003F5397(int, int, int, int);
    void RemoveArmy(LivingWorldArmy *);
    void rva003F5BDB(void *, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *);
    void RetreatArmiesForPlayer(void *);
    void AddArmy(int, void *);

    Rva003F498AOuter *field18;
    Rva003F498AOuter *field1C;
    Rva003F498AOuter *field20;
    LivingWorldRegion *field24;
    float field28;
    float field2C;
    int field30;
    int field34;
    int field38;
    int field3C;
};

#endif
