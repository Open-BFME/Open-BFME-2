// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005838B5@Rva005838B5@@QAEXXZ RVA 0x005838B5 39B
// Evidence: leaf lane; stores vtable 0x0086FC30; calls rowed base
//   ??0Rva005D6FCC@@QAE@PAX@Z 0x005D6FCC and rowed Vector_base BfmeE16
//   0x00211E58; ret 4 single-arg ctor with vector at +8.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva005838B5 : public Rva005D6FCC
{
public:
	Rva005838B5(void *held);
	virtual ~Rva005838B5();
private:
	_STL::vector<BfmeE16> m_vec; // +8
};

Rva005838B5::Rva005838B5(void *held)
	: Rva005D6FCC(held), m_vec(_STL::allocator<BfmeE16>())
{
}
