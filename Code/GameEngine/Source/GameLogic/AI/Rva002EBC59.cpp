// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBC59 @0x002EBC59 38B. Cdecl helper: rowed
// IsOdd on one arg (sharing pushed args), then pinned cdecl 0x002E79A8,
// returning the first arg. Identity unproven.
unsigned char __cdecl Rva002EBBFBIsOdd(void *p);
void __cdecl rva002E79A8(int a1, unsigned char a2, int a3, int a4, int a5);
// ?rva002EBC59@@YAPAXPAX0HHH@Z @0x002EBC59 38B (name from build; see below).
void *rva002EBC59(void *a1, void *a2, int a3, int a4, int a5)
{
	rva002E79A8((int)a1, Rva002EBBFBIsOdd(a2), a3, a4, a5);
	return a1;
}
