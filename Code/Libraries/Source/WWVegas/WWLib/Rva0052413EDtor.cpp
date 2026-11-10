// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0052413E@@QAE@XZ @0x0052413E 47B
// Native Ghidra extent 0x0052413E/47; caller 0x005FFC08 passes this+0xC.
// Target calls the rowed clear at 0x00523F22 followed by vector<AsciiString>
// destruction at 0x0002CC70. Owner identity unknown; same verified mechanism
// as Rva00524265Dtor with independently observed callee and field layout.
#include <vector>

#include "ascii_string.h"

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

#include "Rva00524021.h"

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
