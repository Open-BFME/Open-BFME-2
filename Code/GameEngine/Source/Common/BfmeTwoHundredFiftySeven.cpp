// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 _algobase.c:193 find_if, instantiated for const char * with
// _Not_within_traits<char_traits<char> > (_string.h:87), the search
// find_first_not_of (_string.c:439) runs. Native 0x00029EB0/38B forwards the
// two-pointer predicate to the random-access __find_if at 0x00027FE0 with a
// temporary iterator-category tag.

#include <string>

namespace _STL {
template const char *find_if(const char *, const char *, _Not_within_traits<char_traits<char> >);
}
