// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?Rva004E1AD5Get@@YAXPAURva004E1AD5Item@@0PAX@Z, RVA 0x004E1AD5, 26B.
// Unlock lane: range loop over 0x58-stride objects calling virtual slot 0
// with 0; frameless push-esi loop with late-entry jmp to cmp. Caller at
// 0x004E1FCC passes first/last plus a 1-byte tag (lea [ebp-1]), so 3 args.
// Stride and virtual dispatch from retail bytes; owner unknown so honest
// address-derived names.
struct Rva004E1AD5Item
{
	virtual void f(int);
	char m_pad[0x58 - 4];
};

void __cdecl Rva004E1AD5Get(Rva004E1AD5Item *first, Rva004E1AD5Item *last, void *unused)
{
	for (; first != last; ++first)
		first->f(0);
}
