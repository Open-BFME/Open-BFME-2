// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001ED01E@Rva001ED01E@@QAEXXZ @0x001ED01E 30B.
// Manual destroy-plus-free of Rva001EC349 range at +0..+4 via rowed 0x001ECFC6 plus rowed free 0x00030830.
// Evidence: callees rowed 0x001ECFC6 0x00030830; caller 0x001ED1D3 in 0x001ED13A.
#include <vector>
#include <stdlib.h>

class Rva001EC349
{
public:
	~Rva001EC349();
};

class Rva001ED01E
{
public:
	void rva001ED01E();
private:
	Rva001EC349 *m_00;
	Rva001EC349 *m_04;
};

void Rva001ED01E::rva001ED01E()
{
	_STL::_Destroy(m_00, m_04);
	Rva001EC349 *p = m_00;
	if (p != 0)
		free(p);
}
