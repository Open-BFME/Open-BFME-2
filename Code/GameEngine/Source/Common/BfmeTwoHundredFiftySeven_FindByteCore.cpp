// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 _algobase.c:136 __find_if, random-access form, instantiated for
// const char * with _Eq_char_bound<char_traits<char> > (_ctraits_fns.h:42).
// Native 0x00025B80/349B: four-way unrolled compare loop, then the 3/2/1
// remainder switch; the predicate's char_traits::eq is inlined at each site and
// the unused iterator-category reference stays a dead fourth argument. Its one
// caller is find_if at 0x00026C60, which _Not_within_traits::operator()
// (_string.h:97) reaches.

#include <string>

namespace _STL {
template const char *__find_if(const char *, const char *, _Eq_char_bound<char_traits<char> >, const random_access_iterator_tag &);
}
