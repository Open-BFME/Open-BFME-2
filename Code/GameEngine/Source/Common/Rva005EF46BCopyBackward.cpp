// cl: /MD
// stlport46
// ??$copy_backward@PAVRva005EEFD2@@PAV1@@_STL@@YAPAVRva005EEFD2@@PAV1@00@Z 0x005EF46B 29B STL 3-arg copy_backward wrapper calling 5-arg __copy_backward at 0x005EF000
// Evidence: pushes 0 and tag temp at ebp-1 plus 3 ptr args then call 0x005EF000 with add esp 0x14; caller 0x005EFCA6 in 0x005EFC30; callee pinned 5-arg __copy_backward; same recipe as rowed Rva004F6352 0x004F6876
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#include <stl/_iterator_base.h>
#include <stl/_epilog.h>

class Rva005EEFD2
{
public:
	Rva005EEFD2 &operator=(const Rva005EEFD2 &other);
};

namespace _STL
{
	template <class _BidIt, class _Dist>
	_BidIt __copy_backward(_BidIt first, _BidIt last, _BidIt result, const random_access_iterator_tag &tag, _Dist *);
	template <class _BidIt1, class _BidIt2>
	_BidIt2 copy_backward(_BidIt1 first, _BidIt1 last, _BidIt2 result)
	{
		random_access_iterator_tag tag;
		return __copy_backward(first, last, result, tag, (int *)0);
	}
}

template Rva005EEFD2 *_STL::copy_backward<Rva005EEFD2 *, Rva005EEFD2 *>(Rva005EEFD2 *, Rva005EEFD2 *, Rva005EEFD2 *);

// The retail call in this body reads 0x005EF000, an address the ledger already
// carries as ?Rva005EF000CopyBackward@@YAPAVRva005EEFD2@@PAV1@00@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??$__copy_backward@PAVRva005EEFD2@@H@_STL@@YAPAVRva005EEFD2@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z=?Rva005EF000CopyBackward@@YAPAVRva005EEFD2@@PAV1@00@Z")
