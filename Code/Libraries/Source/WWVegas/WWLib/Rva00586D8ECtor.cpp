// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00586D8E@@QAE@PAX0@Z, retail 0x00586D8E 49B.
// Derived ctor: base Rva005D6FCC (vptr + held void* at +4, rowed 0x005D6FCC)
// then vector<BfmeE16> at +8 via rowed Vector_base 0x00211E58, bool at +0x14
// cleared, void* at +0x18 stored. Caller 0x00586E21 news 0x1C and passes
// (arg, this); vtable 0x00C6FD90 slot0 deleting dtor 0x00586E35.
// BfmeE16 is the 16B size stand-in from stlport_vector_e16_o1.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva00586D8E : public Rva005D6FCC
{
public:
	Rva00586D8E(void *held, void *other);
	virtual ~Rva00586D8E();
private:
	_STL::vector<BfmeE16> m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

Rva00586D8E::Rva00586D8E(void *held, void *other)
	: Rva005D6FCC(held), m_vec(_STL::allocator<BfmeE16>())
{
	m_other = other;
	m_flag = false;
}
