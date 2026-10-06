// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAVRva00151DAB@@@_STL@@YAXPAVRva00151DAB@@0@Z, retail 0x0015209B, 25 bytes.
// Range destroy over 8-byte Rva00151DAB elements via rowed dtor 0x00151DAB stride 8.
// Callers 0x00152118 vector dtor plus 0x0015218A clear plus 0x00152157 erase.
// Same 25B loop shape as rowed BfmeVectorRecord000BDF17 _Destroy at 0x000C37CD
// and Rva0048130E _Destroy at 0x00481595.
#include <vector>

class Rva00151DAB
{
public:
	~Rva00151DAB();

private:
	unsigned char m_pad[8];
};

template void _STL::_Destroy<Rva00151DAB *>(Rva00151DAB *, Rva00151DAB *);
