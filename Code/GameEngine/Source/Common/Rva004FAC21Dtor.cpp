// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DBFME_STRINGBASE_PUBLIC_DTOR
//
// ??1Rva004FAC21@@UAE@XZ, retail 0x004FADB8 (60 bytes).
// Derived dtor of the rowed Rva004FAC21 ctor class (vtable 0x008633B0,
// base Rva004FA830 vtable 0x008633A0): destroys the vector at +8 via the
// rowed ??1Rva004FABE2, then the inlined base string at +4 via
// releaseBuffer. The derived entry vptr store is suppressed with novtable
// (retail stores only the base vtable after the vector destruction).
// Its ??_G 0x004FAD9C is slot 0 of vtable 0x008633B0. Evidence: vtable
// store 0x00C633A0 plus callers/callees in the packet; layout from the
// rowed ctor TU Rva004FAC21Ctor.cpp.
#include "Rva004FA830.h"

struct Rva004FABE2
{
	~Rva004FABE2();
};

inline Rva004FA830::~Rva004FA830()
{
}

class __declspec(novtable) Rva004FAC21 : public Rva004FA830
{
public:
	Rva004FAC21(const StringBase<char> &s);
	virtual ~Rva004FAC21();

private:
	Rva004FABE2 m_v;
	int m_x;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva004FAC21::~Rva004FAC21()
{
}

// ?bfmeAnchorRva004FAC21Dtor absent-from-retail
void bfmeAnchorRva004FAC21Dtor(Rva004FAC21 *p)
{
	p->Rva004FAC21::~Rva004FAC21();
}
