// cl: /O1 /G7 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@URva000AB419Element@@V?$allocator@URva000AB419Element@@@_STL@@@_STL@@IAEXPAURva000AB419Element@@ABU3@ABU__false_type@2@I_N@Z @0x000AAFC6 186B.
// STLport vector<Rva000AB419Element>::_M_insert_overflow false_type growth path.
// Evidence: chain via 0x000A9E8D fill_n now ready; callees allocate 0x002226BE
// copy 0x000A9E67 Construct pin 0x000A9E0A fill 0x000A9E8D free 0x00030830;
// caller push_back 0x000AB446; stride 0x10 via sar 4/shl 4; same shape as sibling
// overflow 0x000AAF09 for Rva000AB3E2Element (0x18 stride) in neighbouring TU.
#include <vector>
struct Rva000AB419Element
{
	int a[4];
public:
	Rva000AB419Element(const Rva000AB419Element &that);
};
namespace _STL
{
template <> void _Construct<Rva000AB419Element, Rva000AB419Element>(Rva000AB419Element *, const Rva000AB419Element &);
}
template void _STL::vector<Rva000AB419Element>::_M_insert_overflow(
	Rva000AB419Element *,
	const Rva000AB419Element &,
	const _STL::__false_type &,
	unsigned int,
	bool);
