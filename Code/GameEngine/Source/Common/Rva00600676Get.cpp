// ?Rva00600676Get@@YGPAXPBDHH@Z @0x00600676 20B. Guarded global virtual
// forward: if G00A06E5C is null return 0 else tail-jump to its slot 2
// (offset 8) with the same 3 stdcall args. Same shape as
// Rva003F7E83Forward.cpp. Evidence: callers push 3 args (e.g. 0x0040980B
// pushes ebx/[ebp+0x10]/eax, 0x002DD9F6 pushes esi/0x41/eax); ret 0xC;
// global 0x00A06E5C; sibling FileSystem::openFile takes the same
// (PBDHH) args. Sibling ?Rva006006A9Get@@YG_NPBD@Z @0x006006A9 20B shares
// the global and forwards to slot 11 (0x2C) with 1 arg returning bool.

class Rva00600676Target
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *v2(const char *a1, int a2, int a3);
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual bool v11(const char *a1);
	virtual bool v12(const char *a1);
};

extern Rva00600676Target *G00A06E5C;

void *__stdcall Rva00600676Get(const char *a1, int a2, int a3)
{
	Rva00600676Target *p = G00A06E5C;
	void *r = 0;
	if (p != 0)
		r = p->v2(a1, a2, a3);
	return r;
}

bool __stdcall Rva006006A9Get(const char *a1)
{
	Rva00600676Target *p = G00A06E5C;
	if (p != 0)
		return p->v11(a1);
	return false;
}
// ?Rva00600695Get@@YG_NPBD@Z @0x00600695 20B. Guarded global virtual forward
// to slot 12 (0x30) with 1 stdcall arg returning bool; null returns false.
// Same shape as v11 sibling above; prev 0x0060068A next 0x006006A9 same TU;
// caller 0x003006D9 pushes empty literal; address-derived honest name.
bool __stdcall Rva00600695Get(const char *a1)
{
	Rva00600676Target *p = G00A06E5C;
	if (p != 0)
		return p->v12(a1);
	return false;
}
// ?G00A06E5C@@3PAVRva00600676Target@@A: the global at VA 0xe06e5c is ?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A.
#pragma comment(linker, "/alternatename:?G00A06E5C@@3PAVRva00600676Target@@A=?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A")
