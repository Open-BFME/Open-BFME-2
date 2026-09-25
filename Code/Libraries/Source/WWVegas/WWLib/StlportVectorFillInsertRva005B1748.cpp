// Target boundary 0x005B1748/232 is STLport vector::_M_fill_insert: the
// boundary checks the 20-byte capacity/position/count cases, calls the
// false_type vector overflow helper when growth is needed, and returns with
// ret 0x0C. Target caller 0x005B1A07 passes the iterator/count/value form.
//
// BfmePod20 is a size-only emitter view (five DWORDs); no concrete application
// record identity or field layout is claimed. Target evidence establishes a
// 0x14 stride and the helper-call ABI, not the retail type name.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct BfmePod20 { int a[5]; };

// /Ob0 preserves retail's out-of-line false_type copy-backward wrapper call.
template void _STL::vector<BfmePod20>::_M_fill_insert(
	BfmePod20 *, unsigned int, const BfmePod20 &);
