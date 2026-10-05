// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001ED3A2@Rva001ED3A2@@QAEXXZ @0x001ED3A2 30B.
// Manual destroy-plus-free of Rva001ED0DE range at +0..+4 via rowed 0x001ED34A plus rowed free 0x00030830.
// Evidence: callees rowed 0x001ED34A 0x00030830; caller 0x001ED50F in 0x001ED476; same 30B shape as rowed 0x001ED01E.
#include <stdlib.h>

namespace _STL
{
template <class I> void __cdecl _Destroy(I first, I last);
}

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
};

class Rva001ED3A2
{
public:
	void rva001ED3A2();
private:
	Rva001ED0DE *m_00;
	Rva001ED0DE *m_04;
};

void Rva001ED3A2::rva001ED3A2()
{
	_STL::_Destroy(m_00, m_04);
	Rva001ED0DE *p = m_00;
	if (p != 0)
		free(p);
}
