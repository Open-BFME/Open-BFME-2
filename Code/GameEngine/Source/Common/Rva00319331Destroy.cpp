// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00319331Destroy@@YAXPAURva00319331Item@@0@Z, retail 0x00319331, 26 bytes.
// Evidence: frameless loop over 0x10-sized vtable objects calling slot 0 with 0.
// Caller 0x00319784 forwards its two pointer args plus a local; loop uses first two.
struct Rva00319331Item
{
	virtual void rva00319331Virt(int);
	char m_pad[12];
};

void __cdecl Rva00319331Destroy(Rva00319331Item *first, Rva00319331Item *last)
{
	for (; first != last; ++first)
		first->rva00319331Virt(0);
}
