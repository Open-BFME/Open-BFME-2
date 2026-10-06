// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__pop_heap@PAVRva004F6093Holder@@V1@URva002BBC1CCmp@@H@_STL@@YAXPAVRva004F6093Holder@@00V1@URva002BBC1CCmp@@PAH@Z @0x002B6368 105B
// 6-arg pop-heap worker over the 4-byte refcounted Rva004F6093Holder with the
// out-of-line comparator Rva002BBC1CCmp. Retail 0x002B6368 sits between
// __unguarded_insertion_sort 0x002B6351 and __make_heap 0x002B63D1 of the sort
// 0x002BBC1C family. Evidence: pin read from the retail REL32 in
// __pop_heap_aux 0x002B641F; *result = *first calls the rowed holder
// operator= 0x002B2F97; value copy for __adjust_heap inlines as mov plus inc
// of refcount at +0xB0; tail calls the pinned __adjust_heap 0x002B589F; the
// value-temp dtor releases TargetRef at +0xAC through the rowed fastcall
// 0x0007DEEF. Callers are __pop_heap_aux 0x002B641F and __partial_sort
// 0x002B92E9.
#include <algorithm>

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

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIter first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
	RandomAccessIter result, Tp val, Compare comp, Distance *)
{
	*result = *first;
	__adjust_heap(first, 0, (int)(last - first), val, comp);
}

template void __pop_heap<Rva004F6093Holder *, Rva004F6093Holder,
	Rva002BBC1CCmp, int>(Rva004F6093Holder *, Rva004F6093Holder *,
	Rva004F6093Holder *, Rva004F6093Holder, Rva002BBC1CCmp, int *);

}
