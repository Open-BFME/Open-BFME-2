// Target boundaries 0x000C828C/191 and 0x000C78D5/30 are STLport vector
// overflow/clear helpers for a 0xB4-byte non-trivial element. The matched
// push_back at 0x000C8633 calls overflow at 0x000C8663 with vector ECX and five
// overflow arguments.
//
// Rva000C828CElement is an address-derived opaque 180-byte emitter view. The
// target Construct wrapper at 0xC2387 reaches the matched record-copy helper
// at 0xC0B85; this TU does not claim a complete application element layout.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva000C828CElement {
	char opaque[180];
	Rva000C828CElement(const Rva000C828CElement &);
	Rva000C828CElement &operator=(const Rva000C828CElement &);
	~Rva000C828CElement();
};

namespace _STL {
template <> void _Construct<Rva000C828CElement, Rva000C828CElement>(
	Rva000C828CElement *, const Rva000C828CElement &);
}

template void _STL::vector<Rva000C828CElement>::_M_clear();
template void _STL::vector<Rva000C828CElement>::_M_insert_overflow(
	Rva000C828CElement *, const Rva000C828CElement &,
	const _STL::__false_type &, unsigned int, bool);
