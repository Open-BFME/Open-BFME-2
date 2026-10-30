// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// ??1ParticleSystemFXNugget@@UAE@XZ 104B @0x001E10EA: virtual dtor.
// Installs no derived vptr (novtable view like Helix 0x001E116E and
// FXListAtBonePos 0x001E1096 siblings). Destroys four AsciiString/
// StringBase<char> members at +0x19C +0x198 +0x190 +0x148 (reverse order)
// via folded 0x00036410 then calls base ??1Rva001DFEAABase@@UAE@XZ
// at 0x001DFA48. Identity: ctor 0x001E0AEF installs vtable 0x007DD908 whose
// slot 0 ??_G 0x001E10CE calls here; FieldParse table 0x00BDD428
// (Name@0x148 AttachToBone@0x190 CreateBoneOverride@0x198
// TargetBoneOverride@0x19C); news 0x1BC.

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class BfmeOwnedString4 : private StringBase<char>
{
public:
    ~BfmeOwnedString4() {}
};

class Rva001DFEAABase
{
public:
    virtual ~Rva001DFEAABase();

private:
    unsigned char unknownBaseTail[0x144];
};

// The target dtor has no derived-vptr store. novtable keeps this view's dtor
// body aligned with that fact; no constructor is emitted from this file.
class __declspec(novtable) ParticleSystemFXNugget : public Rva001DFEAABase
{
public:
    virtual ~ParticleSystemFXNugget();

private:
    BfmeOwnedString4 m_name; // +0x148
    unsigned char m_gap14C[0x44]; // +0x14C..+0x18F (count/offset/radius/height/delay/rotates/bools)
    BfmeOwnedString4 m_attachToBone; // +0x190
    unsigned char m_gap194[4]; // +0x194..+0x197
    BfmeOwnedString4 m_createBoneOverride; // +0x198
    BfmeOwnedString4 m_targetBoneOverride; // +0x19C
    unsigned char m_tail1A0[0x1C]; // +0x1A0..+0x1BB (news 0x1BC)
};

typedef char BaseExtent[sizeof(Rva001DFEAABase) == 0x148 ? 1 : -1];
typedef char OwnedFieldExtent[sizeof(BfmeOwnedString4) == 4 ? 1 : -1];

ParticleSystemFXNugget::~ParticleSystemFXNugget() {}
