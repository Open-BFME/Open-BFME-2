// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$vector@URva004F691E@@V?$allocator@URva004F691E@@@_STL@@@_STL@@QAE@XZ retail 0x004F8A17 30B
// Evidence: chain via Destroy 0x004F838C; same Destroy-plus-free shape as Rva004F69C3 dtor 0x004F8832 63B; callers 0x004F8BA2 0x004F8F61.
#include <vector>

struct Rva004F691E
{
	~Rva004F691E() throw();
	char m_pad[12];
};

template _STL::vector<Rva004F691E, _STL::allocator<Rva004F691E> >::~vector();
