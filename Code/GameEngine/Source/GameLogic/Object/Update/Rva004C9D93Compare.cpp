// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?Rva004C9D93Less@@YG_NPAX0@Z, retail 0x004C9D93, 45 bytes.
// Free __stdcall comparator: int at +0 then float at +8. Callers at 0x004CA2B8
// (node+0x10 vs key) and 0x004CA6A4 test al. Evidence: ret 8, movss/comiss.
bool __stdcall Rva004C9D93Less(void *a, void *b)
{
	int ai = *(int *)a;
	int bi = *(int *)b;
	if (ai < bi)
		return true;
	if (ai > bi)
		return false;
	float af = *(float *)((char *)a + 8);
	float bf = *(float *)((char *)b + 8);
	return bf > af;
}
