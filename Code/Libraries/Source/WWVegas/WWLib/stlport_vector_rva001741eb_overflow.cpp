// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@URva001741EBElement@@V?$allocator@URva001741EBElement@@@_STL@@@_STL@@IAEXPAURva001741EBElement@@ABU3@ABU__false_type@2@I_N@Z
// @ 0x00173EF9 189B: vector<Rva001741EBElement> fill overflow, 48-byte element.
// Evidence: chain from just-landed __uninitialized_copy 0x001733D0; callees rowed allocate 0x003F40D3 copy 0x001733D0 fill_n 0x001733F6 free 0x00030830 plus Construct pin 0x00173351; caller push_back at 0x00174218.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
struct Rva001741EBElement {
  int a[12];
};
namespace _STL {
template <> void _Construct<Rva001741EBElement, Rva001741EBElement>(Rva001741EBElement *, const Rva001741EBElement &);
}
template void _STL::vector<Rva001741EBElement>::_M_insert_overflow(Rva001741EBElement *, const Rva001741EBElement &, const _STL::__false_type &, unsigned int, bool);
