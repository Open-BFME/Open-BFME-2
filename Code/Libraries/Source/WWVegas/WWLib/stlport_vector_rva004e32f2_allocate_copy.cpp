// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@QAE@ABV01@@Z, retail 0x0052D4F5, 96 bytes.
// _STL::vector<Rva004E32F2> copy ctor via Vector_base count plus rowed uninit-copy 0x0052D4CF.
// Evidence: chain lane calls just-landed 0x0052D4CF; count via idiv 0x18; same 96B shape as rowed 0x000BCE36.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class Rva004E32F2
{
public:
	Rva004E32F2();
	Rva004E32F2(const Rva004E32F2 &o);
private:
	char m_pad[0x18];
};
#include <vector>
template class _STL::vector<Rva004E32F2, _STL::allocator<Rva004E32F2> >;
