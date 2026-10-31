// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00240C89Create@@YGPAURva00240C89Node@@ABUBfmeStringRecord00239B46@@@Z, retail 0x00240C89, 34 bytes.
// Free stdcall node creator: allocate 0x10 via byte allocator 0x307F0 then placement-copy the value at +8 via 0x23FC3E, return node.
// Evidence: rowed allocator and typed copy owner, caller 0x241959 (pushes arg, links node), prev Rva00439325Erase flags.
#include <memory>
struct BfmeStringRecord00239B46;
void Rva0023FC3EConstruct(BfmeStringRecord00239B46 *, const BfmeStringRecord00239B46 &);
struct BfmeStringRecord00239B46
{
	char m_data[8];
};
struct Rva00240C89Node
{
	char m_pad[8];
	BfmeStringRecord00239B46 m_val08;
};
struct Rva00240C89Node * __stdcall Rva00240C89Create(const struct BfmeStringRecord00239B46 &x);
struct Rva00240C89Node * __stdcall Rva00240C89Create(const struct BfmeStringRecord00239B46 &x)
{
	struct Rva00240C89Node *tmp = (struct Rva00240C89Node *)_STL::allocator<char>::allocate(0x10, (const void *)0);
	Rva0023FC3EConstruct((BfmeStringRecord00239B46 *)((char *)tmp + 8), x);
	return tmp;
}
