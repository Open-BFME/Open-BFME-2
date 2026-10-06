// cl: /MD
// ?Rva0056BD91Pack@@YAEEEEE@Z @0x0056BD91 20B:
// Free __cdecl byte pack: ((a - c) << 4) - d + b. Args at esp+4/8/c/10.
// Callers at 0x003FF198 0x00447E82 0x00447F30. Retail order sub-c shl sub-d add-b.
unsigned char __cdecl Rva0056BD91Pack(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
unsigned char __cdecl Rva0056BD91Pack(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	unsigned char r = a;
	r -= c;
	r <<= 4;
	r -= d;
	r += b;
	return r;
}
