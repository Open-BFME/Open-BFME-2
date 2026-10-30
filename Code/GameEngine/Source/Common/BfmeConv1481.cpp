// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x000275C0 (235B) is STLport 4.6 basic_string<char>::rfind(char,
// size_type) const (_string.c:385): empty -> npos, last = begin() +
// min(len - 1, pos) + 1, reverse find_if with _Eq_char_bound (0x00026E00,
// BfmeConv1441.cpp), npos on a miss.
#include <string>
extern template _STL::reverse_iterator<const char *> _STL::find_if(_STL::reverse_iterator<const char *>, _STL::reverse_iterator<const char *>, _STL::_Eq_char_bound<_STL::char_traits<char> >);
namespace _STL {
template string::size_type string::rfind(char, string::size_type) const;
}
