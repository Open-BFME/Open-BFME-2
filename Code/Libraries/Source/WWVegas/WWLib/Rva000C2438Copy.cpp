// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAUBfmeVectorRecord000C0BEC@@PAU1@@_STL@@YAPAUBfmeVectorRecord000C0BEC@@PAU1@00ABU__false_type@0@@Z @0x000C2438 38B
// Evidence: retail (first, last, result) loop calls rowed
// ??$_Construct@UBfmeVectorRecord000C0BEC@@U1@@_STL@@YAXPAUBfmeVectorRecord000C0BEC@@ABU1@@Z
// @0x000C23B4 with stride 0x14 on both ranges; callers @0x000C785F
// @0x000C78AA; same family as rowed __uninitialized_fill_n @0x000C245E;
// explicit instantiation of the ONE member; declared-only _Construct
// keeps the call external.
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

template BfmeVectorRecord000C0BEC *_STL::__uninitialized_copy<BfmeVectorRecord000C0BEC *,
	BfmeVectorRecord000C0BEC *>(
	BfmeVectorRecord000C0BEC *first, BfmeVectorRecord000C0BEC *last,
	BfmeVectorRecord000C0BEC *result, const _STL::__false_type &);
