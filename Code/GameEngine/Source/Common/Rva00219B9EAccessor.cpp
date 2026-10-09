// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// CreateAHeroManager / CreateAHeroManager::CreateAHeroClass /
// CreateAHeroManager::CreateAHeroSubClass accessors (CreateAHero.cpp in WB).
//
// Identity (target evidence): WorldBuilder's debug build names each body
// (reverse/wb_name_leads.csv) and its callees agree pairwise with retail: every
// manager two-index getter forwards to the CreateAHeroClass getter of the same
// name (GetSubClassNameTag 0x0021B13A -> 0x0021ADF8, GetStatCount 0x00219E74
// -> 0x00219BE1, ...), and every class getter to the CreateAHeroSubClass one.
// Retail's static fallbacks split the owners: "ERROR: Invalid CalssIndex"
// guards the manager's class vector, "ERROR: Invalid SubCalssIndex" the
// class's subclass vector. Bodies WB leaves unnamed keep their address names.
//
// Layout (target evidence): the manager keeps a vector of 32-byte classes at
// +0x14C and the 16-byte bling list at +0x15C (WB assert names m_blingList);
// a class keeps five strings then a vector of 216-byte subclasses at +0x14,
// bounds-checked by 0x00219B9E with signed idiv (cdq), so /O1 keeps idiv.
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")
extern int g_00DFE368;
extern int g_00DFE364;
extern int g_00DFE3E4;
extern int g_00DFE3E0;

typedef int Int;
typedef unsigned int UnsignedInt;

struct IntVec { int *m_start; int *m_finish; int *m_end; };
struct Elem16 { char m_data[16]; };
struct Vec16 {
    Elem16 *m_start;
    Elem16 *m_finish;
    Elem16 *m_end;
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
        char m_68[0xD8 - 0x68];                 // +0x68 faction mask
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
static __forceinline unsigned ClassCount(const CreateAHeroManager::ClassVec *v) { return v->m_finish - v->m_start; }
static __forceinline CreateAHeroClass &ClassAt(CreateAHeroManager::ClassVec *v, unsigned i) { return v->m_start[i]; }

// 0x00219B9E 44B (unnamed in WB): null when the index is past the subclass
// vector, else the subclass. Signed idiv by 216 for the count.
const CreateAHeroSubClass *CreateAHeroClass::rva00219B9E(UnsignedInt subClassIndex) const
{
    const CreateAHeroSubClass *result = 0;
    unsigned int count = SubClassCount(&m_subClasses);
    if (subClassIndex < count)
        result = &m_subClasses.m_start[subClassIndex];
    return result;
}
// 0x00219CDF 23B (unnamed in WB): subclass +0x10 or 0.
Int CreateAHeroClass::rva00219CDF(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_10;
    return 0;
}
// 0x00219CF6 23B (unnamed in WB): subclass +0x14 or 0.
Int CreateAHeroClass::rva00219CF6(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_14;
    return 0;
}
// 0x00219D0D 23B (unnamed in WB): subclass +0x18 or 0.
Int CreateAHeroClass::rva00219D0D(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_18;
    return 0;
}
// 0x00219D3B 23B (unnamed in WB): subclass +0x58 or 0.
Int CreateAHeroClass::rva00219D3B(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_58;
    return 0;
}
// CreateAHeroClass::GetSubClassSpendableAttributePoints, retail 0x00219D24 23B.
Int CreateAHeroClass::GetSubClassSpendableAttributePoints(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_spendableAttributePoints;
    return 0;
}
// CreateAHeroClass::GetPreferedFaction, retail 0x00219C93 24B; -1 on a bad
// index (or eax,-1).
Int CreateAHeroClass::GetPreferedFaction(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (!p)
        return -1;
    return p->m_preferedFaction;
}
// CreateAHeroClass::GetButtonImageName, retail 0x00219CAB 26B.
const AsciiString &CreateAHeroClass::GetButtonImageName(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_buttonImageName;
    return AsciiString::TheEmptyString;
}
// CreateAHeroClass::GetSubClassUpgradeName, retail 0x00219CC5 26B.
const AsciiString &CreateAHeroClass::GetSubClassUpgradeName(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_upgradeName;
    return AsciiString::TheEmptyString;
}
// CreateAHeroClass::GetStatCount, retail 0x00219BE1 31B: size of the
// subclass's stat key vector at +0x3C.
Int CreateAHeroClass::GetStatCount(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_statNameKeys.m_finish - p->m_statNameKeys.m_start;
    return 0;
}
// CreateAHeroClass::GetAwardCount, retail 0x00219C1F 31B: size of the
// subclass's award key vector at +0x30.
Int CreateAHeroClass::GetAwardCount(UnsignedInt subClassIndex)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_awardNameKeys.m_finish - p->m_awardNameKeys.m_start;
    return 0;
}
// CreateAHeroClass::GetSubClassNameTag, retail 0x0021ADF8 94B: the
// subclass's first string, else a function-static error string.
const AsciiString &CreateAHeroClass::GetSubClassNameTag(UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_nameTag;
    return err;
}
// CreateAHeroClass::GetSubClassImageName, retail 0x0021AE56 99B.
const AsciiString &CreateAHeroClass::GetSubClassImageName(UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_imageName;
    return err;
}
// CreateAHeroClass::GetSubClassDescTag, retail 0x0021AEB9 99B.
const AsciiString &CreateAHeroClass::GetSubClassDescTag(UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->m_descTag;
    return err;
}
// CreateAHeroManager::GetClassNameTag, retail 0x0021AF7E 108B.
const AsciiString &CreateAHeroManager::GetClassNameTag(UnsignedInt classIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count)
        return ClassAt(&m_classes, classIndex).m_nameTag;
    return err;
}
// CreateAHeroManager::GetClassDescTag, retail 0x0021AFEA 112B.
const AsciiString &CreateAHeroManager::GetClassDescTag(UnsignedInt classIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count)
        return ClassAt(&m_classes, classIndex).m_descTag;
    return err;
}
// CreateAHeroManager::GetClassPowersTag, retail 0x0021B05A 112B.
const AsciiString &CreateAHeroManager::GetClassPowersTag(UnsignedInt classIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count)
        return ClassAt(&m_classes, classIndex).m_powersTag;
    return err;
}
// CreateAHeroManager::GetClassImageName, retail 0x0021B0CA 112B.
const AsciiString &CreateAHeroManager::GetClassImageName(UnsignedInt classIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count)
        return ClassAt(&m_classes, classIndex).m_imageName;
    return err;
}
// CreateAHeroManager::GetButtonImageName(class, subclass), retail 0x0021B22E
// 116B: forwards to CreateAHeroClass::GetButtonImageName 0x00219CAB.
const AsciiString &CreateAHeroManager::GetButtonImageName(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetButtonImageName(subClassIndex);
    }
    return err;
}
// CreateAHeroManager::GetButtonImageName(hero), retail 0x0021B670 29B: the
// hero's class (+0x0C) and subclass (+0x10) indices, empty for no hero.
const AsciiString &CreateAHeroManager::GetButtonImageName(const CreateAHeroHero *hero)
{
    if (!hero)
        return AsciiString::TheEmptyString;
    return GetButtonImageName(hero->m_classIndex, hero->m_subClassIndex);
}
// CreateAHeroManager::GetSubClassNameTag, retail 0x0021B13A 122B.
const AsciiString &CreateAHeroManager::GetSubClassNameTag(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetSubClassNameTag(subClassIndex);
    }
    return err;
}
// CreateAHeroManager::GetSubClassImageName, retail 0x0021B1B4 122B.
const AsciiString &CreateAHeroManager::GetSubClassImageName(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetSubClassImageName(subClassIndex);
    }
    return err;
}
// CreateAHeroManager::GetSubClassDescTag, retail 0x0021B2A2 122B.
const AsciiString &CreateAHeroManager::GetSubClassDescTag(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetSubClassDescTag(subClassIndex);
    }
    return err;
}
// CreateAHeroManager::GetClassUpgradeName, retail 0x0021A134 41B; callers
// 0x004085A1/0x00409490 copy the result as a string.
const AsciiString &CreateAHeroManager::GetClassUpgradeName(UnsignedInt classIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count)
        return ClassAt(&m_classes, classIndex).m_upgradeName;
    return AsciiString::TheEmptyString;
}
// 0x0021A016 43B (unnamed in WB): forwards to 0x00219CDF.
Int CreateAHeroManager::rva0021A016(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].rva00219CDF(subClassIndex);
    }
    return 0;
}
// 0x0021A041 43B (unnamed in WB): forwards to 0x00219CF6.
Int CreateAHeroManager::rva0021A041(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].rva00219CF6(subClassIndex);
    }
    return 0;
}
// 0x0021A06C 43B (unnamed in WB): forwards to 0x00219D0D.
Int CreateAHeroManager::rva0021A06C(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].rva00219D0D(subClassIndex);
    }
    return 0;
}
// CreateAHeroManager::GetSubClassSpendableAttributePoints, retail 0x0021A097 43B.
Int CreateAHeroManager::GetSubClassSpendableAttributePoints(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetSubClassSpendableAttributePoints(subClassIndex);
    }
    return 0;
}
// 0x0021A1B6 43B (unnamed in WB): the subclass itself, null on a miss.
const CreateAHeroSubClass *CreateAHeroManager::rva0021A1B6(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].rva00219B9E(subClassIndex);
    }
    return 0;
}
// CreateAHeroManager::GetSubClassUpgradeName, retail 0x0021A15D 46B.
const AsciiString &CreateAHeroManager::GetSubClassUpgradeName(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetSubClassUpgradeName(subClassIndex);
    }
    return AsciiString::TheEmptyString;
}
// CreateAHeroManager::GetStatCount, retail 0x00219E74 43B.
Int CreateAHeroManager::GetStatCount(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetStatCount(subClassIndex);
    }
    return 0;
}
// CreateAHeroManager::GetAwardCount, retail 0x00219ED5 43B.
Int CreateAHeroManager::GetAwardCount(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        return base[classIndex].GetAwardCount(subClassIndex);
    }
    return 0;
}
// 0x00219D52 51B (unnamed in WB): the class's subclass count. Retail
// lea eax,[ecx+0x14C] plus sar 5 for the class, then lea ecx,[ecx+eax+0x14]
// plus mov ecx,0xD8/cdq/idiv for the subclasses.
Int CreateAHeroManager::rva00219D52(UnsignedInt classIndex)
{
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroClass *base = m_classes.m_start;
        CreateAHeroClass *inner = &base[classIndex];
        return (int)SubClassCount(&inner->m_subClasses);
    }
    return 0;
}
// CreateAHeroClass::GetFactionMaskType, retail 0x00219C5D 54B: one-time
// memset of g_00DFE364 guarded by g_00DFE368, then subclass +0x68
// unconditionally.
void *CreateAHeroClass::GetFactionMaskType(UnsignedInt subClassIndex)
{
    if (!(*(unsigned char *)&g_00DFE368 & 1)) {
        g_00DFE368 |= 1;
        ji_006291ae(&g_00DFE364, 0, 4);
    }
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    return (char *)p + 0x68;
}
// CreateAHeroManager::GetFactionMaskType, retail 0x00219F8E 85B: same guard
// idiom; a bad class index returns &g_00DFE3E0.
void *CreateAHeroManager::GetFactionMaskType(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    void *fallback = &g_00DFE3E0;
    if (!(*(unsigned char *)&g_00DFE3E4 & 1)) {
        g_00DFE3E4 |= 1;
        ji_006291ae(fallback, 0, 4);
    }
    unsigned int count = ClassCount(&m_classes);
    if (classIndex >= count)
        return fallback;
    CreateAHeroClass *base = m_classes.m_start;
    return base[classIndex].GetFactionMaskType(subClassIndex);
}
// CreateAHeroSubClass::GetAwardNameKey, retail 0x00219B62 30B: award key
// vector at +0x30, 0 on a bad index.
Int CreateAHeroSubClass::GetAwardNameKey(UnsignedInt index) const
{
    unsigned int count = (unsigned int)(((char *)m_awardNameKeys.m_finish - (char *)m_awardNameKeys.m_start) >> 2);
    if (index < count) {
        _ReadWriteBarrier();
        return m_awardNameKeys.m_start[index];
    }
    return 0;
}
// CreateAHeroClass::GetAwardNameKey, retail 0x00219C3E 31B.
Int CreateAHeroClass::GetAwardNameKey(UnsignedInt subClassIndex, UnsignedInt index)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->GetAwardNameKey(index);
    return 0;
}
// CreateAHeroManager::GetAwardNameKey, retail 0x00219F00 54B.
Int CreateAHeroManager::GetAwardNameKey(UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index)
{
    unsigned int count = (unsigned int)(((char *)m_classes.m_finish - (char *)m_classes.m_start) >> 5);
    if (classIndex < count) {
        _ReadWriteBarrier();
        return ((CreateAHeroClass *)((char *)m_classes.m_start + (classIndex << 5)))->GetAwardNameKey(subClassIndex, index);
    }
    return 0;
}
// CreateAHeroSubClass::GetStatNameKey, retail 0x00219B80 30B: stat key
// vector at +0x3C.
Int CreateAHeroSubClass::GetStatNameKey(UnsignedInt index) const
{
    unsigned int count = (unsigned int)(((char *)m_statNameKeys.m_finish - (char *)m_statNameKeys.m_start) >> 2);
    if (index < count) {
        _ReadWriteBarrier();
        return m_statNameKeys.m_start[index];
    }
    return 0;
}
// CreateAHeroClass::GetStatNameKey, retail 0x00219C00 31B.
Int CreateAHeroClass::GetStatNameKey(UnsignedInt subClassIndex, UnsignedInt index)
{
    const CreateAHeroSubClass *p = rva00219B9E(subClassIndex);
    if (p)
        return p->GetStatNameKey(index);
    return 0;
}
// CreateAHeroManager::GetStatNameKey, retail 0x00219E9F 54B.
Int CreateAHeroManager::GetStatNameKey(UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index)
{
    unsigned int count = (unsigned int)(((char *)m_classes.m_finish - (char *)m_classes.m_start) >> 5);
    if (classIndex < count) {
        _ReadWriteBarrier();
        return ((CreateAHeroClass *)((char *)m_classes.m_start + (classIndex << 5)))->GetStatNameKey(subClassIndex, index);
    }
    return 0;
}
// CreateAHeroManager::GetBling, retail 0x00219D85 37B: the 16-byte bling
// list at +0x15C (WB asserts blingId < m_blingList.size()), null on a miss.
void *CreateAHeroManager::GetBling(UnsignedInt blingId)
{
    Vec16 *v = &m_blingList;
    char *finish = (char *)v->m_finish;
    unsigned int count = (unsigned int)((finish - (char *)v->m_start) >> 4);
    if (blingId < count) {
        _ReadWriteBarrier();
        return &v->m_start[blingId];
    }
    return 0;
}
// CreateAHeroManager::GetPreferedFaction, retail 0x00219FE3 51B; -1 on a bad
// class index.
Int CreateAHeroManager::GetPreferedFaction(UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    unsigned int count = (unsigned int)(((char *)m_classes.m_finish - (char *)m_classes.m_start) >> 5);
    if (classIndex >= count)
        return -1;
    _ReadWriteBarrier();
    return ((CreateAHeroClass *)((char *)m_classes.m_start + (classIndex << 5)))->GetPreferedFaction(subClassIndex);
}
// CreateAHeroManager::GetSubClassAttributeMinValue, retail 0x0021BF42 50B:
// the class index is the middle argument.
Int CreateAHeroManager::GetSubClassAttributeMinValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    ClassVec *v = &m_classes;
    unsigned int count = ClassCount(v);
    if (classIndex < count) {
        _ReadWriteBarrier();
        CreateAHeroClass *base = v->m_start;
        return base[classIndex].GetAttributeMinValue(attribute, subClassIndex);
    }
    return -1;
}
// CreateAHeroManager::GetSubClassAttributeMaxValue, retail 0x0021BF74 50B.
Int CreateAHeroManager::GetSubClassAttributeMaxValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    ClassVec *v = &m_classes;
    unsigned int count = ClassCount(v);
    if (classIndex < count) {
        _ReadWriteBarrier();
        CreateAHeroClass *base = v->m_start;
        return base[classIndex].GetAttributeMaxValue(attribute, subClassIndex);
    }
    return -1;
}
// CreateAHeroManager::GetSubClassAttributeDefaultValue, retail 0x0021BFA6 50B.
Int CreateAHeroManager::GetSubClassAttributeDefaultValue(UnsignedInt attribute, UnsignedInt classIndex, UnsignedInt subClassIndex)
{
    ClassVec *v = &m_classes;
    unsigned int count = ClassCount(v);
    if (classIndex < count) {
        _ReadWriteBarrier();
        CreateAHeroClass *base = v->m_start;
        return base[classIndex].GetAttributeDefaultValue(attribute, subClassIndex);
    }
    return -1;
}

// CreateAHeroManager::GetBlingNameTag (class, subclass overload), retail
// 0x0021CA0D 137B: WB's assert names it ("Class index is invalid in
// CreateAHeroManager::GetBlingNameTag"); the subclass answers through
// 0x0021C9A6, a bad class index with the class-index fallback string.
const AsciiString &CreateAHeroManager::GetBlingNameTag(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroSubClass *p = (CreateAHeroSubClass *)m_classes.m_start[classIndex].rva00219B9E(subClassIndex);
        if (p)
            return *(const AsciiString *)p->rva0021C9A6(blingKey, index);
    }
    return err;
}
// CreateAHeroManager::GetBlingDescTag (class, subclass overload), retail
// 0x0021CA96 137B: as GetBlingNameTag through 0x0021C970.
const AsciiString &CreateAHeroManager::GetBlingDescTag(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex, UnsignedInt index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = ClassCount(&m_classes);
    if (classIndex < count) {
        CreateAHeroSubClass *p = (CreateAHeroSubClass *)m_classes.m_start[classIndex].rva00219B9E(subClassIndex);
        if (p)
            return *p->rva0021C970(blingKey, index);
    }
    return err;
}
