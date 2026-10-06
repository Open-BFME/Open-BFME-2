// cl: /DNDEBUG /MD
// ?Rva005657B2Copy@@YAPAXPAX00@Z @0x005657B2 47B.
// Counted copy over 0x10-stride records through the rowed 0x00564DCB
// operator=: count from (srcEnd - src) >> 4, both ends advanced by 0x10
// per element, returns the advanced dst. Same void*-manual-stride family
// as Rva0056574BFill; Rva00564DCB layout (16B) per its CopyAssign TU.
// Caller at 0x005657F4; unblocks 0x005657E1.
struct Rva00564DCB
{
	Rva00564DCB &operator=(const Rva00564DCB &that);
	char m_pad[0x10];
};

void *__cdecl Rva005657B2Copy(void *src, void *srcEnd, void *dst)
{
	int n = ((char *)srcEnd - (char *)src) >> 4;
	if (n <= 0)
		return dst;
	int m = n;
	do
	{
		((Rva00564DCB *)dst)->operator=(*(const Rva00564DCB *)src);
		src = (char *)src + 0x10;
		dst = (char *)dst + 0x10;
	}
	while (--m != 0);
	return dst;
}
