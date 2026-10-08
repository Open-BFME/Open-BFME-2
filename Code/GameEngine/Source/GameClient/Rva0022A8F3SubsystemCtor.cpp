// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022A8F3Subsystem@@QAE@XZ @0x0022E092 55B
// Evidence: pin ctor; caller GameEngine::init 0x0022EDEF TheLivingWorldAutoResolveWeaponStore; callees baseConstruct 0x001B4E63 and hash_map 0x0022D95A; pattern mirrors PlayerAITypeSetCtor.
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

class __declspec(novtable) Rva0022A8F3SubsystemBase
{
public:
	Rva0022A8F3SubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022A8F3SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};

class Rva0022A8F3Subsystem : public Rva0022A8F3SubsystemBase
{
public:
	Rva0022A8F3Subsystem();
	virtual ~Rva0022A8F3Subsystem();
private:
	_STL::hash_map<int, Rva0022D95AElement> m_map0C;
};

Rva0022A8F3Subsystem::Rva0022A8F3Subsystem()
{
}
