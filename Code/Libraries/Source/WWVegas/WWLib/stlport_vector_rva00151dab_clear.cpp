// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_clear@?$vector@VRva00151DAB@@V?$allocator@VRva00151DAB@@@_STL@@@_STL@@IAEXXZ, retail 0x0015218A, 30 bytes.
// Vector<Rva00151DAB> clear via rowed _Destroy 0x0015209B and free 0x00030830.
// Same 30B Destroy-plus-free shape as rowed _M_clear 0x00153BCF for Rva00153729.
#include <vector>

class Rva00151DAB
{
public:
	~Rva00151DAB();

private:
	unsigned char m_pad[8];
};

template void _STL::vector<Rva00151DAB>::_M_clear();
