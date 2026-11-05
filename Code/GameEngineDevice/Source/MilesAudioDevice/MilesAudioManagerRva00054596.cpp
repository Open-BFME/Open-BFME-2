// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva00054596@MilesAudioManager@@QAEHXZ @0x00054596 43B.
// MilesAudioManager available-3D-sample pop via list erase plus empty check.
// Evidence: unlock lane plus this+0xA3C list<H3DSAMPLE> from Init3DSamplePools plus rowed list<int> erase 0x00438539 plus callers 0x00061F9C 0x00061FB6.
#include <list>

// Single-node erase binds the verified native STLport owner at RVA 0x00438539.
// Retain the callers' out-of-line call without emitting a competing copy.
namespace _STL {
template<> list<int>::iterator list<int>::erase(iterator position);
}
typedef void *H3DSAMPLE;
#include "../../Include/MilesAudioDevice/MilesAudioManager.h"
int MilesAudioManager::rva00054596()
{
	if (!m_available3DSamples.empty()) {
		_STL::list<int>::iterator it = m_available3DSamples.begin();
		int v = *it;
		m_available3DSamples.erase(it);
		return v;
	}
	return 0;
}
