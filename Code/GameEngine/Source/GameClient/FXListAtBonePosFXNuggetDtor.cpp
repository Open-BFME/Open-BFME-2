// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// ??1FXListAtBonePosFXNugget@@UAE@XZ 56B @0x001E1096: virtual dtor.
// Installs no derived vptr (novtable view like Helix 0x001E116E sibling).
// Destroys AsciiString/StringBase<char> member at +0x14C via folded 0x00036410
// then calls base ??1Rva001DFEAABase@@UAE@XZ at 0x001DFA48.
// Identity: ctor 0x001E0A57 installs vtable 0x007DD8F4 whose slot 0 ??_G
// 0x001E107A calls here; FieldParse table 0x00BDD2F8 (FX@0x148 BoneName@0x14C)
// and parse news 0x150 fix the layout; base ctor 0x001DFEAA fixes base extent.

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
class __declspec(novtable) FXListAtBonePosFXNugget : public Rva001DFEAABase
{
public:
    virtual ~FXListAtBonePosFXNugget();

private:
    const char *m_fxName; // +0x148 (trivial; FieldParse FX)
    BfmeOwnedString4 m_boneName; // +0x14C (FieldParse BoneName)
};

typedef char BaseExtent[sizeof(Rva001DFEAABase) == 0x148 ? 1 : -1];
typedef char OwnedFieldExtent[sizeof(BfmeOwnedString4) == 4 ? 1 : -1];

FXListAtBonePosFXNugget::~FXListAtBonePosFXNugget() {}
