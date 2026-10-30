// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Retail 0x00028C90 (43B) is STLport 4.6 basic_string<char>::find_last_of(const
// basic_string &, size_type) const (_string.h), forwarding (s._M_start, pos,
// s.size()) to find_last_of(const char *, size_type, size_type) at 0x00027740
// (BfmeThingPF.cpp).
#include <string>

extern template _STL::string::size_type _STL::string::find_last_of(const char *, _STL::string::size_type, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::find_last_of(const string &, string::size_type) const;
}
