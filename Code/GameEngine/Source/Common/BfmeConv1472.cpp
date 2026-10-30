// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x000260A0 (596B) is STLport 4.6's random-access __find_if
// (_algobase.c:136) over reverse_iterator<const char *> with _Neq_char_bound,
// the core under string::find_last_not_of(char, size_type) const: four-way
// unroll, reverse steps and the tail switch. /Ob2 keeps reverse_iterator's
// temporaries as retail does.
#include <string>
namespace _STL {
template reverse_iterator<const char *> __find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Neq_char_bound<char_traits<char> >, const random_access_iterator_tag &);
}
