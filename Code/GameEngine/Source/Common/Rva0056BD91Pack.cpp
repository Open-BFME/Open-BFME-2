// cl: /MD /O1
// ?Rva0056BD91Pack@@YAEEEDD@Z @0x0056BD91 20B:
// Native calls447E82/447F30 pass -1/-2 offsets as signed byte values.
// The first two byte arguments and unsigned result retain existing evidence.
// O1 gives the independently verified20B arithmetic with signed offsets.
// Free __cdecl byte pack: ((a - c) << 4) - d + b. Args at esp+4/8/c/10.
// Callers at 0x003FF198 0x00447E82 0x00447F30. Retail order sub-c shl sub-d add-b.
unsigned char __cdecl Rva0056BD91Pack(unsigned char a, unsigned char b, char c, char d);
unsigned char __cdecl Rva0056BD91Pack(unsigned char a, unsigned char b, char c, char d)
{
	unsigned char r = a;
	r -= c;
	r <<= 4;
	r -= d;
	r += b;
	return r;
}
