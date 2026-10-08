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
class LivingWorldPendingBattle
{
public:
    unsigned char m_pad00[0x24];
    unsigned int m_key24;
    unsigned char m_pad28[8];
    int m_key30;
    int m_key34;
};

class LivingWorldRegionManager
{
public:
    LivingWorldPendingBattle *rva0020E501(int key);
    LivingWorldPendingBattle *rva0020E57F(unsigned int key);
    LivingWorldPendingBattle *rva0020E5BB(int key);
    LivingWorldPendingBattle *rva0020E5FD(int key);
    LivingWorldPendingBattle *rva0020E6C0();
private:
    unsigned char m_pad00[0x10];
    int m_selectedKey;
    _STL::vector<LivingWorldPendingBattle *> m_pendingBattles;
    _STL::vector<LivingWorldPendingBattle *> m_completedBattles; // +0x20
};

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E501(int key)
{
    for (unsigned int i = 0; i < m_pendingBattles.size(); ++i)
    {
        if (m_pendingBattles[i]->m_key30 == key)
            return m_pendingBattles[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E57F(unsigned int key)
{
    for (unsigned int i = 0; i < m_pendingBattles.size(); ++i)
    {
        if (m_pendingBattles[i]->m_key24 == key)
            return m_pendingBattles[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E5BB(int key)
{
    if (key == 0)
        return 0;
    for (unsigned int i = 0; i < m_pendingBattles.size(); ++i)
    {
        if (m_pendingBattles[i]->m_key34 == key)
            return m_pendingBattles[i];
    }
    return 0;
}

LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E5FD(int key)
{
    if (key == 0)
        return 0;
    for (unsigned int i = 0; i < m_completedBattles.size(); ++i)
    {
        if (m_completedBattles[i]->m_key34 == key)
            return m_completedBattles[i];
    }
    return 0;
}

// Native20E6C0..20E6D6: try the selected +10 key in the pending collection,
// then the completed collection. ResolveBattlesBehavior calls this wrapper;
// the existing independently verified lookups prove its receiver identity.
LivingWorldPendingBattle *LivingWorldRegionManager::rva0020E6C0()
{
    int key = m_selectedKey;
    LivingWorldPendingBattle *battle = rva0020E5BB(key);
    if (!battle)
        battle = rva0020E5FD(key);
    return battle;
}
