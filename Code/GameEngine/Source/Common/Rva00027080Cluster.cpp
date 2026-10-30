// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 _string.h:97 _Not_within_traits<char_traits<char> >::operator(),
// the find_first_not_of / find_last_not_of predicate: find_if over
// [_M_first, _M_last) with _Eq_char_bound(__x), true when the search reaches
// _M_last. Native 0x00027080/65B is its out-of-line copy; the find_if it calls
// is 0x00026C60.

#include <string>

namespace _STL {
template bool _Not_within_traits<char_traits<char> >::operator()(const char &) const;
}
