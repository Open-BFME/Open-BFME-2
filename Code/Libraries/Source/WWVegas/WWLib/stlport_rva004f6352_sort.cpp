// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The quicksort half of STLport's sort over 12-byte Rva004F6352 records,
// ordered by descending key: the introsort loop (0x004F95A8, 136B) and the
// bodies it reaches, the partition and the partial_sort/heap chain (0x004F7022
// .. 0x004F9211). Target evidence: the loop divides by 12 and calls the median
// rowed by hand at 0x004F60EC (Rva004F60ECMedian.cpp); every body copies and
// assigns records through the rowed Rva004F6352 copy constructor (0x004F62DE)
// and assignment (0x004F6352), and releases the handle at +8 through
// ReleaseTreeHintRef00217D4C. The records and the handle are declared as in
// Rva004F6352Swap.cpp, whose swap this instantiation reproduces.
//
// The order compares the int at +8 of the object each record points to,
// read into locals: only that spelling gives retail's partition, which tests
// the first element before entering its scan loop. sort (0x004F9EF3) and its
// insertion tail are not instantiated: their __unguarded_linear_insert
// (0x004F6EB1) keeps the value's pointer in a register across the assignment
// calls, which this compiler does not do for a parameter whose address is
// taken.
//
// The records' copy_backward (0x004F76A1) and the vector's range erase
// (0x004F89A8) are instantiated too: their helpers __copy_backward_ptrs
// (0x004F70A5) and __copy_ptrs (0x004F713E) call the rowed __copy_backward and
// __copy, and the erase destroys the tail through the _Destroy loop rowed by
// hand at 0x004F838C.

#include <algorithm>
#include <vector>

#include "../../Apt/AptRefTarget.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);


// ??1TreeHintRef00217D4C@@QAE@XZ present-unmatched
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

struct MedianKey004F60EC
{
	int _00[2];
	int m_key;
};

struct Rva004F6352
{
	MedianKey004F60EC *m_ptr;
	int m_04;
	TreeHintRef00217D4C m_08;
	Rva004F6352(const Rva004F6352 &other);
	Rva004F6352 &operator=(const Rva004F6352 &other);
	~Rva004F6352() {}
};

struct Rva004F6352Cmp
{
	bool operator()(const Rva004F6352 &a, const Rva004F6352 &b) const
	{
		int ka = a.m_ptr->m_key;
		int kb = b.m_ptr->m_key;
		return ka > kb;
	}
};

template void _STL::__introsort_loop<Rva004F6352 *, Rva004F6352, int, Rva004F6352Cmp>(
	Rva004F6352 *, Rva004F6352 *, Rva004F6352 *, int, Rva004F6352Cmp);

template Rva004F6352 *_STL::copy_backward<Rva004F6352 *, Rva004F6352 *>(Rva004F6352 *, Rva004F6352 *, Rva004F6352 *);

typedef _STL::vector<Rva004F6352> Rva004F6352Vector;
template Rva004F6352Vector::iterator Rva004F6352Vector::erase(Rva004F6352Vector::iterator, Rva004F6352Vector::iterator);
