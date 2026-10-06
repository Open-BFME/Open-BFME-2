// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<void**, Rva00568721Cmp> family over void* keys with the
// pinned thiscall comparator Rva00568721Cmp::operator() (ICF twin of the
// rowed stdcall Rva00568721Less at 0x00568721). The rowed
// __unguarded_partition 0x00568DB7 (stlport_unguarded_partition_rva00568721.cpp)
// was its only landed member; the pointer median and the introsort loop that
// calls it live in stlport_introsort_loop_rva00568721.cpp. This unit holds:
//   sort 0x0056A29B, __final_insertion_sort 0x0056940C, __insertion_sort
//   0x005692DF, __unguarded_insertion_sort 0x00568E00 and its aux 0x00568ACF,
//   __linear_insert 0x0056909F, __unguarded_linear_insert 0x005687FF,
//   partial_sort 0x00569A8D, __partial_sort 0x0056946B, make_heap 0x005690F0,
//   __make_heap 0x00568E78, __adjust_heap 0x00568AF0, __push_heap 0x00568830,
//   sort_heap 0x00569339, pop_heap 0x00569126, __pop_heap_aux 0x00568EE6 and
//   __pop_heap 0x00568E4F.
// Evidence: every body reaches the next by REL32 from the rowed partition and
// the sort call site at 0x0056A2C8; each placed uniquely by masked search in
// 0x568600-0x56A300 (the two 23B forwarders and the two 25B heap wrappers
// split by callee). The vendored header reproduces all but three, which use
// the loaded-temporary spelling of the Rva00422CA8 family siblings and are
// explicit specializations: __unguarded_linear_insert and __push_heap compare
// against and store a loaded temporary, __partial_sort loads *i before the
// comparison.
#include <algorithm>
struct Rva00568721Cmp
{
	bool operator()(const void *a, const void *b) const;
};
namespace _STL
{
// ??$__unguarded_linear_insert@PAPAXPAXURva00568721Cmp@@@_STL@@YAXPAPAXPAXURva00568721Cmp@@@Z @0x005687FF
template <>
void __unguarded_linear_insert<void **, void *, Rva00568721Cmp>(void **last, void *val, Rva00568721Cmp comp)
{
	void **next = last;
	--next;
	for (;;)
	{
		void *tmp = *next;
		if (!comp(val, tmp))
			break;
		*last = tmp;
		last = next;
		--next;
	}
	*last = val;
}
// ??$__push_heap@PAPAXHPAXURva00568721Cmp@@@_STL@@YAXPAPAXHHPAXURva00568721Cmp@@@Z @0x00568830
template <>
void __push_heap<void **, int, void *, Rva00568721Cmp>(void **first, int holeIndex, int topIndex, void *val, Rva00568721Cmp comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex)
	{
		void *tmp = *(first + parent);
		if (!comp(tmp, val))
			break;
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}
// ??$__partial_sort@PAPAXPAXURva00568721Cmp@@@_STL@@YAXPAPAX000URva00568721Cmp@@@Z @0x0056946B
template <>
void __partial_sort<void **, void *, Rva00568721Cmp>(void **first, void **middle, void **last, void **, Rva00568721Cmp comp)
{
	make_heap(first, middle, comp);
	for (void **i = middle; i < last; ++i)
	{
		void *cur = *i;
		if (comp(cur, *first))
			__pop_heap(first, middle, i, *i, comp, (int *)0);
	}
	sort_heap(first, middle, comp);
}
}
// ??$sort@PAPAXURva00568721Cmp@@@_STL@@YAXPAPAX0URva00568721Cmp@@@Z @0x0056A29B and its callees
template void _STL::sort<void **, Rva00568721Cmp>(void **, void **, Rva00568721Cmp);
