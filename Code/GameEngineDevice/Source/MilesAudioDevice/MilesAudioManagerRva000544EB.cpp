// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva000544EB@MilesAudioManager@@QAEXXZ @0x000544EB 64B
// MilesAudioManager release-all-2D-samples: loop over list<int> at +0xA38 releasing
// each HSAMPLE via AIL_release_sample_handle then erase(begin), finally zero the
// sample count at +0x67C (and [ebx+0x67C],0 under /O1).
// Evidence: same +0xA38 list and +0x67C count as InitSamplePools; rowed list<int>
// erase 0x00438539 with the same push/ecx frame as rva0005456B; IAT release call;
// caller 0x000603C0.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef void *HSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_release_sample_handle(HSAMPLE sample);

class MilesAudioManager
{
public:
	void rva000544EB();
private:
	void *m_vtable;
	char m_pad004[0x67c - 4];
	unsigned int m_numSamples;
	char m_pad680[0xA38 - 0x680];
	_STL::list<int> m_available;
};

void MilesAudioManager::rva000544EB()
{
	_STL::list<int>::iterator it = m_available.begin();
	while (it != m_available.end()) {
		AIL_release_sample_handle((HSAMPLE)*it);
		it = m_available.erase(it);
	}
	m_numSamples = 0;
}
