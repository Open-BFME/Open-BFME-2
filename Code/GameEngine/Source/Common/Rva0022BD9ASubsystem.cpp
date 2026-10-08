// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
#include <hash_map>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0041EFE0Element { char bytes[1]; bool operator<(const Rva0041EFE0Element &) const; bool operator==(const Rva0041EFE0Element &) const; };
namespace _STL { template<> struct hash<Rva0041EFE0Element> { unsigned operator()(const Rva0041EFE0Element &) const; }; }

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

// ??0Rva0022BD9ASubsystem@@QAE@XZ @0x0041EFFF 67B
// Target evidence: leaf, called by GameEngine::init 0x0022F999 via new;
// calls rowed baseConstruct 0x001B4E63 then two rowed hash_map ctors 0x0041EFE0
// at +0x0C and +0x20; vtable 0x0083AF78 auto; neighbours 0x0041EFE0 0x0041F25E.
// Precedent Rva00222061Ctor Shell-pattern novtable base for EH after baseConstruct.
class Rva0022BD9ASubsystem : public BFME2NativeNetworkBase
{
public:
	Rva0022BD9ASubsystem();
	virtual ~Rva0022BD9ASubsystem();

private:
	_STL::hash_map<int, Rva0041EFE0Element> m_map0C;
	_STL::hash_map<int, Rva0041EFE0Element> m_map20;
};

Rva0022BD9ASubsystem::Rva0022BD9ASubsystem()
	: m_map0C(),
	  m_map20()
{
}
