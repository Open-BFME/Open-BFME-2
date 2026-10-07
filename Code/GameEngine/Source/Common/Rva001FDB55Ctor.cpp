// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001FDB55@@QAE@XZ @0x001FDB55 76B.
// Default ctor: base BFME2NativeNetwork via its inline ctor (which calls the
// rowed baseConstruct 0x001B4E63), vptr 0x007E1BB0, vector<BfmeE16> at +0xC
// via the rowed _Vector_base ctor 0x00211E58, set<AsciiString> at +0x18 via
// the rowed set ctor 0x000D3A71, and -1 at +0x24. Base layout (vptr + flag
// + value = 12B) from BFME2NativeNetworkBaseConstruct.cpp; element and
// member patterns from stlport_vector_e16_o1.cpp and
// stlport_asciistring_set_base.cpp. The base carries an empty virtual dtor
// with a _ReadWriteBarrier body: it keeps the base-destruction EH states
// retail arms (early state 0 plus state 1) while emitting no normal-path
// instruction (shape-lever guide prescription). Sole caller at 0x0022EA94.
#include <vector>
#include <set>

#include "ascii_string.h"

struct BfmeE16 { float x, y, z, w; };

bool operator<(const AsciiString &, const AsciiString &);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork();
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	BFME2NativeNetwork *baseConstruct();
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

class Rva001FDB55 : public BFME2NativeNetwork
{
public:
	Rva001FDB55();
private:
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set;
	int m_state24;
};

Rva001FDB55::Rva001FDB55()
{
	m_state24 = -1;
}
