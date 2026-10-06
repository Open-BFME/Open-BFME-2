// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PBUBfmeNarrowRecord00079C23@@PAU1@H@_STL@@YAPAUBfmeNarrowRecord00079C23@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z @0x000C379B 50B.
// STL __copy over 0x2c-byte BfmeNarrowRecord00079C23 via rowed operator= 0x7A22A.
#include <vector>
#include <string>

struct BfmeNarrowRecord00079C23
{
	_STL::basic_string<char> m_text0;
	_STL::basic_string<char> m_text1;
	_STL::basic_string<char> m_text2;
	unsigned int m_word0;
	unsigned int m_word1;
	BfmeNarrowRecord00079C23 &operator=(const BfmeNarrowRecord00079C23 &o);
};

template BfmeNarrowRecord00079C23 *_STL::__copy<const BfmeNarrowRecord00079C23 *, BfmeNarrowRecord00079C23 *, int>(
	const BfmeNarrowRecord00079C23 *first, const BfmeNarrowRecord00079C23 *last, BfmeNarrowRecord00079C23 *result,
	const _STL::random_access_iterator_tag &, int *);

template BfmeNarrowRecord00079C23 *_STL::copy<BfmeNarrowRecord00079C23 *, BfmeNarrowRecord00079C23 *>(
	BfmeNarrowRecord00079C23 *first, BfmeNarrowRecord00079C23 *last, BfmeNarrowRecord00079C23 *result);
