// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00240D0FCreate@@YGPAURva00240D0FNode@@ABURva00240D0FValue@@@Z, retail 0x00240D0F, 37 bytes.
// Free stdcall node creator: allocate 0xC via byte allocator 0x307F0 clear +0 then _Construct value at +4 via dup 0x23FC6B, return node.
// Evidence: unlock lane, callee allocate row + dup_0023FC6B row (pair AsciiString NoCaseTreeValue _Construct), caller 0x242F45, sibling Rva00240C89Create same recipe.
namespace _STL
{
	template <class T> class allocator
	{
	public:
		static char *allocate(unsigned int n, const void *hint);
	};
}
void __cdecl dup_0023FC6B() throw();
struct Rva00240D0FValue
{
	char m_data[8];
};
struct Rva00240D0FNode
{
	int m_00;
	Rva00240D0FValue m_04;
};
struct Rva00240D0FNode * __stdcall Rva00240D0FCreate(const struct Rva00240D0FValue &x);
struct Rva00240D0FNode * __stdcall Rva00240D0FCreate(const struct Rva00240D0FValue &x)
{
	struct Rva00240D0FNode *tmp = (struct Rva00240D0FNode *)_STL::allocator<char>::allocate(0xC, (const void *)0);
	tmp->m_00 = 0;
	((void (__cdecl *)(struct Rva00240D0FValue *, const struct Rva00240D0FValue *))&dup_0023FC6B)(
		(struct Rva00240D0FValue *)((char *)tmp + 4), &x);
	return tmp;
}
