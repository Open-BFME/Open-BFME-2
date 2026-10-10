// cl: /MD /O1 /Oy-
//
// ?isValidTarget@AITargetHeuristicEnemyStructure@@QAEHPAUThing@@PAX@Z, retail 0x00573512, 180 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
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

// class key matches the data ledger primary ?g_00DFEEF8@@3PAVRva002A8F24@@A (Rva005EEA20Find.cpp).
class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *owner);
    void *rva002A8F24(class Player *);
    char pad[0x884];
    float fallbackWeight;
};

extern Rva002A8F24 *g_00DFEEF8;

class AITargetHeuristicEnemyStructure
{
public:
	int isValidTarget(Thing *thing, void *owner);
};

int AITargetHeuristicEnemyStructure::isValidTarget(Thing *thing, void *owner)
{
    void *o = owner;
    Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(o);
    int mask1[7];
    int mask2[7];
    memset(mask1, 0, 0x1C);
    memset(mask2, 0, 0x1C);
    unsigned int c10 = 0x10000000;
    ((unsigned char *)mask2)[25] |= 8;
    ((unsigned char *)mask2)[18] |= 0x40;
    ((unsigned char *)mask2)[13] |= 1;
    mask2[4] |= c10;
    mask2[5] |= 0x20000000;
    mask2[1] = mask2[1] | (c10);
    ((unsigned char *)mask2)[18] |= 0x10;
    mask2[1] |= 0x20000000;
    ((unsigned char *)mask2)[6] |= 4;
    if (rec->m_16C == 0)
        mask2[6] |= 4;
    else
        mask1[6] |= 4;
    Thing *t = thing;
    if (0 != t && (t->m_94 & 1) == 0 && (t->m_438 & 1) == 0) {
        bool r1 = t->isAnyKindOf((const BitFlags<69> &)mask1);
        if (r1 != 0 || t->isAnyKindOf((const BitFlags<69> &)mask2) == 0)
            return 1;
        return 0;
    }
    return 0;
}

// WB 015025E0 names this body and independently corroborates both loops.
// Target helper 572C95 is already rowed; its legacy int result is tested
// through the low byte witnessed by the target and debug caller.
class Player;
class Object;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class AITarget
{
public:
    void setTarget(Object *, float);
};
struct EnemyHeuristicIds { ObjectID *first, *last, *limit; };
class Rva005C4AD1LeaField
{
public:
    void *get() const;
};
struct EnemyHeuristicRecord
{
    void *units;
    void *unused;
    Rva005C4AD1LeaField *structures;
};
class AITargetHeuristicEnemyDozer
{
public:
    int isValidTarget(Thing *, void *);
    void findBestTarget(AITarget *, Player *, Player *);
};
void AITargetHeuristicEnemyDozer::findBestTarget(AITarget *target, Player *attackingPlayer, Player *targetPlayer)
{
    EnemyHeuristicRecord *stats = (EnemyHeuristicRecord *)g_00DFEEF8->rva002A8F24(targetPlayer);
    Rva005C4AD1LeaField *structures = stats->structures;
    int count = 0;
    for (ObjectID *p = ((EnemyHeuristicIds *)structures->get())->first;
         count == 0 && p != ((EnemyHeuristicIds *)structures->get())->last; ++p)
    {
        Object *object = TheGameLogic->findObjectByID(*p);
        if ((unsigned char)isValidTarget((Thing *)object, attackingPlayer)) ++count;
    }
    if (count == 0)
    {
        EnemyHeuristicIds *units = (EnemyHeuristicIds *)((char *)stats->units + 0x98);
        for (ObjectID *p = units->first; p != units->last; ++p)
        {
            Object *object = TheGameLogic->findObjectByID(*p);
            if (object) target->setTarget(object, g_00DFEEF8->fallbackWeight);
        }
    }
}
