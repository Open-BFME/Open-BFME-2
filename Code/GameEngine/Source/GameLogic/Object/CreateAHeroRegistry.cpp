// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// CreateAHeroData pointer registry at VA 0x00DFE358 (target evidence: the
// verified CreateAHeroData copy 0x00409D4D registers its this pointer through
// 0x0021D517; both register 0x0021D517 and unregister 0x0021A624 search the
// vector with the rowed STLport find 0x0020E873).
//
// Both retail bodies keep a one-byte nop between the container call and the
// shared ret; the WorldBuilder debug twin of the register (WB 0xB7E820) has
// the same nop after its push_back, so it is a source-level statement carried
// by both builds (spelled here as the __asm nop WWMath's matrix3d.cpp uses).
#include <stl/_algobase.h>
// Keep the native inline maximum without offering a second external copy.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#include <vector>
#include <algorithm>

class CreateAHeroData;

// ScriptGlueRva003BE7ED.cpp owns the registry storage at VA 0x00DFE358.
// Use that datum through the vector view proven by these retail bodies.
extern unsigned int g_00DFE358;
#define g_CreateAHeroRegistry (*reinterpret_cast<_STL::vector<CreateAHeroData *> *>(&g_00DFE358))

void RegisterCreateAHeroAtRva0021D517(CreateAHeroData *hero)
{
    if (_STL::find(g_CreateAHeroRegistry.begin(), g_CreateAHeroRegistry.end(), hero) == g_CreateAHeroRegistry.end()) {
        g_CreateAHeroRegistry.push_back(hero);
        __asm nop
    }
}

// The unregister's erase is the folded 4-byte-element erase 0x001FF51F (the
// rowed vector<void *> spelling, as in Rva004DFB55HeroRemover.cpp): the
// CreateAHeroData spelling already resolves to the other folded erase
// 0x0025BF5D through Rva0025BF8CHeroRemover.cpp, so one name cannot serve both.
namespace _STL { template <> void **vector<void *, allocator<void *> >::erase(void **); }

void UnregisterCreateAHeroAtRva0021A624(CreateAHeroData *hero)
{
    _STL::vector<CreateAHeroData *>::iterator it =
        _STL::find(g_CreateAHeroRegistry.begin(), g_CreateAHeroRegistry.end(), hero);
    if (it != g_CreateAHeroRegistry.end()) {
        reinterpret_cast<_STL::vector<void *> &>(g_CreateAHeroRegistry).erase(reinterpret_cast<void **>(it));
        __asm nop
    }
}
