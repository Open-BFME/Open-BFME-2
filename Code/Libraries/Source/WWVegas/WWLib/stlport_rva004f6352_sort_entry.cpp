// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: the sort entry and insertion tail of STLport's sort over the
// 12-byte Rva004F6352 records whose quicksort half is in stlport_rva004f6352_sort.cpp.
// Bodies are accepted only where byte-equal by the REL32 graph from sort 0x004F9EF3.

#include <algorithm>
#include <vector>

#include "../../Apt/AptRefTarget.h"

// The matched 0x002174A4 body (as in PAUTreeHintRef00217D4CRva004F9565.cpp),
// visible so cl knows the assignments keep no reference to the inserted
// value: retail's insert holds val.m_ptr in EDI across them.
inline __declspec(noinline) TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other)
{
	if (this != &other)
	{
		if (other.m_ptr)
			++other.m_ptr->references;
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
		m_ptr = other.m_ptr;
	}
	return *this;
}

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

// Own the matched 35-byte 0x004F6352 assignment here: the two leading words
// and +8 TreeHintRef agree with the stride-12 callers at 0x004F6C32/0x004F6876.
// Same-TU visibility preserves the native insertion callers' register use.
__declspec(noinline) inline Rva004F6352 &Rva004F6352::operator=(const Rva004F6352 &other)
{
	m_ptr = other.m_ptr;
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}

struct Rva004F6352Cmp
{
	bool operator()(const Rva004F6352 &a, const Rva004F6352 &b) const
	{
		int ka = a.m_ptr->m_key;
		int kb = b.m_ptr->m_key;
		return ka > kb;
	}
};

template void _STL::sort<Rva004F6352 *, Rva004F6352Cmp>(Rva004F6352 *, Rva004F6352 *, Rva004F6352Cmp);

