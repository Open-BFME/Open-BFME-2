// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 64-byte BfmeVectorRecord000BDF17 vector allocation/copy helper at RVA 0xC24A0.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>
// Opaque 12B AsciiString-vector member: only the out-of-line range-destroy
// call appears in the record dtor, pinned at 0x2CC70 (GenericObjectCreationNugget
// precedent). Using vector<AsciiString> here would resolve to the 0x36410 fold
// and miss retail by one reloc.
struct RvaVecAscii
{
	~RvaVecAscii();

private:
	unsigned char m_data[12];
};
struct BfmeVectorRecord000BDF17 {
	RvaVecAscii names;
    AsciiString text0, text1;
    unsigned int word14, word18, word1C, word20, word24, word28;
    unsigned char flag2C, flag2D;
    unsigned int word30, word34, word38;
    unsigned char flag3C;
    BfmeVectorRecord000BDF17();
    BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord000BDF17, BfmeVectorRecord000BDF17>(BfmeVectorRecord000BDF17 *, const BfmeVectorRecord000BDF17 &);
}
template class _STL::vector<BfmeVectorRecord000BDF17, _STL::allocator<BfmeVectorRecord000BDF17> >;
