// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva001364AC@Rva001364AC@@QAEPAXPBUTreeKey00242F5E@@@Z @0x001364AC 34B.
// RB-tree create_node for the unsigned-key/string map: allocates 0x18 via
// rowed byte allocator 0x000307F0 and constructs its 8-byte value at +0x10
// through the genuine pair Construct at 0x0013623C. Native map subscript
// 0x00136A21 proves the unsigned key and mapped string; see the identity
// proof under reverse/attempt_support/construct-uint-ascii-13623c-20261019.md.
// The existing TreeKey parameter spelling is retained as an opaque ABI view.
// Only declarations are needed here: the real template definition belongs
// to stlport_construct_game_structs.cpp, just as native calls it out of line.
class AsciiString;
namespace _STL {
template <class First, class Second> struct pair;
template <class T, class U> void _Construct(T *, const U &);
template <class T> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

#include "TreeKey00242F5E.h"

typedef _STL::pair<const unsigned int, AsciiString> UnsignedAsciiPair;

class Rva001364AC { public: void *rva001364AC(const TreeKey00242F5E *src); };
void *Rva001364AC::rva001364AC(const TreeKey00242F5E *src)
{
	char *block = _STL::allocator<char>::allocate(0x18, 0);
	_STL::_Construct((UnsignedAsciiPair *)(block + 0x10), *(const UnsignedAsciiPair *)src);
	return block;
}
