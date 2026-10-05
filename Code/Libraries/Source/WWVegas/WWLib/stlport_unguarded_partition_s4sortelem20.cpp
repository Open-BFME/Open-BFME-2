// cl: /DNDEBUG /MD /EHsc /O1
//
// Ported from Open-BFME-1 Libraries/Source/WWVegas/WWLib/stlport_unguarded_partition_s4sortelem20.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??$__unguarded_partition@PAUS4SortElem20@@U1@US4Cmp002EB8E0@@@_STL@@YAPAUS4SortElem20@@PAU1@0U1@US4Cmp002EB8E0@@@Z 0x00337655 (101B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// Open-BFME5: _STL::__unguarded_partition<S4SortElem20 *, S4SortElem20,
// S4Cmp002EB8E0>, retail 0x002EAA30, 287 bytes. The body carried only a
// machine byte-dump row.
//
// STLport's partition loop over the same twenty-byte string-keyed element the
// neighbouring insertion-sort and unguarded-linear-insert bodies already
// landed. The comparator is the inlined StringBase memcmp against the empty
// sentinel at 0x0107388B. The pivot is by-value so the frame has an unwind
// record; its destructor stays out of line through the ILT at 0x0002AB2B
// (body 0x002E9E10). The swap is the two-argument helper at ILT 0x0003A76F
// (body 0x002EA1A0) because the element is not trivially copyable.

extern "C" int memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		T m_bfmeData[1];
	};

	Header *m_bfmeHeader;

public:
	// Out of line: retail calls the shared StringBase<char>::compare at
    // 0x000069D6; an inline body here would emit a private copy of it.
    int compare(const StringBase<T> &other) const;

	friend struct S4SortElem20;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20(const S4SortElem20 &other);
	~S4SortElem20();
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem20 &left,
		const S4SortElem20 &right) const
	{
		return left.m_bfmeName.compare(right.m_bfmeName) < 0;
	}
};

void bfmeIterSwapS4SortElem20(S4SortElem20 *left, S4SortElem20 *right);

namespace _STL
{

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
		bfmeIterSwapS4SortElem20(first, last);
		++first;
	}
}

template S4SortElem20 *__unguarded_partition<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0);

}
