// cl: /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

// WB 0x00B569E0 is unnamed; native 0x0020E501..0x0020E53D proves
// the indexed pointer-vector search and the +0x30 key. The named
// EnumeratePendingBattles visits this same +0x14 collection. The named
// resolve-battles click handler sends the returned key in its game message.
// Preserve the address-derived method name until naming evidence exists.
class LivingWorldPendingBattle
{
public:
    unsigned char m_pad00[0x30];
    int m_key30;
};

class LivingWorldRegionManager
{
public:
    LivingWorldPendingBattle *rva0020E501(int key);
private:
    unsigned char m_pad00[0x14];
    _STL::vector<LivingWorldPendingBattle *> m_pendingBattles;
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
