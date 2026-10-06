// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__reverse@PAH@_STL@@YAXPAH0ABUrandom_access_iterator_tag@0@@Z,
// retail 0x002334F8 (33 bytes). _STL::__reverse<int*> random-access overload:
// for (; first < last; ++first) iter_swap(first, --last). iter_swap and swap
// inline, so the body is a 33B manual word-swap loop with no calls.
// Evidence: caller 0x00233A26 pushes first last and tag ref then add esp 0xc;
// next-row sibling __rotate<int*> shares flags; donor STLport 4.5.3 _algo.h.
// ??$reverse@PAH@_STL@@YAXPAH0@Z,
// retail 0x00233A26 (24 bytes). _STL::reverse<int*> wrapper: builds the
// random_access tag on the stack and tail-calls __reverse<int*> above.
// Evidence: calls rowed __reverse 0x002334F8; caller 0x00233B85; same flags.
#include <algorithm>
template void _STL::__reverse<int *>(int *, int *, const _STL::random_access_iterator_tag &);
template void _STL::reverse<int *>(int *, int *);
