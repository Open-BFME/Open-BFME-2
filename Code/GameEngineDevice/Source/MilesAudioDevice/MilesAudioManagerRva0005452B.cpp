// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva0005452B@MilesAudioManager@@QAEXXZ @0x0005452B 64B.
// MilesAudioManager release-all-3D-samples: loop over list<int> at +0xA3C releasing
// each HSAMPLE via AIL_release_3D_sample_handle then erase(begin), finally zero the
// sample count at +0x680 (and [ebx+0x680],0 under /O1).
// Evidence: same shape as 2D release-all 0x000544EB (list +0xA38 count +0x67C)
// shifted by 4 (list +0xA3C count +0x680); rowed list<int> erase 0x00438539;
// IAT 3D release call; callers 0x000603C7 0x0006076B.
#include <list>

// Single-node erase binds the verified native STLport owner at RVA 0x00438539.
// Retain the callers' out-of-line call without emitting a competing copy.
namespace _STL {
template<> list<int>::iterator list<int>::erase(iterator position);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef void *HSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_release_3D_sample_handle(HSAMPLE sample);

class MilesAudioManager
{
public:
    void rva0005452B();
private:
    void *m_vtable;
    char m_pad004[0x680 - 4];
    unsigned int m_numSamples;
    char m_pad684[0xA3C - 0x684];
    _STL::list<int> m_available;
};

void MilesAudioManager::rva0005452B()
{
    _STL::list<int>::iterator it = m_available.begin();
    while (it != m_available.end()) {
        AIL_release_3D_sample_handle((HSAMPLE)*it);
        it = m_available.erase(it);
    }
    m_numSamples = 0;
}
