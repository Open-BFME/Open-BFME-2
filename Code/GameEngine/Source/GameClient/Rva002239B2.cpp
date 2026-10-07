// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002239B2@Rva002239B2@@QAEXPBXPAX@Z @0x002239B2 48B
// ?rva002239E2@Rva002239B2@@QAEXPBXPAX@Z @0x002239E2 24B
// Target boundaries are confirmed by each body's ret 8. The bytes at 0x2239B2
// address a 20-byte table at this+0x70, store the second pointer through its
// returned slot, then call rowed STLport set::insert at this+0x84. The adjacent
// 0x2239E2 body repeats the table lookup/store through this+0x90. The shared
// owner layout is inferred from those offsets; both identities remain address-derived.
// The table lookup target 0x2235F3 is pinned under an address-derived name from
// the observed calls only; its body is a separate blocked candidate and is not recovered here.
#include <set>

struct Rva001408C0Target
{
	int opaque;
};

typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > PtrSet001408C0;

class Rva002235F3
{
private:
	char m_opaque[0x14];

public:
	void *rva002235F3(const void *key);
};

class Rva002239B2
{
public:
	void rva002239B2(const void *key, Rva001408C0Target *value);

private:
	char m_pad[0x70];
	Rva002235F3 m_table70;
	PtrSet001408C0 m_set84;
	Rva002235F3 m_table90;
};

void Rva002239B2::rva002239B2(const void *key, Rva001408C0Target *value)
{
	void *record = m_table70.rva002235F3(key);
	*(void **)record = value;
	m_set84.insert(value);
}

