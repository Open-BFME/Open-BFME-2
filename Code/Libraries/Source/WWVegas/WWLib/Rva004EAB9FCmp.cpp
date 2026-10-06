// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva004EAB9FCmp@@YA_NPBX0@Z, retail 0x004EAB9F, 26 bytes.
// Null-checked equality: returns 1 when first arg non-null and dword at +0x48
// equals dword at second arg +0. Evidence: 7 callers in FUN_008e98f7 pass
// ([esi], [ebp+0x10]) and test al; neighbours in same WWLib STL TU family.
bool __cdecl Rva004EAB9FCmp(const void *a, const void *b)
{
	if (a)
		return *(const int *)((const char *)a + 0x48) == *(const int *)b;
	return false;
}
