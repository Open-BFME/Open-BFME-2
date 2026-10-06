// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@URva004F6986@@V?$allocator@URva004F6986@@@_STL@@@_STL@@QAEXI@Z, retail 0x004F8B21, 104 bytes.
// Evidence: same bytes as vector<Rva004F69C3>::reserve except its _M_clear call
// reads 0x004F89DB, the rowed holder clear that destroys 8-byte Rva004F6986
// elements through the rowed Rva004F8373Destroy, not that vector's rowed
// _M_clear at 0x004F89F9. Calls read _M_allocate_and_copy 0x004F6BD8 and the
// 8-byte allocator 0x00523D6C.
#include <vector>
struct Rva004F6986
{
	~Rva004F6986();
	char m_pad[8];
};

template void _STL::vector<Rva004F6986, _STL::allocator<Rva004F6986> >::reserve(size_t);
