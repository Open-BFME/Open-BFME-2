// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??$__unguarded_insertion_sort_aux@PAUBfmeAssignRecord32@@U1@P6A_NABU1@0@Z@_STL@@YAXPAUBfmeAssignRecord32@@00P6A_NABU1@1@Z@Z @0x00173841 46B insertion sort aux for vector<BfmeAssignRecord32>.
// Loops over [first last) with 0x20 stride; copies each via rowed 0x00173731 then calls.
/// Rowed linear insert 0x0017351C with pred at +0x14; dummy NULL at +0x10 via forwarder 0x001739CD.
/// Evidence: chain from just-landed linear insert; callers at 0x001739DB; prev/next STL helpers.
/// Layout 32B proven by rowed copy/dtor; honest STL instantiation (no guessed args).
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	BfmeAssignRecord32(const BfmeAssignRecord32 &other);
	~BfmeAssignRecord32();
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &other);
};
typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
void __cdecl Rva0017351CInsert(BfmeAssignRecord32 *last, BfmeAssignRecord32 value, BfmePred comp);
namespace _STL {
template <class RandomAccessIter, class T, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T *, Compare comp)
{
	for (BfmeAssignRecord32 *i = (BfmeAssignRecord32 *)first; i != (BfmeAssignRecord32 *)last; ++i)
		Rva0017351CInsert((BfmeAssignRecord32 *)i, *(const BfmeAssignRecord32 *)i, (BfmePred)comp);
}
template void __unguarded_insertion_sort_aux<BfmeAssignRecord32 *, BfmeAssignRecord32, BfmePred>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmePred);
}
