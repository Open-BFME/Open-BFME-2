// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??$__unguarded_insertion_sort@PAUBfmeAssignRecord32@@P6A_NABU1@0@Z@_STL@@YAXPAUBfmeAssignRecord32@@0P6A_NABU1@1@Z@Z @0x001739CD 23B insertion sort entry for vector<BfmeAssignRecord32>.
// Forwards first last plus NULL type tag plus pred to rowed aux 0x00173841.
// Evidence: chain from just-landed aux; frameless 4-push forwarder with push 0 dummy; caller at 0x001740CB.
// Layout 32B proven by siblings; honest STL instantiation.
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
};
typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
namespace _STL {
template <class RandomAccessIter, class T, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T *, Compare comp);
template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__unguarded_insertion_sort_aux(first, last, (BfmeAssignRecord32 *)0, comp);
}
template void __unguarded_insertion_sort<BfmeAssignRecord32 *, BfmePred>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmePred);
}
