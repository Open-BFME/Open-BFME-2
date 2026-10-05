// cl: /O1 /MD
// ??$__copy@PAURva0040538FElement@@PAU1@H@_STL@@YAPAURva0040538FElement@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z retail 0x00404B71 50 bytes.
// STLport __copy for Rva0040538FElement view: count via (last-first)/0x18 then
// copy-constructs each slot through rowed Rva001DE4F0 copy 0x00404A72.
// Evidence: __copy_ptrs 0x00404CD8 calls here with REL32; caller erase
// 0x0040538F; callee copy rowed in Rva001DE4F0Copy.cpp; divisor 0x18 and
// 0x18 adds prove 0x18 element. Recipe: Rva002DFC30CopyLoop 50B assume
// placement-new (assume kills 7.1 null check) with for-i loop and throw.
#include <new.h>

struct Rva0040538FElement
{
	unsigned char _pad[0x18];
};

class Rva001DE4F0
{
public:
	Rva001DE4F0(const Rva001DE4F0 &other) throw();
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class _II, class _OI, class _D>
_OI __copy(_II, _II, _OI, const random_access_iterator_tag &, _D *);
template <>
Rva0040538FElement *__copy<Rva0040538FElement *, Rva0040538FElement *, int>(Rva0040538FElement *, Rva0040538FElement *, Rva0040538FElement *, const random_access_iterator_tag &, int *);
}

template <>
Rva0040538FElement *_STL::__copy<Rva0040538FElement *, Rva0040538FElement *, int>(Rva0040538FElement *__first, Rva0040538FElement *__last, Rva0040538FElement *__result, const random_access_iterator_tag &, int *) throw()
{
	int n = __last - __first;
	if (n <= 0)
		return __result;
	__assume(__result != 0);
	for (int i = 0; i < n; ++i)
	{
		__assume(__result != 0);
		new (__result) Rva001DE4F0(*(const Rva001DE4F0 *)__first);
		++__first;
		++__result;
	}
	return __result;
}
