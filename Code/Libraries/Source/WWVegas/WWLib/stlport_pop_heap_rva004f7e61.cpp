// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport pop_heap<Rva004F6966 *, Rva004F81DBGreater> @0x004F7E61 and its
// heap chain: __pop_heap_aux 0x004F7780, __pop_heap 0x004F728A,
// __adjust_heap 0x004F6D81, __push_heap 0x004F6C64. The only caller is the
// queue pop at 0x004F81DB (vector at +0, one-byte empty comparator at +0xC).
// The 12-byte element holds the refcounted TreeHintRef00217D4C handle at +0
// (copied by the rowed copy constructor 0x004F6966, assigned by the rowed
// assignment 0x004F64FC, released inline through ReleaseTreeHintRef00217D4C)
// and two ints; the comparator orders by the int at +8 with greater-than.
// Element and comparator names are address-derived placeholders.
#include <algorithm>

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

struct Rva004F6966
{
	TreeHintRef00217D4C m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
	Rva004F6966 &operator=(const Rva004F6966 &other);
	~Rva004F6966() {}
};

struct Rva004F81DBGreater
{
	bool operator()(const Rva004F6966 &x, const Rva004F6966 &y) const
	{
		return x.m_08 > y.m_08;
	}
};

template void _STL::pop_heap<Rva004F6966 *, Rva004F81DBGreater>(Rva004F6966 *, Rva004F6966 *, Rva004F81DBGreater);
template void _STL::push_heap<Rva004F6966 *, Rva004F81DBGreater>(Rva004F6966 *, Rva004F6966 *, Rva004F81DBGreater);

// Retail 0x004F64FC is rowed as ??4Rva004F64FC but serves as the assignment
// this heap family calls; alias our assignment name to that row.
#pragma comment(linker, "/alternatename:??4Rva004F6966@@QAEAAU0@ABU0@@Z=??4Rva004F64FC@@QAEAAU0@ABU0@@Z")

