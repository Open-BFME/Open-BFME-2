// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x005B12C5 calls CreateAHeroData's constructor 0x00409C3D at 0x005B12ED on the same receiver, then installs 0x00C72A80 at 0x005B1308. Destructor 0x005B190D restores that table at 0x005B1921 and calls ~CreateAHeroData (0x00409285) at 0x005B19F3. The parent's constructor and destructor store 0x00C38D88 (0x00409C5D/0x00409297), and its destructor finally stores Snapshot's 0x00BBB554 at 0x00409342. These are successive base tables. AptMyHero is polymorphic, with six slots: 0=0x005B1A50 (deleting destructor calling 0x005B190D at 0x005B1A53), 1=0x000B3FD0, 2=0x00409353, 3=0x00408C11, 4=0x004083FF, 5=0x005B023A (the ledger's slot14). Slots 1..4 are inherited unchanged, including the parent's GetSnapshotName returning "CreateAHeroData"; the six-slot table ends at VA 0x00C72A98 with string data.
// Target layout: CreateAHeroData's store at 0x00409D13 reaches +0x13C, and the derived constructor stores its screen argument at +0x140 (0x005B12F5). Stores at 0x005B130E..0x005B1334 prove dword +0x144, byte +0x148, dword +0x14C, bytes +0x150/+0x151 and dwords +0x154/+0x158. The +0x15C member calls 0x00211E58 at 0x005B133A; GetObjectInfo (0x005B0E9F) reads its three-pointer vector span with eight-byte elements. Float stores at 0x005B1354/0x005B1358 prove +0x168/+0x16C; 0x005B136A sets dword +0x170. Array construction at 0x005B1374 and destruction at 0x005B19D3 use two twelve-byte elements at +0x174. The matched constructor declares these as vectors of ObjectCreationList pointers. The +0x15C vector retains the existing BfmeE8 element spelling; GetObjectInfo views the same eight-byte records as BfmePod8. The range helper preserves the witnessed adjacent float initialization. Store 0x005B1386 clears dword +0x18C. The screen constructor calls this constructor on +0x27C at 0x005142E9 and writes its next member at +0x40C (0x005142EE), bounding AptMyHero to 0x190 bytes. Unknown field meanings retain offset names.
// Out-of-line method rows: constructor 0x005B12C5, destructor 0x005B190D, slot14 0x005B023A, GetObjectInfo 0x005B0E9F, AdjustBling 0x005B0EE6, SetBling 0x005B07C1, SwitchToPendingHero 0x005B1E71, FrameUpdate 0x005B1EE2, BuildBlingData 0x005B1B5E; the rva-prefixed declarations below use their ledger row RVAs and signatures. Lifetime and method bodies are declared only. No separate allocation or copy/assignment body for this class is established.
#ifndef BFME2_APTMYHERO_H
#define BFME2_APTMYHERO_H

#include "../GameLogic/CreateAHeroData.h"
#include <vector>

struct BfmeE8
{
    int a;
    float b;
};
class ObjectCreationList;

struct MyHeroViewRange
{
    MyHeroViewRange() : lo(0), hi(0) {}
    float lo, hi;
};

class AptCreateAHero;
class Object;
struct BfmePod8;
struct Rva005B0473View;

class AptMyHero : public CreateAHeroData
{
public:
    AptMyHero(AptCreateAHero *);
    virtual ~AptMyHero();
    virtual void slot14();

    BfmePod8 *GetObjectInfo(int);
    void AdjustBling(int, int, int);
    void SetBling(int, int, int);
    void SwitchToPendingHero();
    void FrameUpdate();
    void BuildBlingData();
    void rva005B0416(int);
    void rva005B0446();
    Rva005B0473View *rva005B0473();
    void rva005B0487();
    bool rva005B0725();
    void rva005B0923(int);
    void rva005B097F(int);
    int rva005B0A95(int, int);
    int rva005B0E60(const Object *);
    void rva005B0FCD(int);
    void rva005B1019();
    void rva005B1288();
    void rva005B1A6C();
    void rva005B21DA(CreateAHeroData *, bool, int);

public:
    AptCreateAHero *field140;
    CreateAHeroData *field144;
    bool field148;
    int field14C;
    bool field150;
    bool field151;
    int field154;
    int field158;
    _STL::vector<BfmeE8> field15C;
    MyHeroViewRange field168;
    int field170;
    _STL::vector<const ObjectCreationList *> field174[2];
    int field18C;
};

typedef char BfmeAptMyHeroExtent[(sizeof(AptMyHero) == 0x190) ? 1 : -1];

#endif
