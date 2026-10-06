// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?bfmeGoELHa@@YAXPAX@Z @ 0x00075311 (25B): the same D3D device global load
// again, one argument and the vtable slot +0x164; only the 0xDEDA98 counter
// follows. Ported from Open-BFME-1 Code/GameEngine/Source/Common/
// BfmeConv816.cpp. Dedicated TU, the donor's other definitions omitted.

struct BfmeVtELH
{
	void *__bfmePad[0x59];				// +0x00 .. +0x160
	void (__stdcall *m_bfmeF89)(void *o, void *a);	// +0x164
};

struct BfmeObjELH
{
	BfmeVtELH *m_bfmeVtbl;
};

extern void *g_Va00DEDA34;					// retail 0x00DEDA34, ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A
extern int g_Va00DEDA98;					// retail 0x00DEDA98

// ?g_Va00DEDA34@@3PAUIDirect3DDevice8@@A: the global at VA 0xDEDA34 is
// ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?g_Va00DEDA34@@3PAX=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")

void __cdecl bfmeGoELHa(void *a)
{
	BfmeObjELH *o = reinterpret_cast<BfmeObjELH *>(g_Va00DEDA34);
	o->m_bfmeVtbl->m_bfmeF89(o, a);
	g_Va00DEDA98++;
}