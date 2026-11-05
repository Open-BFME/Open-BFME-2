// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva0005456B@MilesAudioManager@@QAEHXZ @0x0005456B 43B.
 // MilesAudioManager available-sample pop via list erase plus empty check.
// Evidence: unlock lane plus this+0xA38 list<HSAMPLE> from InitSamplePools plus rowed list<int> erase 0x00438539 plus callers 0x000620D3 0x000620ED.
#include <list>

// Single-node erase binds the verified native STLport owner at RVA 0x00438539.
// Retain the callers' out-of-line call without emitting a competing copy.
namespace _STL {
template<> list<int>::iterator list<int>::erase(iterator position);
}
typedef void *HSAMPLE;
#include "../../Include/MilesAudioDevice/MilesAudioManager.h"
int MilesAudioManager::rva0005456B()
{
	if (!m_availableSamples.empty()) {
		_STL::list<int>::iterator it = m_availableSamples.begin();
		int v = *it;
		m_availableSamples.erase(it);
		return v;
	}
	return 0;
}
