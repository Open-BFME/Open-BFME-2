// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva00054596@MilesAudioManager@@QAEHXZ @0x00054596 43B.
// MilesAudioManager available-3D-sample pop via list erase plus empty check.
// Evidence: unlock lane plus this+0xA3C list<H3DSAMPLE> from Init3DSamplePools plus rowed list<int> erase 0x00438539 plus callers 0x00061F9C 0x00061FB6.
#include <list>
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
		int v = m_available3D.front();
		m_available3D.erase(m_available3D.begin());
		return v;
	}
	return 0;
}
