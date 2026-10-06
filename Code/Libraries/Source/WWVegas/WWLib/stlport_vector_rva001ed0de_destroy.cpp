// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAVRva001ED0DE@@@_STL@@YAXPAVRva001ED0DE@@0@Z @0x001ED34A 25B.
// Range destroy over 0x24-byte Rva001ED0DE via rowed dtor 0x001ED0DE stride 0x24.
// Evidence: callee rowed 0x001ED0DE; callers 0x001ED37D 0x001ED3AA; same 25B loop as rowed 0x001ECFC6.
#include <vector>

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
private:
	unsigned char m_pad[0x24];
};

template void _STL::_Destroy<Rva001ED0DE *>(Rva001ED0DE *, Rva001ED0DE *);
