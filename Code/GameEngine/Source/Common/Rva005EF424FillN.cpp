// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAURva005EFD53Element@@IU1@@_STL@@YAPAURva005EFD53Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x005EF424 (37B).
// _STL::__uninitialized_fill_n<Rva005EFD53Element>, retail 37 bytes. Dedicated TU
// so no local _Construct definition can inline into this loop. Element
// stride is 4 via the dummy body below; _Construct is declared only
// and resolves through the pin at 0x005F09FF. Unblocks 0x005EF4A5.
#include "RegionIconSlotReferenceView.h"

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(cur, x);
	return cur;
}

template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	__false_type tag;
	return __uninitialized_fill_n(first, n, x, tag);
}

}

template Rva005EFD53Element *_STL::__uninitialized_fill_n(Rva005EFD53Element *, unsigned int, const Rva005EFD53Element &, const _STL::__false_type &);
template Rva005EFD53Element *_STL::uninitialized_fill_n(Rva005EFD53Element *, unsigned int, const Rva005EFD53Element &);
