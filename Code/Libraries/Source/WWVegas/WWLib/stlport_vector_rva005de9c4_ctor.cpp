// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva005DE9C4@@QAE@I@Z @0x005DE9C4 31B
// Gap ctor: vtable 0x00876AFC plus Gen vector at +4 via rowed 0x005DE870 plus zero at +0x10.
// Evidence: between rows of stlport_vector_rva005de5b5_dtor.cpp; callee rowed 0x005DE870;
// vtable no name yet g_00C76AFC; callers 0x005DEA09 0x005DEC0C 0x005DEE4B.
#include <vector>

struct Gen003AA0D0
{
	virtual ~Gen003AA0D0();
	char m_pad[0x18 - 4];
};

extern const void *const g_00C76AFC[];

class Rva005DE9C4
{
public:
	Rva005DE9C4(unsigned int n);
	virtual ~Rva005DE9C4();
private:
	_STL::vector<Gen003AA0D0, _STL::allocator<Gen003AA0D0> > m_04;
	int m_10;
};

Rva005DE9C4::Rva005DE9C4(unsigned int n)
	: m_04(n)
{
	m_10 = 0;
}
