// Target boundary 0x0059B809/189 is STLport vector::_M_insert_overflow
// false_type: ?_M_insert_overflow@?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@IAEXPAUBfmePod20@@ABU3@ABU__false_type@2@I_N@Z.
// Matched push_back at 0x0059B8C6 calls it at 0x0059B8F3 and matched
// _M_fill_insert at 0x005B1748 calls it at 0x005B1824 with vector ECX and
// five overflow arguments. Retail advances 0x14-byte elements and
// allocates/copies/fills before releasing old storage. Helpers are
// allocator 0x00395960 copy 0x005B09F5 Construct 0x004FDAEE fill-n
// 0x0059B7E4 and free 0x00030830.
//
// BfmePod20 is a size-only 20-byte emitter view. The concrete retail element
// identity and payload are unknown.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct BfmePod20 { int a[5]; };

template void _STL::vector<BfmePod20>::_M_insert_overflow(
	BfmePod20 *, const BfmePod20 &, const _STL::__false_type &,
	unsigned int, bool);
