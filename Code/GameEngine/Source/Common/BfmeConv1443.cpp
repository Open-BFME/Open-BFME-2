// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026F70 (57B) is STLport 4.6's find_if (_algobase.c:193) over
// reverse_iterator<const char *> with _Neq_char_bound, dispatching to the
// random-access __find_if at 0x000260A0 (BfmeConv1472.cpp).
#include <string>
namespace _STL {
template reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Neq_char_bound<char_traits<char> >);
}
