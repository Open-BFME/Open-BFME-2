// cl: /O1 /G7 /MD
struct Rva005E4300Cmp
{
	bool operator()(int a, int b) const;
};
namespace _STL
{
template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare comp);
}
void __cdecl rva005E50A7(int *first, int *last, Rva005E4300Cmp comp)
{
	int n = (char *)last - (char *)first;
	if ((n & ~3) <= 4)
		return;
	int m = n;
	for (;;) {
		_STL::pop_heap(first, last, comp);
		last = (int *)((char *)last - 4);
		m -= 4;
		if ((m & ~3) <= 4)
			break;
	}
}
