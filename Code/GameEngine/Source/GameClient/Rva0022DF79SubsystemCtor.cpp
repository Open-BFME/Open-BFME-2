// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022A9DDSubsystem@@QAE@XZ @0x0022DF79 55B
// Evidence: GameEngine::init caller registers TheLivingWorldAutoResolveLeadershipStore; callees baseConstruct 0x001B4E63 and hash_map 0x0022D95A.
#include <hash_map>
#include "ascii_string.h"

struct Rva0022D95AElement
{
	char bytes[1];
};

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva0022A9DDSubsystemBase
{
public:
	Rva0022A9DDSubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022A9DDSubsystemBase();

private:
	unsigned char m_04;
	int m_08;
};

class Rva0022A9DDSubsystem : public Rva0022A9DDSubsystemBase
{
public:
	Rva0022A9DDSubsystem();
	virtual ~Rva0022A9DDSubsystem();

private:
	_STL::hash_map<int, Rva0022D95AElement> m_map0C;
};

Rva0022A9DDSubsystem::Rva0022A9DDSubsystem()
{
}
