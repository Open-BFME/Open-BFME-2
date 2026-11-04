// Target facts: RVA 0x002BD4E0 allocates 0x80 bytes and 0x002BD4FC calls constructor 0x004FA3C9.
// Constructor 0x004FA3C9 and cleanup 0x004FA2E2 store no vptr: this class has no retail virtual functions or evidenced base.
// Storage below records retail offsets; field labels and AutoResolveUnitVector are neutral ABI-view spellings, not recovered source names.
// The constructor copies the 12-byte player vector at +0 (0x004FA3E1), with 0x34-byte elements (0x004FA45B..0x004FA464).
// It constructs two 12-byte current-unit vectors at +0x0C (0x004FA3E6..0x004FA3FD) and two 12-byte maps at +0x24 (0x004FA402..0x004FA418).
// Vector headers at +0x3C/+0x48/+0x54/+0x60/+0x6C call 0x00211E58 at 0x004FA424/432/43E/44A/456.
// The +0x48 vector holds pointers: 0x004FA4B3 constructs their objects, 0x004FA4C7 appends them, and 0x004FA30C..0x004FA326 destroys them in four-byte steps.
// Its begin/end/capacity words occupy +0x48/+0x4C/+0x50; the destructor frees its begin at 0x004FA371.
// Current-unit enumeration 0x004F6234 reads begin/end at +0x0C/+0x10 with 12-byte side stride and four-byte element stride.
// Cleanup 0x004FA383..0x004FA3B5 destroys maps at +0x24/+0x30, current units at +0x0C/+0x18, then players at +0.
// applyResults 0x004F7B6B reads four-byte IDs at +0x60/+0x64 and eight-byte records at +0x6C/+0x70.
// Constructor 0x004FA46C writes zero to +0x7C; 0x004FA59A writes -1 to +0x78. Methods 0x004F81CC and 0x004F61B1 read those respective words.
// Method declarations retain the ledger spellings at 0x004F6187/61B1/6234/68B8/76EA/7B6B/81CC/922C/9635/9658/971E/99CC/9C8E/9D6A/9F39, 0x004FA1F3 and 0x004FA3C9.
// Cleanup 0x004FA2E2 is rowed as ~Rva004FA2E2; the out-of-line destructor declaration prevents an implicit empty destructor.

#pragma once

class ArmySummary;
struct AutoResolveUnitRef;
class Rva004F5FD8;
class Rva004F76EAPred;
class Rva004FA168Storage;
struct PlayerStorage;
struct Pred004F6234;
struct Rva004F9635Rec;
struct Rva0040DC56Element;
struct TreeHintRef00217D4C;

namespace _STL
{
template<class T> class allocator;
template<class T, class Allocator> class vector;
}

struct AutoResolveUnitVector
{
    AutoResolveUnitRef *m_start;
    AutoResolveUnitRef *m_finish;
    AutoResolveUnitRef *m_endOfStorage;
};

class LivingWorldAutoResolveBattle
{
public:
    LivingWorldAutoResolveBattle(const PlayerStorage &);
    ~LivingWorldAutoResolveBattle();

    void rva004F6187();
    void determineWinner();
    void enumerateCurrentUnits(int, Pred004F6234 *);
    void rva004F68B8(unsigned, bool);
    void enumerateReinforcementUnits(int, int, Rva004F76EAPred *);
    void applyResults();
    int rva004F81CC(int);
    void addUnitsForCurrentRound(int);
    void rva004F9635(Rva004F9635Rec *);
    void rva004F9658(Rva004FA168Storage &,
        _STL::vector<Rva0040DC56Element, _STL::allocator<Rva0040DC56Element> > &,
        ArmySummary *, unsigned, bool);
    void rva004F971E();
    void rva004F99CC(bool *);
    void rva004F9C8E(TreeHintRef00217D4C *, int);
    void completeRound();
    void rva004F9F39();
    void buildReinforcementMaps();

    struct PointerRange
    {
        void *field00;
        void *field04;
        void *field08;
    };

    struct OwnedPointerRange
    {
        Rva004F5FD8 **field00;
        Rva004F5FD8 **field04;
        Rva004F5FD8 **field08;
    };

    unsigned char field00[0x0C];
    AutoResolveUnitVector field0C[2];
    unsigned char field24[0x18];
    PointerRange field3C;
    OwnedPointerRange field48;
    PointerRange field54;
    PointerRange field60;
    PointerRange field6C;
    int field78;
    int field7C;
};
