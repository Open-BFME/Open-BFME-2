// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAUBfmeNarrowRecord00079C23@@IU1@@_STL@@YAPAUBfmeNarrowRecord00079C23@@PAU1@IABU1@ABU__false_type@0@@Z, retail 0x000C0B15, 37 bytes.
// Fill loop over 0x2c-byte narrow records through the rowed _Construct at
// 0x000C0A70. Same 37B shape as the rowed BDF17 fill at 0x000C0ACA.
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
#include <string>

struct BfmeNarrowRecord00079C23
{
	_STL::basic_string<char> m_text0;
	_STL::basic_string<char> m_text1;
	_STL::basic_string<char> m_text2;
	unsigned int m_word0;
	unsigned int m_word1;
	BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o);
};

namespace _STL
{
template <> void _Construct<BfmeNarrowRecord00079C23, BfmeNarrowRecord00079C23>(BfmeNarrowRecord00079C23 *, const BfmeNarrowRecord00079C23 &);
}

template class _STL::vector<BfmeNarrowRecord00079C23, _STL::allocator<BfmeNarrowRecord00079C23> >;
