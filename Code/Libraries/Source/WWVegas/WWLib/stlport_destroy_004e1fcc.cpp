// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?Rva004E1FCCGet@@YAXPAURva004E1AD5Item@@0@Z, RVA 0x004E1FCC, 24B. Chain lane:
// forwards first/last plus a 1-byte tag local to rowed 0x004E1AD5; EBP frame
// with push ecx plus lea [ebp-1]. Callers at 0x004E222F/0x004FABFC/0x00566A61.
// Owner unknown so honest address-derived names.
struct Rva004E1AD5Item
{
	virtual void f(int);
	char m_pad[0x58 - 4];
};
void __cdecl Rva004E1AD5Get(Rva004E1AD5Item *first, Rva004E1AD5Item *last, void *tag);
struct Rva004E1FCCTag
{
	char x;
};

void __cdecl Rva004E1FCCGet(Rva004E1AD5Item *first, Rva004E1AD5Item *last)
{
	Rva004E1FCCTag tag;
	Rva004E1AD5Get(first, last, &tag);
}

// ?rva004E2227@Rva004E2227@@QAEXXZ, RVA 0x004E2227, 30B. Chain lane: calls
// rowed 0x004E1FCC range destroy with first/last at this+0/+4 then frees
// first via rowed free 0x00030830 when non-null; push-esi this plus
// pop-cleaned pushes. Caller at 0x004E3973. Owner unknown so honest
// address-derived names.
extern "C" void __cdecl free(void *p);
struct Rva004E2227
{
	Rva004E1AD5Item *m_first;
	Rva004E1AD5Item *m_last;
	void rva004E2227();
};

void Rva004E2227::rva004E2227()
{
	Rva004E1FCCGet(m_first, m_last);
	if (m_first != 0)
		free(m_first);
}
