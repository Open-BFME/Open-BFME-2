// cl: /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

// WB 0x00B569E0 is unnamed; native 0x0020E501..0x0020E53D proves
// the indexed pointer-vector search and the +0x30 key. The named
// EnumeratePendingBattles visits this same +0x14 collection. The named
// resolve-battles click handler sends the returned key in its game message.
// Siblings 0x0020E57F / 60 B, 0x0020E5BB / 66 B and 0x0020E5FD / 66 B
// are independently bounded by Ghidra and corroborated by WB indexed loops.
// They compare +0x24 or +0x34; the latter two reject zero keys, and the last
// searches the completed collection at +0x20. Key meanings remain unproven.
// Preserve address-derived method names until naming evidence exists.
// What 0x0020E53D reaches through the battle's +0x24 word: an int at +0x12C.
struct Rva0020E53DTarget
{
    unsigned char m_pad00[0x12C];
    int m_key12C;
};

class LivingWorldPendingBattle
{
public:
    unsigned char m_pad00[0x24];
    unsigned int m_key24;
    unsigned char m_pad28[8];
    int m_key30;
    int m_key34;
};

#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"

// Preserve this consumer's vector element type over the canonical raw storage.
// Re-derive the view at each access: caching a vector reference changes MSVC's
// alias analysis and hoists the loop bounds, unlike the retail bodies.

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E501(int key)
{
    for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14)->size(); ++i)
    {
        if ((*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i]->m_key30 == key)
            return (*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i];
    }
    return 0;
}

// Native0x0020E53D..0x0020E57F (66B): the same pending search, keyed one
// level deeper: the +0x12C int of the object the battle's +0x24 word points to.
LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E53D(int key)
{
    for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14)->size(); ++i)
    {
        if (reinterpret_cast<Rva0020E53DTarget *>((*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i]->m_key24)->m_key12C == key)
            return (*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E57F(unsigned int key)
{
    for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14)->size(); ++i)
    {
        if ((*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i]->m_key24 == key)
            return (*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E5BB(int key)
{
    if (key == 0)
        return 0;
    for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14)->size(); ++i)
    {
        if ((*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i]->m_key34 == key)
            return (*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field14))[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E5FD(int key)
{
    if (key == 0)
        return 0;
    for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field20)->size(); ++i)
    {
        if ((*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field20))[i]->m_key34 == key)
            return (*reinterpret_cast<_STL::vector<LivingWorldPendingBattle *> *>(&field20))[i];
    }
    return 0;
}

// Native20E6C0..20E6D6: try the selected +10 key in the pending collection,
// then the completed collection. ResolveBattlesBehavior calls this wrapper;
// the existing independently verified lookups prove its receiver identity.
LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E6C0()
{
    int key = field10;
    LivingWorldPendingBattle *battle = rva0020E5BB(key);
    if (!battle)
        battle = rva0020E5FD(key);
    return battle;
}
