// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 allocator<T>::allocate for an opaque one-byte element view.
// Target identity is unresolved; the Rva name is a codegen view only. The
// 23-byte body fills the exact Ghidra gap between 0xAD7A8/37 and 0xAD7E4/34,
// in the STLport vector helper block beside allocator<short> at 0xAD722.
#include <vector>

struct Rva000AD7CDElement
{
    unsigned char m_byte;
};

template Rva000AD7CDElement *_STL::allocator<Rva000AD7CDElement>::allocate(
    unsigned int, const void *) const;
