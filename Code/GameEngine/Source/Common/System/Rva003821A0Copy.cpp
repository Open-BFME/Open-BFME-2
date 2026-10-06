// cl: /DNDEBUG /MD /GX
// ?Rva003821A0Copy@@YAXPAX0@Z 0x003821A0 25B
// Free copy helper: copies byte at +0 and word at +2, skipping pad at +1.
// Evidence: single caller 0x00382BA1 pushes (dst=buf+0x10, src=arg) then calls here;
// dst null-guarded (test eax, je). No donor; honest address name.

struct Rva003821A0Fields
{
	unsigned char m0;
	unsigned short m2;
};

void __cdecl Rva003821A0Copy(void* dstRaw, void* srcRaw)
{
	Rva003821A0Fields* dst = (Rva003821A0Fields*)dstRaw;
	Rva003821A0Fields* src = (Rva003821A0Fields*)srcRaw;
	if (dst) {
		dst->m0 = src->m0;
		dst->m2 = src->m2;
	}
}
