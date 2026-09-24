// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Descending int specialization of _STL::__introsort_loop. Needs /G7 (Pentium 4
// tuning): /O1 emits the threshold mask as dword `and eax,0xfc` where
// retail has the byte form `and al,0xfc` (VID/BVID/StepTDB precedent).
// Shard, not graft: the home TU verifies its 18 rows under /O1 and a flag
// flip would perturb them. Drivers only make the compiler emit the helper
// and carry no rows.
#include <algorithm>
#include <functional>

void bfmeEmitIntIntroSortLoopGreater(int *first, int *last)
{
	_STL::sort(first, last, _STL::greater<int>());
	_STL::partial_sort(first, last, last, _STL::greater<int>());
}
