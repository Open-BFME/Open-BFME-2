// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001F092A@@QAE@XZ, retail 0x001F092A, 80 bytes.
// Default ctor: base BFME2NativeNetwork via its inline ctor (rowed
// baseConstruct 0x001B4E63), vptr 0x007E100C, map<int,void*> at +0x0C via
// rowed map ctor 0x0033C432, vector<BfmeE16> at +0x18 and +0x24 via rowed
// _Vector_base ctor 0x00211E58. Base layout (vptr + flag + value = 12B)
// from BFME2NativeNetworkBaseConstruct.cpp; member pattern from
// Rva001FDB55Ctor.cpp (same base plus vector/set) and
// stlport_vector_e16_o1.cpp. Sole caller at 0x0022EBBD.
#include <vector>
#include <map>

struct BfmeE16 { float x, y, z, w; };

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork();
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	void baseConstruct();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

// ??0BFME2NativeNetwork@@QAE@XZ present-unmatched
__forceinline BFME2NativeNetwork::BFME2NativeNetwork()
{
	baseConstruct();
}

class Rva001F092A : public BFME2NativeNetwork
{
public:
	Rva001F092A();
private:
	_STL::map<int, void *> m_map;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec0;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec1;
};

Rva001F092A::Rva001F092A()
{
}
