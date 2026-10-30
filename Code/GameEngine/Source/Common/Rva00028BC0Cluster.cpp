// cl: /DNDEBUG /MD /EHsc /Od /D_STLP_USE_STATIC_LIB
// stlport46
// Two run wrappers built on the char_traits<char>::length helper at 0x00006F30.
// 0x00028BC0 is STLport 4.5.3's basic_string<char>::find(const char *, size_type)
// const: it forwards (s, pos, length(s)) to the three-argument find at
// 0x00027540. The plain /Od build keeps both calls out of line, as retail does.
// 0x00028CC0 is STLport 4.6's find_last_of(const char *, size_type) const,
// forwarding (s, pos, length(s)) to find_last_of(const char *, size_type,
// size_type) at 0x00027740 (BfmeThingPF.cpp).
#include <string>

namespace _STL {
// Retail's three-argument find and its search core are emitted by
// stlport_reverse_string_search.cpp under /Od /Ob2; this unit only calls them.
template <> string::size_type string::find(const char *, string::size_type, string::size_type) const;
template <> const char *search(const char *, const char *, const char *, const char *, _Eq_traits<char_traits<char> >);
template string::size_type string::find(const char *, string::size_type) const;
}

extern template _STL::string::size_type _STL::string::find_last_of(const char *, _STL::string::size_type, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::find_last_of(const char *, string::size_type) const;
}
