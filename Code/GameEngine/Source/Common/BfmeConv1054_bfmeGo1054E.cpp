// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?bfmeGo1054E@@YAXHH@Z @ 0x000753EF (35B): the D3D device global at 0xDEDA34
// is loaded straight rather than through BFME 1's DX8Wrapper::_Get_D3D_Device8,
// which retails as a separate getter; the vtable slot is +0xB0 and the counter
// pair is 0xDEDA4C / 0xDEDA98. Ported from Open-BFME-1
// Code/GameEngine/Source/Common/BfmeConv1054.cpp. Dedicated TU, the donor's
// other definitions omitted.

struct BfmeVt1054
{
	void *__bfmePad[0x2C];				// +0x00 .. +0xB4
	void (__stdcall *m_bfmeFn)(void *o, int a, int b);	// +0xB0
};

struct BfmeE1054
{
	BfmeVt1054 *m_bfmeVt;
};

extern void *g_Va00DEDA34;					// retail 0x00DEDA34, ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A
extern int g_Va00DEDA4C;					// retail 0x00DEDA4C
extern int g_Va00DEDA98;					// retail 0x00DEDA98

// ?g_Va00DEDA34@@3PAUIDirect3DDevice8@@A: the global at VA 0xDEDA34 is
// ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?g_Va00DEDA34@@3PAX=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")

void __cdecl bfmeGo1054E(int a, int b)
{
	g_Va00DEDA4C++;

	void *o = g_Va00DEDA34;
	BfmeE1054 *p = reinterpret_cast<BfmeE1054 *>(o);

	p->m_bfmeVt->m_bfmeFn(p, a, b);
	g_Va00DEDA98++;
}