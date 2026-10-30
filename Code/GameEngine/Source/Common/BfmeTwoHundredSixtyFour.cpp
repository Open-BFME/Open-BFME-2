// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00027F30 (44B) is STLport 4.6's find_end (_algobase.c:345) over
// const char * with _Eq_traits<char_traits<char> >, forwarding to the
// bidirectional __find_end at 0x00026FF0 (BfmeConv1466.cpp) with temporary
// iterator-category tags.
#include <string>

extern template const char *_STL::__find_end(const char *, const char *, const char *, const char *, const _STL::bidirectional_iterator_tag &, const _STL::bidirectional_iterator_tag &, _STL::_Eq_traits<_STL::char_traits<char> >);

namespace _STL {
template const char *find_end(const char *, const char *, const char *, const char *, _Eq_traits<char_traits<char> >);
}
