// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00549DF2Cmp@@YGIPAX0@Z @0x00549DF2 39B
// Unsigned word compare at +0x5DA via double chase. Evidence:
// free-function via two stack args plus ret-8 (__stdcall); dword chase
// [arg]+0 then +4 then word +0x5DA for both; cmp-cx-mem plus sbb-neg
// boolize; 12 callers plus 6 unblocks; name stays address-derived.
unsigned __stdcall Rva00549DF2Cmp(void *a1, void *a2);

unsigned __stdcall Rva00549DF2Cmp(void *a1, void *a2)
{
	void *p1 = *(void **)a1;
	void *p1b = *(void **)((char *)p1 + 4);
	unsigned short w1 = *(unsigned short *)((char *)p1b + 0x5DA);
	void *p2 = *(void **)a2;
	void *p2b = *(void **)((char *)p2 + 4);
	unsigned short w2 = *(unsigned short *)((char *)p2b + 0x5DA);
	return (w2 < w1) ? 1 : 0;
}
