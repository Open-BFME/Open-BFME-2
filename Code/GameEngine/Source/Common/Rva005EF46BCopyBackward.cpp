// cl: /MD
// ??$copy_backward@PAVRva005EEFD2@@PAV1@@_STL@@YAPAVRva005EEFD2@@PAV1@00@Z 0x005EF46B 29B STL 3-arg copy_backward wrapper calling 5-arg __copy_backward at 0x005EF000
// Evidence: pushes 0 and tag temp at ebp-1 plus 3 ptr args then call 0x005EF000 with add esp 0x14; caller 0x005EFCA6 in 0x005EFC30; callee pinned 5-arg __copy_backward; same recipe as rowed Rva004F6352 0x004F6876
class Rva005EEFD2
{
public:
	Rva005EEFD2 &operator=(const Rva005EEFD2 &other);
};

namespace _STL
{
	struct random_access_iterator_tag {};
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
