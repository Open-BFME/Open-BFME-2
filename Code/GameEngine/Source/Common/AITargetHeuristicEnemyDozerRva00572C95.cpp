// cl: /MD /O1 /Oy-
//
// ?isValidTarget@AITargetHeuristicEnemyDozer@@QAEHPAUThing@@PAX@Z, retail 0x00572c95, 149 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// AITargetHeuristicEnemyDozer::isValidTarget, retail 0x00572C95 (149 bytes). Shape and
// KindOf mask views follow the neighbouring EnemyStructure heuristic (Rva00573512Permuted.cpp);
// the debug build's AITargetHeuristicEnemyDozer::isValidTarget is the name lead.
#include <string.h>
#pragma function(memset)

template <int N>
class BitFlags
{
public:
    BitFlags() { memset(this, 0, sizeof(*this)); }
    void set(int bit) { m_words[bit >> 5] |= 1u << (bit & 31); }
    unsigned m_words[7];
};

struct Thing
{
    bool isAnyKindOf(const BitFlags<69> &mask) const;
    unsigned char m_pad00[0x94];
    unsigned char m_94;
    unsigned char m_pad95[0x438 - 0x94 - 1];
    unsigned char m_438;
};

class AITargetHeuristicEnemyDozer
{
public:
    int isValidTarget(Thing *thing, void *owner);
};

int AITargetHeuristicEnemyDozer::isValidTarget(Thing *thing, void *owner)
{
    long mask1[7];
    unsigned long mask2[7];
    memset(mask1, 0, 0x1C);
    memset(mask2, 0, 0x1C);
    ((unsigned char *)mask2)[25] |= 8;
    ((unsigned char *)mask2)[13] |= 1;
    const unsigned int c10 = 0x10000000;
    Thing *t = thing;
    ((unsigned char *)mask2)[18] |= 0x40;
    mask1[6] |= 4;
    mask2[1] |= c10;
    mask2[5] = mask2[5] | (0x20000000);
    mask2[4] |= c10;
    ((unsigned char *)mask2)[18] |= 0x10;
    mask2[1] = mask2[1] | (0x20000000);
    ((unsigned char *)mask2)[6] |= 4;
    if (0 != t && (t->m_94 & 1) == 0 && (t->m_438 & 1) == 0) {
        const bool r1 = t->isAnyKindOf((const BitFlags<69> &)mask1);
        if (r1 != 0 || t->isAnyKindOf((const BitFlags<69> &)mask2) == 0)
            return 1;
        return 0;
    }
    return 0;
}
