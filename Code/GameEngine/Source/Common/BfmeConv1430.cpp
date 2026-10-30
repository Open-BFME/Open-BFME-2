// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026EA0 (147B) is STLport 4.6's __find_first_of (_algobase.c:264)
// over reverse_iterator<const char *> and const char * with
// _Eq_traits<char_traits<char> > (_ctraits_fns.h:31), the search under
// string::find_last_of(const char *, size_type, size_type) const at 0x00027740.
#include <string>

namespace _STL {
template reverse_iterator<const char *> __find_first_of(reverse_iterator<const char *>, reverse_iterator<const char *>, const char *, const char *, _Eq_traits<char_traits<char> >);
}
