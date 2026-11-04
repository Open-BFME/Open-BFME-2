// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00287F76Element>::_M_insert_overflow, retail 0x00287B4D, 184 bytes.
// Masked-identical to landed BfmeE8 overflow at 0x00057C80 (8-byte stride,
// inline free). Same no-EH / bfmealloc recipe as stlport_vector_e8_allocate_copy.cpp.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Match the owning fire-logic TU's six-byte payload and eight-byte stride.
// Its spread pass stores a cell pointer and a 16-bit pending heat value.
struct Rva00287F76Element
{
    void *m_cell;
    unsigned short m_value;
};
// Retail copies six bytes of each eight-byte slot through this rowed owner.
void __cdecl Rva002861B0Copy(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __forceinline void
_Construct<Rva00287F76Element, Rva00287F76Element>(
    Rva00287F76Element *dest, const Rva00287F76Element &source)
{ Rva002861B0Copy(dest, &source); }
}
template class _STL::vector<Rva00287F76Element, _STL::allocator<Rva00287F76Element> >;
