//
// ?Rva00225A93Get@@YAHHHHHH@Z @0x00225A93 5B.
// Free __cdecl helper returning its 5th int arg (mov eax,[esp+0x14]/ret).
// Evidence: 5B body, ret with no pop (__cdecl), 22 callers 213-218B,
// LINK BONUS via 0x002264B3, prev/next neighbours.
int Rva00225A93Get(int a, int b, int c, int d, int e)
{
	return e;
}
