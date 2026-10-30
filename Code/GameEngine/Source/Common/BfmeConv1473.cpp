// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00026340 (758B) is STLport 4.6's search (_algobase.c:207) over
// reverse_iterator<const char *> with _Eq_traits<char_traits<char> >, the
// reverse subsequence scan __find_end (0x00026FF0, BfmeConv1466.cpp) runs for
// string::rfind(const char *, size_type, size_type) const.
#include <string>

namespace _STL {
template reverse_iterator<const char *> search(reverse_iterator<const char *>, reverse_iterator<const char *>, reverse_iterator<const char *>, reverse_iterator<const char *>, _Eq_traits<char_traits<char> >);
}
