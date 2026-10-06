// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBC7F @0x002EBC7F 40B. Cdecl helper: rowed
// IsOdd on one arg (sharing pushed args), then pinned cdecl 0x002E79A8
// with a struct pair unpacked, returning the first arg. Identity unproven.
struct Rva002EBC7FPair
{
	int x;
	int y;
};
unsigned char __cdecl Rva002EBBFBIsOdd(void *p);
void __cdecl rva002E79A8(int a1, unsigned char a2, int a3, int a4, int a5);
// ?rva002EBC7F@@YAPAXPAX0PAURva002EBC7FPair@@H@Z @0x002EBC7F 40B (name guess).
void *rva002EBC7F(void *a1, void *a2, Rva002EBC7FPair *a3, int a4)
{
	rva002E79A8((int)a1, Rva002EBBFBIsOdd(a2), a3->x, a3->y, a4);
	return a1;
}
