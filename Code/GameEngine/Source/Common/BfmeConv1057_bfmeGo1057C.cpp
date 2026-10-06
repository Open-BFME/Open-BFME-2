// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?bfmeGo1057C@@YAXHHH@Z @ 0x0006628A (39B): same D3D device global load as
// bfmeGo1054E but the vtable slot is +0x114 and both counters are bumped.
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1057.cpp.
// Dedicated TU, the donor's other definitions omitted.

struct BfmeVt1057
{
	void *__bfmePad[0x45];				// +0x00 .. +0x110
	void (__stdcall *m_bfmeFn)(void *o, int a, int b, int c);	// +0x114
};

struct BfmeE1057
{
	BfmeVt1057 *m_bfmeVt;
};

extern void *g_Va00DEDA34;					// retail 0x00DEDA34, ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A
extern int g_Va00DEDA68;					// retail 0x00DEDA68
extern int g_Va00DEDA98;					// retail 0x00DEDA98

// ?g_Va00DEDA34@@3PAUIDirect3DDevice8@@A: the global at VA 0xDEDA34 is
// ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?g_Va00DEDA34@@3PAX=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")

void __cdecl bfmeGo1057C(int a, int b, int c)
{
	void *o = g_Va00DEDA34;
	BfmeE1057 *p = reinterpret_cast<BfmeE1057 *>(o);

	p->m_bfmeVt->m_bfmeFn(p, a, b, c);
	g_Va00DEDA98++;
	g_Va00DEDA68++;
}