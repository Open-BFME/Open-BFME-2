// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// Three STLport 4.6 basic_string<char> forwarders (_string.h) that hand
// (s._M_start, pos, s.size()) to the three-argument member:
//   0x00028B90 find(const basic_string &, size_type) const -> 0x00027540
//   0x0002A270 rfind(const basic_string &, size_type) const -> 0x00029850
//   0x0002ACF0 find_last_not_of(const basic_string &, size_type) const -> 0x0002A420
#include <string>

// The three-argument members are instantiated in stlport_reverse_string_search.cpp
// (find, find_last_not_of) and BfmeConv1480.cpp (rfind).
extern template _STL::string::size_type _STL::string::find(const char *, _STL::string::size_type, _STL::string::size_type) const;
extern template _STL::string::size_type _STL::string::rfind(const char *, _STL::string::size_type, _STL::string::size_type) const;
extern template _STL::string::size_type _STL::string::find_last_not_of(const char *, _STL::string::size_type, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::find(const string &, string::size_type) const;
template string::size_type string::rfind(const string &, string::size_type) const;
template string::size_type string::find_last_not_of(const string &, string::size_type) const;
}
