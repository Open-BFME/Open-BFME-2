// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__adjust_heap@PAVRva004F6093Holder@@HV1@URva002BBC1CCmp@@@_STL@@YAXPAVRva004F6093Holder@@HHV1@URva002BBC1CCmp@@@Z @0x002B589F 165B
// STLport sift-down over the 4-byte refcounted Rva004F6093Holder with the
// out-of-line comparator Rva002BBC1CCmp. Retail 0x002B589F sits between
// __unguarded_insertion_sort_aux 0x002B5873 and copy_backward 0x002B5944.
// Evidence: callers __pop_heap 0x002B63A9 and __make_heap 0x002B6408; sift loop
// compares via pinned 0x002B367C and moves via rowed holder operator=
// 0x002B2F97; value copy for __push_heap inlines as mov plus inc of refcount
// at +0xB0; tail calls rowed __push_heap 0x002B459E; value-temp dtor releases
// TargetRef at +0xAC through rowed fastcall 0x0007DEEF.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva002BBC1CTarget
{
	char m_pad00[0xAC];
	TargetRef00217D4C m_ac; // +0xAC, references at +0xB0
};

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other);

private:
	Rva002BBC1CTarget *m_ptr;
};

struct Rva002BBC1CCmp
{
	bool operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			--secondChild;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<Rva004F6093Holder *, int, Rva004F6093Holder,
	Rva002BBC1CCmp>(Rva004F6093Holder *, int, int, Rva004F6093Holder,
	Rva002BBC1CCmp);

}
