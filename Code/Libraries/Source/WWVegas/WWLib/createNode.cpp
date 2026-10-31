// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?createNode@@YGPAURva00240D0FNode@@ABURva00240D0FValue@@@Z, retail 0x00240D0F, 37 bytes.
// Free stdcall node creator: allocate 0xC via byte allocator 0x307F0 clear +0 then _Construct value at +4 via dup 0x23FC6B, return node.
// Evidence: unlock lane, callee allocate row + dup_0023FC6B row (pair AsciiString NoCaseTreeValue _Construct), caller 0x242F45, sibling Rva00240C89Create same recipe.
#include <memory>
void __cdecl Rva0023FC6BConstruct(void *dest, const void *source);
struct Rva00240D0FValue
{
	char m_data[8];
};
struct Rva00240D0FNode
{
	int m_next;
	Rva00240D0FValue m_04;
};
struct Rva00240D0FNode * __stdcall createNode(const struct Rva00240D0FValue &x);
struct Rva00240D0FNode * __stdcall createNode(const struct Rva00240D0FValue &x)
{
	struct Rva00240D0FNode *node = (struct Rva00240D0FNode *)_STL::allocator<char>::allocate(0xC, (const void *)0);
	node->m_next = 0;
	Rva0023FC6BConstruct((struct Rva00240D0FValue *)((char *)node + 4), &x);
	return node;
}
