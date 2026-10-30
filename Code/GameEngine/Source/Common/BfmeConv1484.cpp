// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x000278A0 (241B) is STLport 4.6 basic_string<char>::
// find_last_not_of(char, size_type) const (_string.c:480): empty -> npos,
// last = begin() + min(len - 1, pos) + 1, reverse find_if with _Neq_char_bound
// (0x00026F70, BfmeConv1443.cpp), npos on a miss.
#include <string>
extern template _STL::reverse_iterator<const char *> _STL::find_if(_STL::reverse_iterator<const char *>, _STL::reverse_iterator<const char *>, _STL::_Neq_char_bound<_STL::char_traits<char> >);
namespace _STL {
template string::size_type string::find_last_not_of(char, string::size_type) const;
}
