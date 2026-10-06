// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Target: Ghidra boundary 0x000567C5, 47 bytes. MilesAudioManager class identity
// and list offset +0x98 come from the adjacent matched initSamplePools TU;
// request helper identity and call target come from the target packet. The
// request object's +0 and +8 stores are target observations, not donor layout claims.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva00051107AudioRequest;

class MilesAudioManager
{
public:
	void rva000567C5(unsigned int value);
	Rva00051107AudioRequest *rva00051107();

private:
	void *m_vtable;
	char m_pad004[0x94];
	_STL::list<int> m_availableRequests;
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
