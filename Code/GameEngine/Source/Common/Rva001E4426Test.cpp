// cl: /MD
// ?Rva001E4426Test@@YAHPAIH@Z @0x001E4426 31B: __cdecl bit test over dword array.
// Evidence: 3 callers push bit then array ptr (ecx+0x108 at 0x000456AC / ecx+0x1c8 at 0x001E4A4E / ecx+0x3a4 at 0x0028D8EB); same unsigned-shr shape as Object::testStatus and RvaBitTestTwins.
int __cdecl Rva001E4426Test(unsigned int *bits, int bit)
{
	return (bits[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
}
