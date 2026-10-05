// cl: /O1 /G7 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@URva000AB3E2Element@@V?$allocator@URva000AB3E2Element@@@_STL@@@_STL@@IAEXPAURva000AB3E2Element@@ABU3@ABU__false_type@2@I_N@Z @0x000AAF09 189B.
// STLport vector<Rva000AB3E2Element>::_M_insert_overflow false_type growth path.
// Evidence: chain via landed 0x000A9E1C copy now ready; callees allocate 0x00395944
// copy 0x000A9E1C Construct pin 0x000A9DF8 fill 0x000A9E42 free 0x00030830;
// caller push_back 0x000AB3E2; stride 0x18 via idiv; same 189B shape as Pod24
// overflow 0x000BCFF9 which shares the 0x18 imul allocate.
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
