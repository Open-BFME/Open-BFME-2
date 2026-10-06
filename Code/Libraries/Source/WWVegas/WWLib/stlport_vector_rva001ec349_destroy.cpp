// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAVRva001EC349@@@_STL@@YAXPAVRva001EC349@@0@Z @0x001ECFC6 25B.
// Range destroy over 0x24-byte Rva001EC349 via rowed dtor 0x001EC349 stride 0x24.
// Evidence: callee rowed 0x001EC349; callers 0x001ECFF9 0x001ED026; same 25B loop as rowed 0x0015209B.
#include <vector>

class Rva001EC349
{
public:
	~Rva001EC349();
private:
	unsigned char m_pad[0x24];
};

template void _STL::_Destroy<Rva001EC349 *>(Rva001EC349 *, Rva001EC349 *);
