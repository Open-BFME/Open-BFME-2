// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva001364AC@Rva001364AC@@QAEPAXPBUTreeKey00242F5E@@@Z @0x001364AC 34B.
// RB-tree create_node for set<TreeKey00242F5E>: allocates 0x18 via rowed byte
// allocator 0x000307F0, constructs the 8-byte key at +0x10 via rowed dup
// 0x0013623C (object-symbol _Construct<TreeKey00242F5E>, true name rowed at
// 0x000A7876) called through a dup cast per Rva002CF9DCCreate precedent so
// the gate resolves to the dup address, returns the block, ret 4 (__thiscall,
// this unused). Evidence: caller 0x001364F7 (RB insert: mov ecx edi, push key,
// links node then calls _Rebalance 0x00025490) calls it twice; node base 0x10
// plus key size 8 matches TreeKey00242F5E (int plus AsciiString handle).
// Pattern follows Rva002CF9DCCreate.cpp (allocate plus dup-cast construct).
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

struct TreeKey00242F5E { char _m[8]; };

void __cdecl dup_0013623C(void);
typedef void (__cdecl *TreeKeyConstructFn)(TreeKey00242F5E *, const TreeKey00242F5E &);

class Rva001364AC { public: void *rva001364AC(const TreeKey00242F5E *src); };
void *Rva001364AC::rva001364AC(const TreeKey00242F5E *src)
{
	char *block = _STL::allocator<char>::allocate(0x18, 0);
	((TreeKeyConstructFn)&dup_0013623C)((TreeKey00242F5E *)(block + 0x10), *src);
	return block;
}
