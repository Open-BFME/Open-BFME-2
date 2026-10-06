// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 Libraries/Source/WWVegas/WWLib/stlport_sort_s4sortelem20.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva002EBEF0@@YAXPAUS4SortElem20@@0US4Cmp002EB8E0@@@Z 0x00337DA9 (70B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME5: STLport sort driver over twenty-byte S4 records, retail 0x002EBEF0.

struct S4SortElem20
{
	char m_bfmeBytes[20];
};

struct S4Cmp002EB8E0
{
	int m_bfmeState;
};

void Rva002EBEF0Intro(S4SortElem20 *first,
	S4SortElem20 *last, S4SortElem20 *, int depth,
	S4Cmp002EB8E0 comp);

namespace _STL
{
template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first,
	RandomAccessIter last, Compare comp);
}

void Rva002EBEF0(S4SortElem20 *first,
	S4SortElem20 *last, S4Cmp002EB8E0 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		Rva002EBEF0Intro(first, last, (S4SortElem20 *)0,
			k * 2, comp);
		_STL::__final_insertion_sort(first, last, comp);
	}
}
