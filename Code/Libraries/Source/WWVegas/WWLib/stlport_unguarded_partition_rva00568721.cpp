// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_partition@PAPAXPAXURva00568721Cmp@@@_STL@@YAPAPAXPAPAX0PAXURva00568721Cmp@@@Z @0x00568DB7 73B: quicksort partition over void* keys
// with the rowed stdcall comparator at 0x00568721 via thiscall twin Rva00568721Cmp::operator(). Scan up while comp(*first,pivot),
// scan down while comp(pivot,*last), swap on cross, return the split. Evidence: same 73B shape as rowed 0x004231A0 int partition;
// caller 0x00569E91 passes (first,last,pivot,comp) in the 123B sort-loop shape; both callees rowed to 0x00568721; lea ecx for
// thiscall comp plus two pushes matches 0x004231A0 precedent; unblocks 0x00569E91.
// The stateless Rva00568721Cmp call and rowed Rva00568721Less compare the same
// key fields (+0x44 word, then +0x47 high nibble). Their two pointer arguments
// share the same stack layout/cleanup; thiscall's empty-functor ECX is ignored
// by the stdcall row. Bind the old spelling without changing this body.
#pragma comment(linker, "/alternatename:??RRva00568721Cmp@@QBE_NPBX0@Z=?Rva00568721Less@@YG_NPBX0@Z")
struct Rva00568721Cmp
{
	bool operator()(const void *a, const void *b) const;
};

namespace _STL
{

template <class ForwardIter1, class ForwardIter2>
__forceinline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	void *temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template void **__unguarded_partition<void **, void *, Rva00568721Cmp>(void **, void **, void *, Rva00568721Cmp);

}
