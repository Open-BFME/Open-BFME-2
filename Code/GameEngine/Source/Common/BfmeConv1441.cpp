// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026E00 (57B) is STLport 4.6's find_if (_algobase.c:193) over
// reverse_iterator<const char *> with _Eq_char_bound, dispatching to the
// random-access __find_if at 0x00025CE0 (BfmeConv1471.cpp).
#include <string>
namespace _STL {
template reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Eq_char_bound<char_traits<char> >);
}
