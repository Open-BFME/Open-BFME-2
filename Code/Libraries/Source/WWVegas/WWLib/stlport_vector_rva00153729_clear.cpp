// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_clear@?$vector@URva00153729@@V?$allocator@URva00153729@@@_STL@@@_STL@@IAEXXZ, retail 0x00153BCF, 30 bytes.
// Vector<Rva00153729> clear via rowed _Destroy 0x153BB6 and free 0x30830.
// Evidence: push [esi+4] push [esi] call 0x153BB6 mov esi [esi] test free; same 30B shape as rowed _M_clear 0x15373C; caller at 0x153CF8.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct Rva00153729
{
	~Rva00153729();
	unsigned char m_data[0x4C];
};
template void _STL::vector<Rva00153729>::_M_clear();

// Whole-class instantiation: its members that are rowed were placed at retail
// by masked search of this TU's emitted bodies plus REL32 callee agreement.
template class _STL::vector<Rva00153729,_STL::allocator<Rva00153729> >;
