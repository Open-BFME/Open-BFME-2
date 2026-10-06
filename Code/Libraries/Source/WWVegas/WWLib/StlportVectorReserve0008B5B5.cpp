// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@URva0008DE1CElement@@V?$allocator@URva0008DE1CElement@@@_STL@@@_STL@@QAEXI@Z @0x0008B5B5 125B
// Evidence: unlock lane; 24B element via push 0x18 pop idiv; callees _M_allocate_and_copy 0x0008A1D0
// allocate 0x00395944 (shared 24B fold) _free 0x00030830; capacity check then
// allocate vs allocate_and_copy; prev StlportVectorOverflow0008B503 sibling flags.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct Rva0008DE1CElement
{
    char m_pad[24];

public:
    Rva0008DE1CElement(const Rva0008DE1CElement &that);
};

template void _STL::vector<Rva0008DE1CElement>::reserve(unsigned int);
