// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: the sort entry and insertion tail of STLport's sort over the
// 12-byte Rva004F6352 records whose quicksort half is in stlport_rva004f6352_sort.cpp.
// Bodies are accepted only where byte-equal by the REL32 graph from sort 0x004F9EF3.

#include <algorithm>
#include <vector>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};

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

template void _STL::sort<Rva004F6352 *, Rva004F6352Cmp>(Rva004F6352 *, Rva004F6352 *, Rva004F6352Cmp);

