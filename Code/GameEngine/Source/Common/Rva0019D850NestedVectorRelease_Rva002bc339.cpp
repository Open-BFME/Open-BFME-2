// cl: -EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc_alloconly
// stlport46
// Retail 0x002BC339: nested-vector count constructor (100 bytes).
// The 60-byte allocation base at 0x005C8C37 uses BFME's allocator<char>.
// /EHs preserves cleanup state across the C allocator calls, as retail does.
//
// Target layout evidence: the element range destructor at 0x002BB6BE steps
// 20 bytes and calls 0x002B6B4C, which frees the vector starting at offset 8.
// The type's original name is unknown; these are local layout views only.
#include <vector>

struct Rva002BC339Value
{
    int m_words[5];
};

// Use the existing typed range-destroy provider for this compatible layout.
// Its body and element destructor are owned by stlport_destroy_member20_2bb6be.cpp.
struct Rva002BB6BE20Rec;
namespace _STL {
template <> void _Destroy<Rva002BB6BE20Rec *>(Rva002BB6BE20Rec *, Rva002BB6BE20Rec *);

template <> inline vector<Rva002BC339Value>::~vector()
{
    _Destroy(reinterpret_cast<Rva002BB6BE20Rec *>(this->_M_start),
             reinterpret_cast<Rva002BB6BE20Rec *>(this->_M_finish));
}
}

template _STL::vector<_STL::vector<Rva002BC339Value> >::vector(unsigned int);
