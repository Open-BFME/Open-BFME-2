// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022BE0FSubsystem@@QAE@XZ @0x003ED340 55B
// Ctor: baseConstruct 0x001B4E63 then vtable 0x00C36100 then hash_map
// ctor 0x003ED321. Evidence: caller GameEngine::init at 0x0022F9DC
// (TheThreatFinderManager) plus vtable 0x00C36100 slot 0 plus dtor twin
// 0x003ED1FC in Rva003ED1FCDtor plus StlSweep map row 0x003ED321.
#include <hash_map>

struct Rva003ED321Element
{
	char bytes[1];
	bool operator<(const Rva003ED321Element &) const;
	bool operator==(const Rva003ED321Element &) const;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag04;
	char m_pad05[3];
	int m_value08;
};

class Rva0022BE0FSubsystem : public BFME2NativeNetworkBase
{
public:
	Rva0022BE0FSubsystem();
	virtual ~Rva0022BE0FSubsystem();
private:
	_STL::hash_map<int, Rva003ED321Element> m_map;
};

// ??0Rva0022BE0FSubsystem@@QAE@XZ
Rva0022BE0FSubsystem::Rva0022BE0FSubsystem()
{
}
