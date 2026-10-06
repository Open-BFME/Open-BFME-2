// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<int*, Rva00422CA8> and its insertion-sort half over int sort
// keys with the rowed thiscall comparator Rva00422CA8 (operator()(int,int) at
// 0x00422CA8, defined in Rva00422CA8Cmp.cpp):
//   sort                           0x0042549E  67B
//   __final_insertion_sort         0x004243D4  68B
//   __insertion_sort               0x00423DE1  45B
//   __unguarded_insertion_sort     0x00423E0E  23B
//   __unguarded_insertion_sort_aux 0x004238ED  33B
//   __linear_insert                0x004238AE  63B
//   __unguarded_linear_insert      0x00423262  49B
// Evidence: sort calls the rowed __introsort_loop 0x00425385 (whose TU names
// 0x0042549E as its sort wrapper) and then 0x004243D4; each body reaches the
// next by REL32 and the leaves call the rowed comparator and the rowed
// __copy_trivial_backward 0x00620840. The heap/partition half lives in
// stlport_push_heap_rva00422ca8.cpp and its siblings.
//
// The vendored header reproduces six of the seven. Retail's
// __unguarded_linear_insert loads *next into a temporary, compares against
// it and stores that temporary (edi, ebp frame), the same temporary spelling
// as the hand-written __push_heap sibling, so it is an explicit
// specialization declared before the sort instantiation uses it.
#include <algorithm>

class Rva00422CA8
{
public:
	bool operator()(int a, int b) const;
};

namespace _STL
{

// ??$__unguarded_linear_insert@PAHHVRva00422CA8@@@_STL@@YAXPAHHVRva00422CA8@@@Z @0x00423262
template <>
void __unguarded_linear_insert<int *, int, Rva00422CA8>(int *last, int val, Rva00422CA8 comp)
{
	int *next = last;
	--next;
	for (;;)
	{
		int tmp = *next;
		if (!comp(val, tmp))
			break;
		*last = tmp;
		last = next;
		--next;
	}
	*last = val;
}

}

// ??$sort@PAHVRva00422CA8@@@_STL@@YAXPAH0VRva00422CA8@@@Z @0x0042549E and its insertion-sort callees
template void _STL::sort<int *, Rva00422CA8>(int *, int *, Rva00422CA8);
