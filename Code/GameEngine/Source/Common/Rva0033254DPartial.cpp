// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva0033254DPartial@@YAXPAUS4SortElem12@@00US4Cmp002E1690@@@Z @0x0033254D 27B
// 5-arg __partial_sort forwarder over rowed 0x0033234F (4th Tp* null).
// Evidence: unlock lane calls 0x0033234F row; 5 pushes plus add esp,0x14 plus ret; caller 0x0033268E; neighbours stlport_vector /O1/G7 and stlport_vector_allocate /O1.
struct S4SortElem12
{
	char m_pad[12];
};
struct S4Cmp002E1690
{
	int m_slot;
};
namespace _STL
{
template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator, RandomAccessIterator, RandomAccessIterator, Tp *, Compare);
}
void __cdecl Rva0033254DPartial(S4SortElem12 *first, S4SortElem12 *middle, S4SortElem12 *last, S4Cmp002E1690 comp)
{
	_STL::__partial_sort<S4SortElem12 *, S4SortElem12, S4Cmp002E1690>(first, middle, last, (S4SortElem12 *)0, comp);
}
