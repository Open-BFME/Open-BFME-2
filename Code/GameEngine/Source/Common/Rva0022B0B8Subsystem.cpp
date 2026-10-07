// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
#include <hash_map>

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase();
private:
	char m_flag;
	int m_value;
};

struct Rva003EF584Element { char bytes[1]; bool operator<(const Rva003EF584Element &) const; bool operator==(const Rva003EF584Element &) const; };
namespace _STL { template<> struct hash<Rva003EF584Element> { unsigned operator()(const Rva003EF584Element &) const; }; }

// ??0Rva0022B0B8Subsystem@@QAE@XZ @0x003EF5A3 55B
// Target evidence: called by GameEngine::init at 0x0022F279; target calls
// rowed baseConstruct and hash_map ctor, stores vtable 0x008363D8, then returns.
// Class name is address-derived; the base and one-map layout are structural inference.
class Rva0022B0B8Subsystem : public BFME2NativeNetworkBase
{
public:
	Rva0022B0B8Subsystem();
	virtual ~Rva0022B0B8Subsystem();

private:
	_STL::hash_map<int, Rva003EF584Element> m_map;
};

Rva0022B0B8Subsystem::Rva0022B0B8Subsystem()
	: m_map()
{
}
