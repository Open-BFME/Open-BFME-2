// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022BD25Subsystem@@QAE@XZ, retail 0x0041F913 (55B).
// Subsystem ctor for TheArmyDefinitionManager: base BFME2NativeNetwork via rowed baseConstruct 0x001B4E63 plus hash_map member at +0xC via rowed 0x0041F8F4 and vtable 0x00C3B8C8. Evidence: pin ??0Rva0022BD25Subsystem@@QAE@XZ; caller 0x0022F955 in GameEngine::init new Rva0022BD25Subsystem; vtable slot0 rowed Rva0041F94A deleting wrapper.
#include <hash_map>
#include "ascii_string.h"

struct Rva0041F8F4Element
{
	char bytes[1];
};

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva0022BD25SubsystemBase
{
public:
	Rva0022BD25SubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022BD25SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};

class Rva0022BD25Subsystem : public Rva0022BD25SubsystemBase
{
public:
	Rva0022BD25Subsystem();
	virtual ~Rva0022BD25Subsystem();
private:
	_STL::hash_map<int, Rva0041F8F4Element> m_map0C;
};

Rva0022BD25Subsystem::Rva0022BD25Subsystem()
{
}
