// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 _algobase.c:136 __find_if, random-access form, instantiated for
// const char * with _Not_within_traits<char_traits<char> > (_string.h:87): the
// forward find_first_not_of search. Native 0x00027FE0/534B unrolls four
// predicate tests per step and finishes with the 3/2/1 remainder switch; each
// inlined predicate calls find_if 0x00026C60 and compares with _M_last.

#include <string>

namespace _STL {
template const char *__find_if(const char *, const char *, _Not_within_traits<char_traits<char> >, const random_access_iterator_tag &);
}
