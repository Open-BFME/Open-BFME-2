// cl: /DNDEBUG /MD
//
// ?Rva002861B0Copy@@YAXPAXPBX@Z @0x002861B0 25B.
// Null-checked 6-byte copy (dword + word) with caller-cleaned __cdecl.
// Callers are the array-copy loops at 0x002861C9/0x002861EF/0x00287BA0/0x00287F88
// which stride by 8 and copy 6. No donor; identity is address-honest only.

#define NULL 0

void __cdecl Rva002861B0Copy(void *dst, const void *src)
{
	if (dst == NULL)
		return;
	*(unsigned int *)dst = *(const unsigned int *)src;
	*(unsigned short *)((char *)dst + 4) = *(const unsigned short *)((const char *)src + 4);
}
