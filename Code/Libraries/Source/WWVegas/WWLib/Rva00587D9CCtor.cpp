// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00587D9C@@QAE@PAX0@Z, retail 0x00587D9C 49B.
// Derived ctor: base Rva005D6FCC (vptr + held void* at +4, rowed 0x005D6FCC)
// then vector<BfmeE16> at +8 via rowed Vector_base 0x00211E58, bool at +0x14
// set, void* at +0x18 stored. Caller 0x00587F39; vtable 0x00C6FF38.
// Same recipe as rowed ??0Rva00586D8E 0x00586D8E with flag true.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva00587D9C : public Rva005D6FCC
{
public:
	Rva00587D9C(void *held, void *other);
	virtual ~Rva00587D9C();
private:
	_STL::vector<BfmeE16> m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

Rva00587D9C::Rva00587D9C(void *held, void *other)
	: Rva005D6FCC(held), m_vec(_STL::allocator<BfmeE16>())
{
	m_other = other;
	m_flag = true;
}
