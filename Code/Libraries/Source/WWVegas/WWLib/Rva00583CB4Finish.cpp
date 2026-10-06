// ?rva00583CB4@Rva005843DA@@QAEXH@Z
// partial score=0.93 date=2026-09-29
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00583CB4@Rva005843DA@@QAEXH@Z 44B @0x00583CB4: virtual slot 11
// (offset 0x2C) of vtable 0x0086FC80 installed by rowed ctor 0x005843DA.
// Bounds-checked store of 3 to field +0 of the 28-byte element at the given
// index in the vector at +8; early-out for negative or out-of-range indices.
#include <vector>

struct Rva00583CE0Elem
{
	int m_00;
	char m_pad04[0x0C];
	bool m_10;
	char m_pad11[0x03];
	unsigned int m_14;
	char m_pad18[0x04];
};

class Rva005D6FCC
{
public:
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva005843DA : public Rva005D6FCC
{
public:
	void rva00583CB4(int i);
private:
	_STL::vector<Rva00583CE0Elem> m_vec; // +8
	bool m_flag; // +0x14
};

void Rva005843DA::rva00583CB4(int i)
{
	if (i >= 0 && i < m_vec.size())
		m_vec[i].m_00 = 3;
}
