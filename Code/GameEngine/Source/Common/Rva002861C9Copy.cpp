// cl: /DNDEBUG /MD
// ?Rva002861C9Copy@@YAPAXPBX0PAX@Z, retail 0x002861C9, 38 bytes. Array copy of 6-byte records via rowed copy 0x002861B0. Called from 0x00287B8B/0x00287BD6. Neighbours share /O1.
void __cdecl Rva002861B0Copy(void *dst, const void *src);
void *__cdecl Rva002861C9Copy(const void *first, const void *last, void *result)
{
	char *d = (char *)result;
	const char *s = (const char *)first;
	const char *e = (const char *)last;
	while (s != e) {
		Rva002861B0Copy(d, s);
		s += 8;
		d += 8;
	}
	return (void *)d;
}
