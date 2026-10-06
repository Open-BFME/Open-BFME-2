// cl: /MD
// ?Rva00587599Copy@@YAPAVRva00587375@@PBV1@0PAV1@PBX@Z @0x00587599 38B
// Range copy 0x3C structs: while first!=last via rowed 0x00587410,
// advances both, returns result end. 4th void* unused.
// Unblocks 0x00587C40 0x00587DCD.
// Evidence: callers 0x00587C81 0x00587CCC 0x00587E29 0x00587E75 plus add 0x3C x2.
class Rva00587375
{
public:
	void rva00587375(const Rva00587375 *src);
};
void __cdecl Rva00587410Copy(Rva00587375 *dest, const Rva00587375 *src);
Rva00587375 *__cdecl Rva00587599Copy(const Rva00587375 *first, const Rva00587375 *last, Rva00587375 *result, const void *unused)
{
	(void)unused;
	Rva00587375 *d = result;
	const Rva00587375 *s = first;
	while (s != last) {
		Rva00587410Copy(d, s);
		s = (const Rva00587375 *)((const char *)s + 0x3c);
		d = (Rva00587375 *)((char *)d + 0x3c);
	}
	return d;
}
