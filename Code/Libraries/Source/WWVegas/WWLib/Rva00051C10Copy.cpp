// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// _STL::__copy random-access loops over three 4-byte handle types, retail
// 0x00051BE1 47B, 0x00051C10 47B and 0x005E1A87 47B, plus the matching
// __copy_backward 0x004F6628 47B and fill 0x005EF488 29B.
// Evidence: both count (last - first) >> 2 elements and assign each through an
// external operator=, 0x00037150 (the rowed UnicodeString::set) and
// 0x00239099 (the rowed OpaqueRefElement4 assignment) and 0x002174A4 (the rowed
// TreeHintRef00217D4C assignment). __copy_backward decrements both ends before
// each 0x002174A4 assignment; fill walks first..last assigning the value through
// the rowed Rva005EEFD2 operator= 0x005EEFD2. Same recipe as the
// 0x004039E0 sibling in Rva00403927Copy.cpp; dedicated TU so the operator=
// calls stay external.
#include "unicode_string.h"

struct OpaqueRefElement4
{
	void *referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct TreeHintRef00217D4C
{
	void *m_target;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

class Rva005EEFD2
{
	void *m_data;

public:
	Rva005EEFD2 &operator=(const Rva005EEFD2 &that);
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

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter2 __copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result, const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n)
		*--result = *--last;
	return result;
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value)
{
	for (; first != last; ++first)
		*first = value;
}

}

template UnicodeString *_STL::__copy(UnicodeString *, UnicodeString *, UnicodeString *, const random_access_iterator_tag &, int *);
template OpaqueRefElement4 *_STL::__copy(OpaqueRefElement4 *, OpaqueRefElement4 *, OpaqueRefElement4 *, const random_access_iterator_tag &, int *);
template TreeHintRef00217D4C *_STL::__copy(TreeHintRef00217D4C *, TreeHintRef00217D4C *, TreeHintRef00217D4C *, const random_access_iterator_tag &, int *);
template TreeHintRef00217D4C *_STL::__copy_backward(TreeHintRef00217D4C *, TreeHintRef00217D4C *, TreeHintRef00217D4C *, const random_access_iterator_tag &, int *);
template void _STL::fill(Rva005EEFD2 *, Rva005EEFD2 *, const Rva005EEFD2 &);
