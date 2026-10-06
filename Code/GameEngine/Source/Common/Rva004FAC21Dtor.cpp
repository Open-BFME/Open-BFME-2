// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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
#include "ascii_string.h"

struct Rva004FABE2
{
	~Rva004FABE2();
};

class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &s);

private:
	AsciiString m_s;
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

Rva004FAC21::~Rva004FAC21()
{
}
