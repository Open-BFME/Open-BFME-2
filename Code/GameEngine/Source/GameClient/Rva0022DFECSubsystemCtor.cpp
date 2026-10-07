// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022A968Subsystem@@QAE@XZ @0x0022DFEC 55B
// Evidence: GameEngine::init caller registers TheLivingWorldAutoResolveBodyStore; callees baseConstruct 0x001B4E63 and hash_map 0x0022D95A.
#include <hash_map>
#include "ascii_string.h"

struct Rva0022D95AElement
{
	char bytes[1];
};

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) Rva0022A968SubsystemBase
{
public:
	Rva0022A968SubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022A968SubsystemBase();

private:
	unsigned char m_04;
	int m_08;
};

class Rva0022A968Subsystem : public Rva0022A968SubsystemBase
{
public:
	Rva0022A968Subsystem();
	virtual ~Rva0022A968Subsystem();

private:
	_STL::hash_map<int, Rva0022D95AElement> m_map0C;
};

Rva0022A968Subsystem::Rva0022A968Subsystem()
{
}
