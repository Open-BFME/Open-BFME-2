// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00207539Pop@@YAXPAH0HVRva00204BB8@@@Z @0x00207539 30B
// pop_heap wrapper over the rowed __pop_heap 0x002074D4: last-1 as
// result/value plus trailing zero; same pattern as Rva0021AD3FPopHeap.
// Evidence: chain via landed pop_heap; caller 0x00207BD1 in 0x00207BC3.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
    RandomAccessIter result, Tp val, Compare comp);

}

typedef void (__cdecl *PopHeap5)(int *, int *, int *, int, Rva00204BB8);
typedef void (__cdecl *PopHeap6)(int *, int *, int *, int, Rva00204BB8, int);

void __cdecl Rva00207539Pop(int *first, int *last, int, Rva00204BB8 comp)
{
	PopHeap5 fn5 = (PopHeap5)&_STL::__pop_heap<int *, int, Rva00204BB8>;
	PopHeap6 fn6 = (PopHeap6)fn5;
	int *newLast = last - 1;
	fn6(first, newLast, newLast, *newLast, comp, 0);
}
