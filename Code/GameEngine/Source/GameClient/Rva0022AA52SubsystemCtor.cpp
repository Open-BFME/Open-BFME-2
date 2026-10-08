// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022AA52Subsystem@@QAE@XZ @0x0022E03F 55B
// Evidence: pin ctor; caller GameEngine::init TheLivingWorldAutoResolveCombatChainStore; callees baseConstruct 0x001B4E63 and hash_map 0x0022D95A; pattern mirrors Rva0022A8F3Subsystem.
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

class __declspec(novtable) Rva0022AA52SubsystemBase
{
public:
	Rva0022AA52SubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022AA52SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};

class Rva0022AA52Subsystem : public Rva0022AA52SubsystemBase
{
public:
	Rva0022AA52Subsystem();
	virtual ~Rva0022AA52Subsystem();
private:
	_STL::hash_map<int, Rva0022D95AElement> m_map0C;
};

Rva0022AA52Subsystem::Rva0022AA52Subsystem()
{
}
