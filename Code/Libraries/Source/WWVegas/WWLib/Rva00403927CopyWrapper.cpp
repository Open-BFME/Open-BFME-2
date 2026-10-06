// cl: /DNDEBUG /MD
// ??$copy@PAVRva00403927@@PAV1@@_STL@@YAPAVRva00403927@@PAV1@00@Z @0x00403BD2 29B
// _STL::copy<Rva00403927> forwarding wrapper, retail 29 bytes. Pushes NULL
// distance and a tag local, then calls the rowed 5-arg __copy at 0x004039E0.
// Dedicated TU so the __copy call stays external. Called by 0x004043C2.
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
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result)
{
	random_access_iterator_tag _t;
	return __copy(first, last, result, _t, (int *)0);
}

}

template Rva00403927 *_STL::copy(Rva00403927 *, Rva00403927 *, Rva00403927 *);
