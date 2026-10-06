// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?Rva0021ACB9Swap@@YAXPAVRva0021915B@@0@Z, retail 0x0021ACB9, 74 bytes.
// Swap 8-byte Rva0021915B entries via temp pair<const AsciiString,char>
// copy 0x005117F6 plus rowed Rva assign 0x0021915B plus releaseBuffer
// 0x00036410. Callers at 0x0021C711 0x0021BA41. Prev Rva dtor next map.
#include "ascii_string.h"
namespace _STL {
template <class T1, class T2> struct pair {
    T1 first;
    T2 second;
    pair(const pair &);
};
}
typedef _STL::pair<const AsciiString, char> Pair0021ACB9;
class Rva0021915B {
public:
    Rva0021915B &operator=(const Rva0021915B &other);
};

void __cdecl Rva0021ACB9Swap(Rva0021915B *a, Rva0021915B *b)
{
    Pair0021ACB9 tmp(*reinterpret_cast<const Pair0021ACB9 *>(a));
    *a = *b;
    *b = *reinterpret_cast<const Rva0021915B *>(&tmp);
}
