// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAUBfmeVectorRecord000C0BEC@@IU1@@_STL@@YAPAUBfmeVectorRecord000C0BEC@@PAU1@IABU1@ABU__false_type@0@@Z @0x000C245E 37B
// Evidence: caller @0x000C788C pushes 4 args and pops 0x10, so retail is
// the 4-arg (first, n, x, tag) form whose loop calls rowed
// ??$_Construct@UBfmeVectorRecord000C0BEC@@U1@@_STL@@YAXPAUBfmeVectorRecord000C0BEC@@ABU1@@Z
// @0x000C23B4; explicit instantiation of the ONE member; declared-only
// _Construct keeps the call external.
#include <vector>

struct BfmeVectorRecord000C0BEC
{
	~BfmeVectorRecord000C0BEC();
	unsigned char m_data[0x14];
};

namespace _STL
{
template <> void _Construct<BfmeVectorRecord000C0BEC, BfmeVectorRecord000C0BEC>(
	BfmeVectorRecord000C0BEC *ptr, const BfmeVectorRecord000C0BEC &value);
}

template BfmeVectorRecord000C0BEC *_STL::__uninitialized_fill_n<BfmeVectorRecord000C0BEC *,
	unsigned int, BfmeVectorRecord000C0BEC>(
	BfmeVectorRecord000C0BEC *first, unsigned int n, const BfmeVectorRecord000C0BEC &x,
	const _STL::__false_type &);
