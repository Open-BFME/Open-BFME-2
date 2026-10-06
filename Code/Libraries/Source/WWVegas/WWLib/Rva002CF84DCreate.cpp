// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002CF84DCreate@@YGPAXPBURva002CF120@@@Z @0x002CF84D 34B.
// Node create: allocates a 0x24-byte block through the rowed byte allocator
// 0x000307F0, placement-copies an Rva002CF120 value at block+0x10 through the
// rowed null-guarded 0x002CF35C, returns the block, ret 4. Same 0x10 value
// offset as the NoCase _M_create_node family; the tree template identity is
// unproven so this stays an honest free function (cf. Rva002CF571Loop).
// Callers at 0x002CFA39 0x0033BFD9 0x0033BFF4.
#include <map>

namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct Rva002CF120;
void __cdecl Rva002CF35CCopy(Rva002CF120 *dest, const Rva002CF120 *src);

void *__stdcall Rva002CF84DCreate(const Rva002CF120 *src)
{
	char *block = _STL::allocator<char>::allocate(0x24, 0);
	Rva002CF35CCopy((Rva002CF120 *)(block + 0x10), src);
	return block;
}
