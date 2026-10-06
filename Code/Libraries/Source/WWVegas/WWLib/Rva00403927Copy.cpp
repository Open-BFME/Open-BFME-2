// cl: /DNDEBUG /MD
// ??$__copy@PAVRva00403927@@PAV1@H@_STL@@YAPAVRva00403927@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x004039E0 50B
// _STL::__copy<Rva00403927> random-access loop, retail 50 bytes. Count via
// idiv by stride 0x14, per-element operator= through the rowed 0x00403927.
// Called by the 29B forwarding wrapper at 0x00403BD2 (copy dispatch with tag
// and NULL distance). Dedicated TU so the operator= call stays external.
class Rva00403927
{
	char _m[0x14];

public:
	Rva00403927 &operator=(const Rva00403927 &that);
};

namespace _STL
{

struct random_access_iterator_tag {};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *)
{
	for (int n = last - first; n > 0; --n)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

}

template Rva00403927 *_STL::__copy(Rva00403927 *, Rva00403927 *, Rva00403927 *, const random_access_iterator_tag &, int *);
