// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// _STL::sort family over the 8-byte Rva0040CB11Entry (int plus refcounted
// holder) with a descending float comparator, retail 0x0040CF36..0x0040F497.
//
// Target evidence: sort 0x0040F454 (one caller 0x0040F501) reaches every
// placed body through REL32 calls that agree with this TU's own call graph:
// __introsort_loop 0x0040F34E -> __median 0x0040D0C1, partial_sort 0x0040E952;
// __final_insertion_sort 0x0040E908 -> __insertion_sort 0x0040E77A ->
// __linear_insert 0x0040E333 -> __unguarded_linear_insert 0x0040D170 and
// copy_backward 0x0040DA59; __unguarded_insertion_sort 0x0040D98E -> _aux
// 0x0040D598; partial_sort -> make_heap 0x0040DD0A -> __make_heap 0x0040DA0A
// -> __adjust_heap 0x0040D5C5 -> __push_heap 0x0040D1CE; sort_heap 0x0040E3B4
// -> pop_heap 0x0040DD23 -> __pop_heap_aux 0x0040DA74 -> __pop_heap
// 0x0040D9A5. Element copies call the rowed Rva0040CB11Entry copy ctor
// 0x004F6335; element assignment calls 0x0040D0A4 (rowed as
// Rva0040D0A4Entry::operator=, the same 8-byte entry under a second
// placeholder name). The inlined value destructor releases the TargetRef at
// +0xAC of the pointee through the rowed fastcall 0x0007DEEF.
// The comparator reads the float at +8 of each holder's pointee and orders
// descending (comiss/ja in __median); its out-of-line copy 0x0040CF36 is
// unreferenced in retail as here and unique in .text.
//
// The entry and holder copy ctors and operator= are defined here (the
// retail TU saw them as header inlines): with their bodies visible cl knows
// the calls do not touch the by-value element, so __unguarded_linear_insert,
// __push_heap and __linear_insert keep the element's pointee in a callee-saved
// register across the operator= and copy-ctor calls and drop the null test
// before the final release, as retail does; declared only, every one of them
// reloaded the pointee from its stack slot. The copies this TU emits of the
// two operator= bodies are byte-identical to the rows at 0x0040D0A4 and
// 0x002B2F97 and are rowed as their ICF aliases; its swap and __copy_backward
// instantiations are byte-identical to the hand-named rows 0x0040D11C and
// 0x0040D251, and copy_backward's two 29-byte wrappers fold onto 0x0040D66B
// (left unrowed: an ICF pair). Structural inference: the comparator reads
// each side through a pointer local and then a float local; the float locals
// keep both operands in xmm registers (comiss reg,reg) in the heap bodies,
// and the pointer locals give __unguarded_partition its pivot pointer in ecx
// and __partial_sort its middle iterator in ebx, as retail has them (with the
// float locals alone each of those two bodies came out with one register
// pair swapped). __unguarded_partition's iter_swap is the swap instantiation
// at 0x0040D11C, rowed under a hand name and pinned here.
#include <algorithm>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[8];
	float m_value; // +0x08
	char m_pad0C[0xAC - 0xC];
	TargetRef00217D4C m_ac; // +0xAC
};

class Rva004F6093Holder
{
	friend struct Rva0040F454Cmp;

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
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}

private:
	Rva0040F454Target *m_ptr;
};

class Rva0040CB11Entry
{
	friend struct Rva0040F454Cmp;

public:
	Rva0040CB11Entry(const Rva0040CB11Entry &other) : m_first(other.m_first), m_second(other.m_second)
	{
	}
	Rva0040CB11Entry &operator=(const Rva0040CB11Entry &other)
	{
		m_first = other.m_first;
		m_second = other.m_second;
		return *this;
	}

private:
	int m_first;
	Rva004F6093Holder m_second;
};

struct Rva0040F454Cmp
{
	bool operator()(const Rva0040CB11Entry &a, const Rva0040CB11Entry &b) const
	{
		const Rva0040F454Target *p = a.m_second.m_ptr;
		float x = p->m_value;
		const Rva0040F454Target *q = b.m_second.m_ptr;
		float y = q->m_value;
		return x > y;
	}
};

template void _STL::sort<Rva0040CB11Entry *, Rva0040F454Cmp>(Rva0040CB11Entry *, Rva0040CB11Entry *, Rva0040F454Cmp);
