// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /Oy- /arch:SSE /Ob2 /EHsc /MD /DBFME_ASCII_DTOR_DECL
// stlport
// Native21AF1C..21AF7E retains EBP; this complete owner declaration is
// copied from Rva00219B9EAccessor.cpp to keep the class ABI identical while
// using the native frame-pointer setting only for this lookup.
#include "ascii_string.h"
typedef int Int;
typedef unsigned int UnsignedInt;

struct IntVec { int *m_start; int *m_finish; int *m_end; };
struct Elem16 { char m_data[16]; };
struct Vec16 {
    Elem16 *m_start;
    Elem16 *m_finish;
    Elem16 *m_end;
};

// Layout copied from the owned175B constructor's measured record; it is
// also the WB-named GetViewInfo fallback, with a trivial destructor.
struct Rva002195E6Group {
 float value00, value04, value08, value0C, value10; unsigned int untouched14;
};
class Rva002195E6 {
public: __declspec(nothrow) Rva002195E6();
private:
 Rva002195E6Group group00, group18, group30, group48;
 float value60, value64; unsigned int word68;
};

// The hero's class and subclass indices (WB asserts name the argument hero).
class CreateAHeroHero
{
public:
    char m_00[0x0C];
    UnsignedInt m_classIndex;       // +0x0C
    UnsignedInt m_subClassIndex;    // +0x10
};

class CreateAHeroManager
{
public:
    class CreateAHeroSubClass
    {
    public:
        void *rva0021C9A6(Int blingKey, UnsignedInt index);                // 0x0021C9A6, bling name tag
        const AsciiString *rva0021C970(Int blingKey, UnsignedInt index);   // 0x0021C970, bling desc tag
        Int GetAwardNameKey(UnsignedInt index) const;     // 0x00219B62
        Int GetStatNameKey(UnsignedInt index) const;      // 0x00219B80

        AsciiString m_nameTag;                  // +0x00
        AsciiString m_descTag;                  // +0x04
        AsciiString m_imageName;                // +0x08
        AsciiString m_buttonImageName;          // +0x0C
        Int m_10;
        Int m_14;
        Int m_18;
        Int m_spendableAttributePoints;         // +0x1C
        AsciiString m_upgradeName;              // +0x20
        char m_24[0x30 - 0x24];
        IntVec m_awardNameKeys;                 // +0x30
        IntVec m_statNameKeys;                  // +0x3C
        char m_48[0x58 - 0x48];
        Int m_58;                               // +0x58
        char m_5C[0x64 - 0x5C];
        Int m_preferedFaction;                  // +0x64
        char m_68[4];                          // +0x68 faction mask
        Rva002195E6 m_viewInfo;                 // +0x6C measured view record
    };

    struct SubClassVec {
        CreateAHeroSubClass *m_start;
        CreateAHeroSubClass *m_finish;
        CreateAHeroSubClass *m_end;
    };

    class CreateAHeroClass
    {
        friend class CreateAHeroManager;
    public:
        const CreateAHeroSubClass *rva0021AF1C(const AsciiString &name);
        Int rva00219CDF(UnsignedInt subClassIndex);
        Int rva00219CF6(UnsignedInt subClassIndex);
        Int rva00219D0D(UnsignedInt subClassIndex);
        Int rva00219D3B(UnsignedInt subClassIndex);
        Int GetSubClassSpendableAttributePoints(UnsignedInt subClassIndex);
        Int GetPreferedFaction(UnsignedInt subClassIndex);
        const AsciiString &GetButtonImageName(UnsignedInt subClassIndex);
        const AsciiString &GetSubClassUpgradeName(UnsignedInt subClassIndex);
        Int GetStatCount(UnsignedInt subClassIndex);
        Int GetAwardCount(UnsignedInt subClassIndex);
        const AsciiString &GetSubClassNameTag(UnsignedInt subClassIndex);
        const AsciiString &GetSubClassImageName(UnsignedInt subClassIndex);
        const AsciiString &GetSubClassDescTag(UnsignedInt subClassIndex);
        void *GetFactionMaskType(UnsignedInt subClassIndex);
        Int GetAwardNameKey(UnsignedInt subClassIndex, UnsignedInt index);
        Int GetStatNameKey(UnsignedInt subClassIndex, UnsignedInt index);
        Int GetAttributeMinValue(UnsignedInt attribute, UnsignedInt subClassIndex);
        Int GetAttributeMaxValue(UnsignedInt attribute, UnsignedInt subClassIndex);
        Int GetAttributeDefaultValue(UnsignedInt attribute, UnsignedInt subClassIndex);

        AsciiString m_nameTag;                  // +0x00
        AsciiString m_descTag;                  // +0x04
        AsciiString m_powersTag;                // +0x08
        AsciiString m_imageName;                // +0x0C
        AsciiString m_upgradeName;              // +0x10
        SubClassVec m_subClasses;               // +0x14

    private:
        const CreateAHeroSubClass *rva00219B9E(UnsignedInt subClassIndex) const;   // 0x00219B9E
    };

    struct ClassVec {
        CreateAHeroClass *m_start;
        CreateAHeroClass *m_finish;
        CreateAHeroClass *m_end;
    };

    const Rva002195E6 *GetViewInfo(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const AsciiString &GetClassNameTag(UnsignedInt classIndex);
    const AsciiString &GetClassDescTag(UnsignedInt classIndex);
    const AsciiString &GetClassPowersTag(UnsignedInt classIndex);
    const AsciiString &GetClassImageName(UnsignedInt classIndex);
    const AsciiString &GetSubClassNameTag(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const AsciiString &GetBlingNameTag(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index);
    const AsciiString &GetBlingDescTag(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index);
    const AsciiString &GetSubClassImageName(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const AsciiString &GetSubClassDescTag(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const AsciiString &GetButtonImageName(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const AsciiString &GetButtonImageName(const CreateAHeroHero *hero);
    const AsciiString &GetClassUpgradeName(UnsignedInt classIndex);
    const AsciiString &GetSubClassUpgradeName(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int rva0021A016(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int rva0021A041(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int rva0021A06C(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetSubClassSpendableAttributePoints(UnsignedInt classIndex, UnsignedInt subClassIndex);
    const CreateAHeroSubClass *rva0021A1B6(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetStatCount(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetAwardCount(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int rva00219D52(UnsignedInt classIndex);
    void *GetFactionMaskType(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetAwardNameKey(UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index);
    Int GetStatNameKey(UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index);
    void *GetBling(UnsignedInt blingId);
    Int GetPreferedFaction(UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetSubClassAttributeMinValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetSubClassAttributeMaxValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex);
    Int GetSubClassAttributeDefaultValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex);

private:
    char m_pad[0x14C];
    ClassVec m_classes;                         // +0x14C
    char m_pad3[0x15C - 0x158];
    Vec16 m_blingList;                          // +0x15C
};

typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;
typedef CreateAHeroManager::CreateAHeroSubClass CreateAHeroSubClass;

static __forceinline unsigned SubClassCount(const CreateAHeroManager::SubClassVec *v) { return v->m_finish - v->m_start; }
const CreateAHeroSubClass *CreateAHeroManager::CreateAHeroClass::rva0021AF1C(const AsciiString &name)
{
 const CreateAHeroSubClass *found = 0;
 for (UnsignedInt index = 0; index < SubClassCount(&m_subClasses); ++index) {
  if (name.compareNoCase(m_subClasses.m_start[index].m_upgradeName) == 0)
   found = &m_subClasses.m_start[index];
 }
 return found;
}
