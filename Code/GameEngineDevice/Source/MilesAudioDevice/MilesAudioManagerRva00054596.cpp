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
class MilesAudioManager
{
public:
	int rva00054596();
private:
	void *m_vtable;
	char m_padC[0x9DC - 4];
	char m_pad9DC[0xA3C - 0x9DC];
	_STL::list<int> m_available3D;
};
int MilesAudioManager::rva00054596()
{
	if (!m_available3D.empty()) {
		_STL::list<int>::iterator it = m_available3D.begin();
		int v = *it;
		m_available3D.erase(it);
		return v;
	}
	return 0;
}
