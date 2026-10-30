// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026FF0 (144B) is STLport 4.6's bidirectional __find_end
// (_algobase.c:319) over const char * with _Eq_traits<char_traits<char> >:
// reverse search (0x00026340, BfmeConv1473.cpp), then step back by the
// needle's length.
#include <string>

extern template _STL::reverse_iterator<const char *> _STL::search(_STL::reverse_iterator<const char *>, _STL::reverse_iterator<const char *>, _STL::reverse_iterator<const char *>, _STL::reverse_iterator<const char *>, _STL::_Eq_traits<_STL::char_traits<char> >);

namespace _STL {
template const char *__find_end(const char *, const char *, const char *, const char *, const bidirectional_iterator_tag &, const bidirectional_iterator_tag &, _Eq_traits<char_traits<char> >);
}
