// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00029850 (206B) is STLport 4.6 basic_string<char>::rfind(const char *,
// size_type, size_type) const (_string.c:367): npos when the needle is longer,
// min(len, pos) for an empty needle, else find_end with _Eq_traits (0x00027F30,
// BfmeTwoHundredSixtyFour.cpp).
#include <string>

extern template const char *_STL::find_end(const char *, const char *, const char *, const char *, _STL::_Eq_traits<_STL::char_traits<char> >);

namespace _STL {
template string::size_type string::rfind(const char *, string::size_type, string::size_type) const;
}
