// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@URva000AB3E2Element@@V?$allocator@URva000AB3E2Element@@@_STL@@@_STL@@IAEXPAURva000AB3E2Element@@ABU3@ABU__false_type@2@I_N@Z @0x000AAF09 189B.
// STLport vector<Rva000AB3E2Element>::_M_insert_overflow false_type growth path.
// Evidence: chain via landed 0x000A9E1C copy now ready; callees allocate 0x00395944
// copy 0x000A9E1C Construct pin 0x000A9DF8 fill 0x000A9E42 free 0x00030830;
// caller push_back 0x000AB3E2; stride 0x18 via idiv; same 189B shape as Pod24
// overflow 0x000BCFF9 which shares the 0x18 imul allocate.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
struct Rva000AB3E2Element
{
	int a[6];
public:
	Rva000AB3E2Element(const Rva000AB3E2Element &that);
};
namespace _STL
{
template <> void _Construct<Rva000AB3E2Element, Rva000AB3E2Element>(Rva000AB3E2Element *, const Rva000AB3E2Element &);
}
template void _STL::vector<Rva000AB3E2Element>::_M_insert_overflow(
	Rva000AB3E2Element *,
	const Rva000AB3E2Element &,
	const _STL::__false_type &,
	unsigned int,
	bool);

// ?_M_insert_overflow@?$vector@URva0008DE1CElement@@V?$allocator@URva0008DE1CElement@@@_STL@@@_STL@@IAEXPAURva0008DE1CElement@@ABU3@ABU__false_type@2@I_N@Z @0x0008B6C0 189B.
// The same 189B trivially-destructible growth path for the 24-byte element of
// push_back 0x0008DE1C (its sole caller, StlportVectorPushBackFamily.cpp).
// Its _Construct REL32 reads 0x0008A173, the pinned _Construct for this type.
struct Rva0008DE1CElement
{
	int a[6];
public:
	Rva0008DE1CElement(const Rva0008DE1CElement &that);
};
namespace _STL
{
template <> void _Construct<Rva0008DE1CElement, Rva0008DE1CElement>(Rva0008DE1CElement *, const Rva0008DE1CElement &);
}
template void _STL::vector<Rva0008DE1CElement>::_M_insert_overflow(
	Rva0008DE1CElement *,
	const Rva0008DE1CElement &,
	const _STL::__false_type &,
	unsigned int,
	bool);
