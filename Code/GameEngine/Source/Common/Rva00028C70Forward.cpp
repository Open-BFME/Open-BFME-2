// cl: /Od
// stlport46
// Retail 0x00028C70 (29B) is STLport 4.6's inline basic_string<char>::
// find_first_of(char, size_type) const (_string.h:1105), forwarding to
// find(char, size_type) const at 0x000274D0.
#include <string>

// find's body is instantiated in BfmeConv1301.cpp; do not emit a second copy.
extern template _STL::string::size_type _STL::string::find(char, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::find_first_of(char, string::size_type) const;
}
