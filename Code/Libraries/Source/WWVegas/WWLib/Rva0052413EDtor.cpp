// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0052413E@@QAE@XZ @0x0052413E 47B
// Native Ghidra extent 0x0052413E/47; caller 0x005FFC08 passes this+0xC.
// Target calls the rowed clear at 0x00523F22 followed by vector<AsciiString>
// destruction at 0x0002CC70. Owner identity unknown; same verified mechanism
// as Rva00524265Dtor with independently observed callee and field layout.
#include <vector>

#include "ascii_string.h"

class Rva00524021
{
public:
	void rva00523F22();
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

Rva0052413E::~Rva0052413E()
{
	((Rva00524021 *)this)->rva00523F22();
}
