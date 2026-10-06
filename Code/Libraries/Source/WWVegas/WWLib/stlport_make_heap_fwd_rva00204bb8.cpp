// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00207BAAWrap@@YAXPAH0VRva00204BB8@@@Z @0x00207BAA 25B
// make_heap forwarding wrapper: pushes two trailing zeros alongside
// (first,last,comp) into the rowed __make_heap worker 0x002074FD.
// Evidence: chain via landed make_heap; same forwarder pattern as
// Rva002C531BWrap pushing two trailing zeros; caller 0x00209A73.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIter, class Compare>
void __make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp);

}

typedef void (__cdecl *MakeHeap3)(int *, int *, Rva00204BB8);
typedef void (__cdecl *MakeHeap5)(int *, int *, Rva00204BB8, int, int);

void __cdecl Rva00207BAAWrap(int *first, int *last, Rva00204BB8 comp)
{
	MakeHeap3 fn3 = (MakeHeap3)&_STL::__make_heap<int *, Rva00204BB8>;
	MakeHeap5 fn5 = (MakeHeap5)fn3;
	fn5(first, last, comp, 0, 0);
}
