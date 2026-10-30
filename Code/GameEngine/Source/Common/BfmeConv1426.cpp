// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026E40 (90B) is STLport 4.6's __find_first_of (_algobase.c:264)
// over const char * with _Eq_traits<char_traits<char> > (_ctraits_fns.h:31),
// the search under string::find_first_of(const char *, size_type, size_type)
// const at 0x000276B0; the empty predicate is the fifth stack word.
#include <string>

namespace _STL {
template const char *__find_first_of(const char *, const char *, const char *, const char *, _Eq_traits<char_traits<char> >);
}
