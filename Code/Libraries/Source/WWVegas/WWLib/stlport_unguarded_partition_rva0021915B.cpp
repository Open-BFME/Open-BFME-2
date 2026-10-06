// cl: /Ireference/shims/bfme2_ascii /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_partition@PAURva0021915B@@U1@URva0021B753@@@_STL@@ @0x0021C6CB 107B partition with rowed comparator 0x0021B753 and rowed swap 0x0021ACB9 plus pivot release via 0x00036410.
// Evidence: chain lane all callees rowed; first/last stride 8 plus bool-first comparator plus swap callers prove Rva0021915B family; same partition shape as rowed 0x004231A0 with EH for non-trivial pivot. Donor vendor/stlport/stl/_algo.c:__unguarded_partition.
#include "ascii_string.h"
class Rva0021915B {
public:
	Rva0021915B &operator=(const Rva0021915B &other);
	friend struct Rva0021B753;
private:
	AsciiString m_str;
	bool m_byte;
};
struct Rva0021B753 {
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};
void __cdecl Rva0021ACB9Swap(Rva0021915B *a, Rva0021915B *b);
namespace _STL {
template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first, RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true) {
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		Rva0021ACB9Swap(first, last);
		++first;
	}
}
template Rva0021915B *__unguarded_partition<Rva0021915B *, Rva0021915B, Rva0021B753>(Rva0021915B *, Rva0021915B *, Rva0021915B, Rva0021B753);
}
