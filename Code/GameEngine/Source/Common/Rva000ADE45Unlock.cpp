// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// _STL::__copy_ptrs<BfmeStringRecord00063BE4 *, BfmeStringRecord00063BE4 *>,
// retail 0x000ADE45, 29 bytes.
// STLport 4.5.3's pointer copy for a type with non-trivial assignment: it
// forwards to the rowed __copy 0x00332F29 with a random-access tag and a null
// distance. Retail's only caller 0x00335C9B pushes the address of an empty
// temporary as a fourth argument, STLport's by-reference __false_type tag,
// and the sibling __copy_backward_ptrs 0x000ADECE has this shape under its
// by-reference STLport name. The bfmealloc shim spells __copy_ptrs by value,
// so this unit declares the vendored by-reference signature and instantiates it.
#include <algorithm>
struct BfmeStringRecord00063BE4 {
	unsigned int word0, word1, word2, word3, word4, word5, word6;
	char text[4];
	unsigned char tail0, tail1;
};
namespace _STL {
template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter first, _InputIter last, _OutputIter result, const __false_type &)
{
	return __copy(first, last, result, random_access_iterator_tag(), (int *)0);
}
template BfmeStringRecord00063BE4 *__copy_ptrs(BfmeStringRecord00063BE4 *, BfmeStringRecord00063BE4 *, BfmeStringRecord00063BE4 *, const __false_type &);
}
