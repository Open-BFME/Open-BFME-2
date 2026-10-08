// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Target: Ghidra boundary 0x000567C5, 47 bytes. MilesAudioManager class identity
// and list offset +0x98 come from the adjacent matched initSamplePools TU;
// request helper identity and call target come from the target packet. The
// request object's +0 and +8 stores are target observations, not donor layout claims.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <hash_map>

struct Rva00051107AudioRequest;

class MilesAudioManager
{
public:
	void rva000567C5(unsigned int value);
	Rva00051107AudioRequest *rva00051107();
	void rva00057787(unsigned int id);

private:
	typedef _STL::hash_multimap<unsigned int, int> RequestMap;

	void *m_vtable;
	char m_pad004[0x94];
	_STL::list<int> m_availableRequests;
	char m_pad09C[0x104 - 0x9C];
	RequestMap m_map104;					// +0x104
};

struct Rva00051107AudioRequest
{
	unsigned int state;
	unsigned int pad04;
	unsigned int value;
};

void MilesAudioManager::rva000567C5(unsigned int value)
{
	Rva00051107AudioRequest *request = rva00051107();
	request->value = value;
	request->state = 1;
	m_availableRequests.push_back(reinterpret_cast<const int &>(request));
}

// ?rva00057787@MilesAudioManager@@QAEXI@Z, retail 0x00057787..0x000577E3 (92
// bytes): ids from 5 up are looked up in the +0x104 multimap (rowed _M_find
// 0x002888D4 and iterator increment 0x0041E832 for <unsigned, int>); every
// value stored under the id is queued through the request helper above, or
// the id itself when it has none.
void MilesAudioManager::rva00057787(unsigned int id)
{
	if (id < 5)
		return;
	RequestMap::iterator it = m_map104.find(id);
	if (it == m_map104.end())
	{
		rva000567C5(id);
		return;
	}
	do
	{
		rva000567C5(it->second);
		++it;
	} while (it != m_map104.end() && it->first == id);
}
