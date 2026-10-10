// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAUBfmeNarrowRecord000BFDC7@@IU1@@_STL@@YAPAUBfmeNarrowRecord000BFDC7@@PAU1@IABU1@ABU__false_type@0@@Z, retail 0x000C0B60, 37 bytes.
// Fill loop over 0x20-byte narrow records through the rowed _Construct at
// 0x000C0A9D. Sibling of the 0x000C0B15 fill for 0x2c-byte records.
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

struct BfmeNarrowRecord000BFDC7
{
	unsigned int m_word0;
	_STL::basic_string<char> m_text;
	unsigned int m_word1;
	unsigned int m_word2;
	unsigned int m_word3;
	unsigned int m_word4;
	BfmeNarrowRecord000BFDC7();
	BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &o);
};

namespace _STL
{
template <> void _Construct<BfmeNarrowRecord000BFDC7, BfmeNarrowRecord000BFDC7>(BfmeNarrowRecord000BFDC7 *, const BfmeNarrowRecord000BFDC7 &);
}

template class _STL::vector<BfmeNarrowRecord000BFDC7, _STL::allocator<BfmeNarrowRecord000BFDC7> >;
