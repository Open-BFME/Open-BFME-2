// cl: /MD
// ?Rva003B8E13DestroyRange@@YAXPAURva003B8B61Elem@@0@Z @0x003B8E13 24B.
// Two-arg range destroy forwarding to the 0x003B8B61 tagged loop with a tag temp.
// Evidence: retail push ebp; mov ebp,esp; push ecx; lea eax,[ebp-1]; push eax;
// push [ebp+0xC]; push [ebp+8]; call 0x003B8B61; add esp,0xC; leave; ret.
// Caller chain: vector dtor at 0x003B9065 and _M_clear plus 0x003B90A9/0x003F52D4.
// Mirrors LivingWorldRegionConnectionHelpers DestroyRange/Tagged shapes; element
// is the 0x68 virtual-dtor holder from Rva003B8B61Destroy.cpp.
struct Rva003B8B61Elem
{
	virtual void destroy(int);
	char m_pad[0x68 - 4];
};
void __cdecl Rva003B8B61Destroy(Rva003B8B61Elem *first, Rva003B8B61Elem *last, int unused);

void __cdecl Rva003B8E13DestroyRange(Rva003B8B61Elem *first, Rva003B8B61Elem *last)
{
	char dummy;
	Rva003B8B61Destroy(first, last, (int)&dummy);
}
