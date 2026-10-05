// cl: /O1
//
// ?rva004F9EF3@@YAXPAURva004F6352@@0URva004F6352Cmp@@@Z @0x004F9EF3 70B.
// Sort driver for 12-byte Rva004F6352 records: skip empty ranges, count the
// elements by byte span over 12, halve down to a depth, run the pinned
// 0x004F95A8 sort phase with twice the depth, then the rowed
// __final_insertion_sort 0x004F8C99. Both templates are declared but never
// defined here so the calls bind to the rowed copies.
struct Rva004F6352;

struct Rva004F6352Cmp
{
};

namespace _STL
{
template<class _RI, class _C>
void __final_insertion_sort(_RI __first, _RI __last, _C __comp);
}

void rva004F95A8(Rva004F6352 *first, Rva004F6352 *last, int a, int depth, Rva004F6352Cmp comp);

void rva004F9EF3(Rva004F6352 *first, Rva004F6352 *last, Rva004F6352Cmp comp)
{
	if (first == last)
		return;
	int n = ((char *)last - (char *)first) / 12;
	int depth = 0;
	while (n != 1) {
		++depth;
		n >>= 1;
	}
	rva004F95A8(first, last, 0, depth + depth, comp);
	_STL::__final_insertion_sort(first, last, comp);
}
