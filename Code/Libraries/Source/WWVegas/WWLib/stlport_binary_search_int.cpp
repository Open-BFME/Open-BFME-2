// cl: /DNDEBUG /MD /EHsc /Oi
// stlport
#include <algorithm>
#include <string.h>
//
// binary_search<int*, int> @0x0040AD75 56B: lower_bound through the rowed
// __lower_bound<int*, int, less<int>, int> worker 0x0040AC58, then
// i != last && !(val < *i) with a signed compare. Evidence: sole callee is
// that worker; callers 0x0040AE1F and 0x0040AE51; unique masked hit.
//
// Retail zero-fills the one-byte comparator before passing it by value.
// Preserve that initialization while using the shared STL comparator type.
namespace _STL {

template <> int* __lower_bound<int*, int, less<int>, int>(
    int*, int*, const int&, less<int>, int*);

// ??$binary_search@PAHH@_STL@@YA_NPAH0ABH@Z @0x0040AD75
template <>
bool binary_search<int*, int>(int* __first, int* __last, const int& __val)
{
	less<int> comparator;
	memset(&comparator, 0, sizeof(comparator));
	int* __i = __lower_bound(__first, __last, __val, comparator, (int*)0);
	return __i != __last && !(__val < *__i);
}

}
