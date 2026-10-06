// ?Rva003FCD04Compare@@YAHPAX0H@Z
// partial score=0.93 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
//
// ?Rva003FCD04Compare@@YAHPAX0H@Z @0x003FCD04 (84B):
// Free-function wrapper around chunked stream compare 0x003FC43A: builds two
// 8-byte stack adapters (vtables 0x007FDC60 and 0x00837C20, same 2-virtual
// stream interface as Rva003FC43A) over the two incoming pointer params plus
// forwarded int, then calls Compare.
extern const void *const g_007FDC60[];
extern const void *const g_00837C20[];
class Rva003FC43A
{
public:
	virtual int v00();
	virtual void v01(void *buffer, int offset, int length);
};
int __cdecl Rva003FC43ACompare(Rva003FC43A *a, Rva003FC43A *b, int unused);
class WrapA
{
public:
	virtual int v00();
	virtual void v01(void *buffer, int offset, int length);
	WrapA(void **pp) { *(const void **)this = g_007FDC60; m_pp = pp; }
	~WrapA() {}
	void **m_pp;
};
class WrapB
{
public:
	virtual int v00();
	virtual void v01(void *buffer, int offset, int length);
	WrapB(void *p) { *(const void **)this = g_00837C20; m_p = p; }
	~WrapB() {}
	void *m_p;
};
int __cdecl Rva003FCD04Compare(void *a, void *b, int c)
{
	void *pa = a;
	WrapB wb(b);
	WrapA wa(&pa);
	return Rva003FC43ACompare((Rva003FC43A*)&wa, (Rva003FC43A*)&wb, c);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00837C20@@3QBQBXB=??_7Rva003FC428@@6B@")
#pragma comment(linker, "/alternatename:?g_007FDC60@@3QBQBXB=??_7Rva002AAD77@@6B@")
