// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Free pair<AsciiString,AsciiString>::operator< at 0x00206BCF (65B).
// Lexicographic less (first, then second) over two direct primitive
// operator< calls plus the second-pair call, each cleaning its two pushes
// with pop-pop like the getter TUs. The primitive resolves through its pin
// at 0x5598C. AsciiString is the 4B m_data object; pair comes from real
// STLport <utility> so the mangling is compiler-attested.

#include <utility>

typedef bool Bool;

#include "ascii_string.h"

Bool operator<(const AsciiString &left, const AsciiString &right);

Bool operator<(const _STL::pair<AsciiString, AsciiString> &a,
    const _STL::pair<AsciiString, AsciiString> &b)
{
    return (a.first < b.first) || (!(b.first < a.first) && (a.second < b.second));
}
