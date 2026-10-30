// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 _algobase.c:193 find_if, instantiated for const char * with
// _Eq_char_bound<char_traits<char> > (_ctraits_fns.h:42), the search
// _Not_within_traits::operator() (_string.h:97) runs for every character.
// Native 0x00026C60/34B forwards to the random-access __find_if at 0x00025B80
// with a temporary iterator-category tag as its fourth argument.

#include <string>

namespace _STL {
template const char *find_if(const char *, const char *, _Eq_char_bound<char_traits<char> >);
}
