// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva00410A86NewNode@@YGPAXPBX@Z, retail 0x00410A86 37B. Hashtable node
// allocator for the AsciiString-keyed 12-byte node family (next+pair).
// Allocates 12 bytes through the rowed game byte allocator 0x000307F0,
// zeroes the next link, and placement-copies the 8-byte pair through the
// rowed _Construct dup 0x004109BC for pair<const AsciiString,
// TreeHintRef00217D4C>. Same shape as rowed 0x00410997 and 0x004152E6.
// Called by 0x00410E0A in 0x00410DDF. Evidence: ret-4 free function;
// push 0/push 0xC/call shape.
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

struct TreeHintPayload00410A86
{
	unsigned char m_data[4];
};

typedef _STL::pair<const AsciiString, TreeHintPayload00410A86> NewNodePair;

void __cdecl dup_004109BC(void);
typedef void (__cdecl *NewNodeConstructFn)(NewNodePair *, NewNodePair const &);

struct HashNode
{
	void *m_next;
	NewNodePair m_val;
};

void *__stdcall Rva00410A86NewNode(const void *src)
{
	HashNode *node = (HashNode *)_STL::allocator<char>::allocate(12, 0);
	node->m_next = 0;
	((NewNodeConstructFn)&dup_004109BC)(&node->m_val, *(const NewNodePair *)src);
	return node;
}
