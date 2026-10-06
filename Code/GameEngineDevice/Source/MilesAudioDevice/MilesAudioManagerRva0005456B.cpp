// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva0005456B@MilesAudioManager@@QAEHXZ @0x0005456B 43B.
 // MilesAudioManager available-sample pop via list erase plus empty check.
// Evidence: unlock lane plus this+0xA38 list<HSAMPLE> from InitSamplePools plus rowed list<int> erase 0x00438539 plus callers 0x000620D3 0x000620ED.
#include <list>
typedef void *HSAMPLE;
class MilesAudioManager
{
public:
	int rva0005456B();
private:
	void *m_vtable;
	char m_padC[0x9DC - 4];
	char m_pad9DC[0xA38 - 0x9DC];
	_STL::list<int> m_available;
};
int MilesAudioManager::rva0005456B()
{
	if (!m_available.empty()) {
		int v = m_available.front();
		m_available.erase(m_available.begin());
		return v;
	}
	return 0;
}
