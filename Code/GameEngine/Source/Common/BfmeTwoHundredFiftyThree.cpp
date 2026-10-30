// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026F40 (34B) is STLport 4.6's find_if (_algobase.c:193) over
// const char * with _Neq_char_bound, forwarding to the random-access __find_if
// at 0x00025F00 (BfmeConv1468.cpp) with a temporary iterator-category tag.
#include <string>

namespace _STL {
template const char *find_if(const char *, const char *, _Neq_char_bound<char_traits<char> >);
}
