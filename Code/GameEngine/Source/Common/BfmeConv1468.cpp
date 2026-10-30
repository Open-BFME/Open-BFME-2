// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00025F00 (408B) is STLport 4.6's random-access __find_if
// (_algobase.c:136) over const char * with _Neq_char_bound (_ctraits_fns.h),
// the core under string::find_first_not_of(char, size_type) const: four-way
// unrolled compare loop, then the 3/2/1 remainder switch.
#include <string>

namespace _STL {
template const char *__find_if(const char *, const char *, _Neq_char_bound<char_traits<char> >, const random_access_iterator_tag &);
}
