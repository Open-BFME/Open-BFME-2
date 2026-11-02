// Target facts: RVA 0x0022CA45 calls SubsystemInterface's ctor (0x001B4E63), stores VA 0x00BE25B4 at +0 and constructs vectors at +0x0C/+0x18 through 0x00211E58. Allocation at 0x0022E740 pushes 0x24 before that ctor at 0x0022E755. Base ctor/dtor 0x001B4E63/0x001B4E74 use VA 0x00BD77A0, byte +4 and AsciiString +8; the derived dtor 0x001FF909 restores 0x00BE25B4, destroys both pointer vectors and calls the base dtor at 0x001FF9D0.
// Target facts: VA 0x00BE25B4 has 14 slots (RVAs): 0=0x001FF9E4 (deleting dtor calling 0x001FF909), 1=0x001FF8FB (rowed init), 2=0x001B5384, 3/8/10/12=0x000B3FD0 (ret), 4=0x001FF625 (ret 4), 5=0x001FF354 (Bool), 6=0x000D43D0 (zero), 7/13=0x0047A69C (ret 4), 9=0x001FF5C3, 11=0x005CB9FF (false, ret 4). The next table at VA 0x00BE25EC belongs to ScienceInfo's constructor 0x001FFE39. Lookup 0x001FF3AD reads vector begin/end at +0x0C/+0x10, follows overrides and compares ScienceInfo's key +0x10. The second vector's element identity and member name are unknown. Vector storage uses neutral pointer fields to keep its proven layout independent of the consumer's STL implementation.
// Names: Zero Hour Common/Science.h supplies the query names; BFME2 ledger rows prove findScienceInfo 0x001FF3AD, getSciencePurchaseCost 0x001FF3DC, isScienceGrantable 0x001FF432, getNameAndDescription 0x001FF449, playerHasPrereqsForScience 0x001FF47D (Rva0043D3A8 receiver), rva001FF4D3 0x001FF4D3, isValidScience 0x001FF50D, getInternalNameForScience 0x001FF5F2, friend_lookupScience 0x001FF65D, getScienceFromInternalName 0x001FF725, rva000E7C20SciencePrereqMemo 0x001FFAA1, getPurchasableSciences 0x001FFB64, playerHasRootPrereqsForScience 0x001FFC55, friend_getScienceNames 0x001FFCA3 and friend_parseScienceDefinition 0x001FFF3A. reverse/symbols.csv also binds lookupScience(const char*) const to 0x001FF65D for INI::scanScience (0x00338A8D); this declaration preserves that existing caller spelling. reset/update use the registered parent's slots 9/10; unnamed overrides retain its neutral slot names. Destructor and all rowed methods are declared out of line.
#ifndef BFME2_COMMON_SCIENCESTORE_H
#define BFME2_COMMON_SCIENCESTORE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

namespace _STL {
    template <class T> class allocator;
    template <class T, class A> class vector;
}

enum ScienceType;
class INI;
class Player;
class Rva0043D3A8;
class ScienceInfo;
class UnicodeString;

class ScienceStore : public SubsystemInterface
{
public:
    ScienceStore();
    virtual ~ScienceStore();
    virtual void init();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    virtual void update() {}

    bool isValidScience(ScienceType science) const;
    bool isScienceGrantable(ScienceType science) const;
    bool getNameAndDescription(ScienceType science, UnicodeString &name, UnicodeString &description) const;
    bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType science) const;
    bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
    int getSciencePurchaseCost(ScienceType science) const;
    ScienceType getScienceFromInternalName(const AsciiString &name) const;
    AsciiString getInternalNameForScience(ScienceType science) const;
    void getPurchasableSciences(const Player *player, _STL::vector<ScienceType, _STL::allocator<ScienceType> > &purchasable, _STL::vector<ScienceType, _STL::allocator<ScienceType> > &potentiallyPurchasable) const;
    ScienceType friend_lookupScience(const char *scienceName) const;
    ScienceType lookupScience(const char *scienceName) const;
    static void friend_parseScienceDefinition(INI *ini);
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > friend_getScienceNames() const;
    bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;

private:
    friend class ScienceInfo;
    const ScienceInfo *findScienceInfo(ScienceType science) const;
    bool rva000E7C20SciencePrereqMemo(const Player *player, ScienceType science, void *memo) const;
    ScienceInfo **field0c;
    ScienceInfo **field10;
    ScienceInfo **field14;
    void **field18;
    void **field1c;
    void **field20;
};

typedef char ScienceStoreSizeIs0x24[(sizeof(ScienceStore) == 0x24) ? 1 : -1];

extern ScienceStore *TheScienceStore;

#endif
