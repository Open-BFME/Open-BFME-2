// ??$_M_allocate_and_copy@PAUAngleFXInfo@@@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@IAEPAUAngleFXInfo@@IPAU2@0@Z
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<AngleFXInfo>::_M_allocate_and_copy at 0x00181500, the
// reallocation path of StructureToppleUpdate's angle-FX list. Split out of
// AngleFXInfoVectorInsertOverflow.cpp: that unit's implicit instantiation emits
// the vendored __uninitialized_copy<_Construct> loop (destination-indexed,
// 79 B), while retail chases the *source* pointer and derives the destination
// as `result + (p - first)` (76 B). The vendored header cannot be edited, so
// the member template is explicitly specialized here (member-template
// specialization of an explicit class-template specialization, the MSVC 7.1
// `template<> template<>` form) and the explicit instantiation uses it.
//
// The char-pointer spelling of `result + (p - first)` plus the null check on
// the derived destination reproduces retail exactly: the null check keeps the
// derived pointer materialized (`lea edx,[esi+ecx]; test edx,edx; je`) instead
// of letting MSVC strength-reduce it into an indexed store, and the source is
// the induction variable (`add ecx,8; cmp ecx,edi; jne`). Evidence: boundary
// 0x00181500 from the candidate inventory, 76 retail bytes, callers in
// StructureToppleUpdate.cpp.

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
struct AngleFXInfo
{
	float angle;
	FXList *fxList;
};

template<>
template<>
AngleFXInfo * _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >::_M_allocate_and_copy<AngleFXInfo *>(
	unsigned int n, AngleFXInfo *first, AngleFXInfo *last)
{
	AngleFXInfo *result = this->_M_end_of_storage.allocate(n);
	for (AngleFXInfo *p = first; p != last; ++p)
	{
		AngleFXInfo *dest = (AngleFXInfo *)((char *)result + ((char *)p - (char *)first));
		if (dest)
			*dest = *p;
	}
	return result;
}

template class _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >;
