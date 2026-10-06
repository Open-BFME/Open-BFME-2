// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva002ACFD6NewNode@@YGPAXPBX@Z @0x002ACFD6 37B: hashtable node allocator
// for the AsciiString-keyed 12-byte node family (next+pair) that callers
// 0x001F8F70 and 0x002ADD5C insert into buckets via next-link chaining.
// Allocates 12 bytes through rowed byte allocator 0x000307F0 zeroes next
// via and-mem-0 under /O1 and placement-copies the 8-byte pair through
// rowed _Construct 0x001F6882 for pair<const AsciiString
// TreeHintPayload001F8ACB>. Prev Rva002ACF9CInsert /O1 /DNDEBUG /MD next
// SubsystemNameGetters2 no flags. Honest address-derived free function
// following Rva00212354NewNode 37B precedent with true _Construct name.
#include <map>
#include <set>
#include <list>
#include <vector>

namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
}

#include "ascii_string.h"

struct TreeHintPayload001F8ACB
{
	unsigned char m_body[4];
};

typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> NewNodePair;

struct HashNode
{
	void *m_next;
	NewNodePair m_val;
};

void *__stdcall Rva002ACFD6NewNode(const void *src)
{
	HashNode *node = (HashNode *)_STL::allocator<char>::allocate(12, 0);
	node->m_next = 0;
	_STL::_Construct(&node->m_val, *(const NewNodePair *)src);
	return node;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva002ACFD6@Rva000427195@@QAEPAXPBX@Z=?Rva002ACFD6NewNode@@YGPAXPBX@Z")
