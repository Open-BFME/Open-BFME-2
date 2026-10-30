// cl: /DNDEBUG /MD /EHsc /Od /D_STLP_USE_STATIC_LIB
// stlport46
// Two (const char *, size_type) forwarders of STLport basic_string<char>, each
// passing (s, pos, char_traits<char>::length(s)) to its three-argument form.
// The plain /Od build keeps length at 0x00006F30 out of line, as retail does.
// 0x0002ACC0 is find_first_not_of(const char *, size_type) const, forwarding to
// 0x0002A3A0 (BfmeS1155.cpp); 0x0002AD20 is find_last_not_of(const char *,
// size_type) const, forwarding to 0x0002A420
// (stlport_reverse_string_search.cpp).
#include <string>

extern template _STL::string::size_type _STL::string::find_first_not_of(const char *, _STL::string::size_type, _STL::string::size_type) const;
extern template _STL::string::size_type _STL::string::find_last_not_of(const char *, _STL::string::size_type, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::find_first_not_of(const char *, string::size_type) const;
template string::size_type string::find_last_not_of(const char *, string::size_type) const;
}
