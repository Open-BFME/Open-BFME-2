// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_insertion_sort@PAHVRva005E4300Cmp@@@_STL@@YAXPAH0VRva005E4300Cmp@@@Z @0x005E4A48 23B unguarded insertion sort entry for int keys.
// Forwards first last plus NULL type tag plus comparator to rowed aux 0x005E48A1.
// Evidence: chain from just-landed aux; frameless 4-push forwarder with push 0 dummy; caller at 0x005E4C57 in 0x005E4C2F; same 23B shape as 0x00423E0E and 0x001739CD.
class Rva005E4300Cmp
{
public:
	bool operator()(int a, int b) const;
};
namespace _STL {
template <class RandomAccessIter, class T, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T *, Compare comp);
template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__unguarded_insertion_sort_aux(first, last, (int *)0, comp);
}
template void __unguarded_insertion_sort<int *, Rva005E4300Cmp>(int *, int *, Rva005E4300Cmp);
}
