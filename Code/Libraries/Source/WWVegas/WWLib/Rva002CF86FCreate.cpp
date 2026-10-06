// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002CF86FCreate@@YGPAXPBURva002CF13B@@@Z @0x002CF86F 34B.
// Node create: allocates a 0x18-byte block through the rowed byte allocator
// 0x000307F0, placement-copies an Rva002CF13B value at block+0x10 through the
// rowed null-guarded 0x002CF36E, returns the block, ret 4. Same 0x10 value
// offset as the 0x002CF84D family for the 8-byte record. Callers at 0x002CFA57
// 0x0033C114 0x0033C12F unblocks 0x0033C0E1 and 0x002CFA4E.
#include <map>

namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct Rva002CF13B;
void __cdecl Rva002CF36ECopy(Rva002CF13B *dest, const Rva002CF13B *src);

void *__stdcall Rva002CF86FCreate(const Rva002CF13B *src)
{
	char *block = _STL::allocator<char>::allocate(0x18, 0);
	Rva002CF36ECopy((Rva002CF13B *)(block + 0x10), src);
	return block;
}
