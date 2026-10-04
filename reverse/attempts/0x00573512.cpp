// ?Rva00573512Check@@YGHPAUThing@@PAX@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?Rva00573512Check@@YGHPAUThing@@PAX@Z @0x00573512 180B unlock free function with record lookup plus two 28B masks plus KINDOF checks
// ?Rva00573512Check@@YGHPAUThing@@PAX@Z present-unmatched
#include <string.h>

template <int N>
class BitFlags
{
public:
    bool test(const void *kindOf) const;
    unsigned m_words[7];
};

struct ThingTemplate
{
    char m_pad[0x108];
    int m_kindOf;
};

struct Thing
{
    bool isAnyKindOf(const BitFlags<69> &mask) const;
    unsigned char m_pad94[0x94];
    unsigned char m_94;
    unsigned char m_pad95[0x438 - 0x94 - 1];
    unsigned char m_438;
};

struct Rva002A8AB1Record
{
    char m_pad[0x16C];
    int m_16C;
};

struct Rva002A8F24
{
    Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

// ?Rva00573512Check@@YGHPAUThing@@PAX@Z present-unmatched
int __stdcall Rva00573512Check(Thing *thing, void *owner)
{
    Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(owner);
    unsigned int mask1[7];
    unsigned int mask2[7];
    memset(mask1, 0, 0x1C);
    memset(mask2, 0, 0x1C);
    ((unsigned char *)mask2)[18] |= 0x40;
    ((unsigned char *)mask2)[25] |= 8;
    ((unsigned char *)mask2)[13] |= 1;
    mask2[1] |= 0x10000000;
    mask2[4] |= 0x10000000;
    ((unsigned char *)mask2)[18] |= 0x10;
    mask2[1] |= 0x20000000;
    mask2[5] |= 0x20000000;
    ((unsigned char *)mask2)[6] |= 4;
    if (rec->m_16C == 0)
        mask2[6] |= 4;
    else
        mask1[6] |= 4;
    Thing *t = thing;
    if (t != 0 && (t->m_94 & 1) == 0 && (t->m_438 & 1) == 0) {
        if (t->isAnyKindOf((const BitFlags<69> &)mask1))
            return 1;
        if (t->isAnyKindOf((const BitFlags<69> &)mask2))
            return 0;
        return 1;
    }
    return 0;
}
