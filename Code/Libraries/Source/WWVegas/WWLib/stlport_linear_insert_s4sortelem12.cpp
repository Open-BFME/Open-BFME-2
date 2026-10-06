// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// ??$__linear_insert@PAUS4SortElem12@@U1@US4Cmp002E1690@@@_STL@@YAXPAUS4SortElem12@@0U1@US4Cmp002E1690@@@Z @0x00332028 111B
// Evidence: pin name; LINK BONUS via 0x0033215E; caller insertion_sort 0x00332183; callees rowed 0x00331E0D 0x00331759 0x00331962 0x00036410 plus pinned unguarded 0x00331A46.
template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
	~StringBase(void) { releaseBuffer(); }
	T *m_bfmeData;

	friend struct S4SortElem12;
};

struct S4SortElem12
{
	int m_bfmeA;
	StringBase<char> m_bfmeName;
	char m_bfmeC;
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeA < right.m_bfmeA;
	}
};

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right);

#include <new.h>

class Rva002DFC30
{
	int m_00;
	void *m_04;
	char m_08;
public:
	Rva002DFC30(const Rva002DFC30 &other) throw();
};

Rva002DFC30 *Rva00331E0DCopy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result);

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp)
{
	if (comp(val, *first))
	{
		Rva00331E0DCopy((Rva002DFC30 *)first, (Rva002DFC30 *)last, (Rva002DFC30 *)(last + 1));
		new ((void *)first) Rva002DFC30(*(const Rva002DFC30 *)&val);
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690);

}
