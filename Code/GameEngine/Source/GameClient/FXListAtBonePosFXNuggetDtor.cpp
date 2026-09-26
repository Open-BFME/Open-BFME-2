// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1FXListAtBonePosFXNugget@@UAE@XZ 56B @0x001E1096: virtual dtor.
// Installs no derived vptr (novtable view like Helix 0x001E116E sibling).
// Destroys AsciiString/StringBase<char> member at +0x14C via folded 0x00036410
// then calls base ??1TransportContainModuleData@@UAE@XZ at 0x001DFA48.
// Identity: ctor 0x001E0A57 installs vtable 0x007DD8F4 whose slot 0 ??_G
// 0x001E107A calls here; FieldParse table 0x00BDD2F8 (FX@0x148 BoneName@0x14C)
// and parse news 0x150 fix the layout; base ctor 0x001DFEAA fixes base extent.

template <typename T>
class StringBase
{
    void *m_data;
    void releaseBuffer();

protected:
    ~StringBase() { releaseBuffer(); }
};

class BfmeOwnedString4 : private StringBase<char>
{
public:
    ~BfmeOwnedString4() {}
};

class TransportContainModuleData
{
public:
    virtual ~TransportContainModuleData();

private:
    unsigned char unknownBaseTail[0x144];
};

// The target dtor has no derived-vptr store. novtable keeps this view's dtor
// body aligned with that fact; no constructor is emitted from this file.
class __declspec(novtable) FXListAtBonePosFXNugget : public TransportContainModuleData
{
public:
    virtual ~FXListAtBonePosFXNugget();

private:
    const char *m_fxName; // +0x148 (trivial; FieldParse FX)
    BfmeOwnedString4 m_boneName; // +0x14C (FieldParse BoneName)
};

typedef char BaseExtent[sizeof(TransportContainModuleData) == 0x148 ? 1 : -1];
typedef char OwnedFieldExtent[sizeof(BfmeOwnedString4) == 4 ? 1 : -1];

FXListAtBonePosFXNugget::~FXListAtBonePosFXNugget() {}
