// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00087A5CCopy@@YAXPAPAX0@Z @ 0x00087A5C (24B): null-guarded 4-byte
// owning-reference placement copy; copies the pointer then increments the
// pointee refcount at +4. Evidence: 25 callers including vector insert-overflow
// trio 0x0007E2FA/0x00577CA0 plus 178B overflow bodies; shape matches
// AsciiString _Construct at 0x00142CC0 (25B add) with /O1 inc form per §4.1.

void __cdecl Rva00087A5CCopy(void **dst, void **src)
{
	if (!dst)
		return;
	void *v = *src;
	*dst = v;
	if (!v)
		return;
	++*(int *)((char *)v + 4);
}
