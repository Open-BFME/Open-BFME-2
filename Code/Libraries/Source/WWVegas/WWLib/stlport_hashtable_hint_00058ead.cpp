// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva00056E53New@@YGPAUHashNode00056E53@@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@Z, retail 0x00056E53 (37B).
// Hashtable twin of the rowed ?_M_create_node at 0x00056F9E for the same
// pair<const AsciiString TreeHintPayload0005808E>: 12-byte node (next+0
// plus 8-byte value at +4) via the same rowed byte allocator 0x000307F0 and
// the same rowed _Construct 0x00055924. Caller at 0x00058C9A links the node
// into the bucket vector (begin+4) after the rowed bucketIndex 0x00223149.
// Stdcall per ret-4; honest-address free function since the owning hashtable
// type is unproven.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload0005808E { char m_body[4]; };
typedef _STL::pair<const AsciiString, TreeHintPayload0005808E> TreeHintPair0005808E;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct HashNode00056E53
{
	HashNode00056E53 *m_next;
	TreeHintPair0005808E m_val;
};

HashNode00056E53 *__stdcall Rva00056E53New(const TreeHintPair0005808E &value)
{
	HashNode00056E53 *node = (HashNode00056E53 *)_STL::allocator<char>::allocate(sizeof(HashNode00056E53), 0);
	node->m_next = 0;
	_STL::_Construct(&node->m_val, value);
	return node;
}
