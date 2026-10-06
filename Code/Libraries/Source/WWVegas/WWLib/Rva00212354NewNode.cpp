// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva00212354NewNode@@YGPAXPBX@Z, retail 0x00212354 37B. Hashtable node
// allocator for the AsciiString-keyed 12-byte node family (next+pair) that
// resize 0x00212858 and inserts 0x00212A16/0x00212A5A belong to. Allocates
// 12 bytes through the rowed game byte allocator 0x000307F0, zeroes the
// next link, and placement-copies the 8-byte pair through the rowed
// _Construct 0x00211F6D (NoCase twin; any 4-byte second shares the body via
// the rowed pair copy 0x00466EA7). Called by 0x00212A41 and 0x00212AA0.
// Evidence: ret-4 free function (no ecx use); push 0/push 0xC/call shape.
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

struct NoCaseTreeValue4
{
	unsigned char m_data[4];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NewNodePair;

void __cdecl dup_00211F6D(void);
typedef void (__cdecl *NewNodeConstructFn)(NewNodePair *, NewNodePair const &);

struct HashNode
{
	void *m_next;
	NewNodePair m_val;
};

void *__stdcall Rva00212354NewNode(const void *src)
{
	HashNode *node = (HashNode *)_STL::allocator<char>::allocate(12, 0);
	node->m_next = 0;
	((NewNodeConstructFn)&dup_00211F6D)(&node->m_val, *(const NewNodePair *)src);
	return node;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva00212354@Rva000427195@@QAEPAXPBX@Z=?Rva00212354NewNode@@YGPAXPBX@Z")
