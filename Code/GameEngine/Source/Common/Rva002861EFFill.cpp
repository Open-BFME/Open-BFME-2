// cl: /DNDEBUG /MD
// ?Rva002861EFFill@@YAPAXPAXIPBX@Z, retail 0x002861EF, 37 bytes. Array fill of 6-byte records via rowed copy 0x002861B0. Called from 0x00287BB8. Neighbours share /O1.
void __cdecl Rva002861B0Copy(void *dst, const void *src);
void *__cdecl Rva002861EFFill(void *dst, unsigned int count, const void *src)
{
	char *d = (char *)dst;
	unsigned int n = count;
	if (n > 0) {
		do {
			Rva002861B0Copy(d, src);
			d += 8;
			--n;
		} while (n != 0);
	}
	return d;
}
