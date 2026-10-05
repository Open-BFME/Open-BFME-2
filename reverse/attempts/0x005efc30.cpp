// ?_M_fill_insert@?$vector@URva005EFD53Element@@V?$allocator@URva005EFD53Element@@@_STL@@@_STL@@QAEXPAURva005EFD53Element@@IABU3@@Z
// partial score=0.93 date=2026-10-05
// cl: /G7 /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@URva005EFD53Element@@V?$allocator@URva005EFD53Element@@@_STL@@@_STL@@QAEXPAURva005EFD53Element@@IABU3@@Z @0x005EFC30 265B: vector _M_fill_insert for 4-byte refcounted element.
// Evidence: calls rowed uninitialized_fill_n 0x005EF4A5 plus pinned __uninitialized_copy 0x005EF3FE plus rowed copy_backward 0x005EF46B plus rowed fill 0x005EF488 plus rowed overflow 0x005EFB7E plus rowed Release 0x0007DEEF; caller 0x005EFDE9 resize; same shape as STLport _vector.c _M_fill_insert.
#include <vector>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva005EEFD2Target
{
	int m_00;
	TargetRef00217D4C m_04;
};

class Rva005EEFD2
{
public:
	Rva005EEFD2 &operator=(const Rva005EEFD2 &other);
private:
	Rva005EEFD2Target *m_ptr;
};

struct Rva005EFD53Element
{
	Rva005EEFD2Target *m_ptr;
	Rva005EFD53Element(const Rva005EFD53Element &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr != 0)
			++m_ptr->m_04.references;
	}
	~Rva005EFD53Element()
	{
		if (m_ptr != 0)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_04);
	}
	Rva005EFD53Element &operator=(const Rva005EFD53Element &other);
};

namespace _STL
{
template <> __declspec(nothrow) void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *__p, const Rva005EFD53Element &__val);
}

template void _STL::vector<Rva005EFD53Element>::_M_fill_insert(
	Rva005EFD53Element *, unsigned int, const Rva005EFD53Element &);
