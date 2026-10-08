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

// The device and per-frame counters are DX8Wrapper's protected statics
// (dx8wrapper.cpp); number_of_DX8_calls is its file-scope counter.
class DX8Wrapper
{
protected:
	static struct IDirect3DDevice8 *D3DDevice;		// retail 0x00DEDA34
	friend void __cdecl bfmeGoELHa(void *);
};
extern unsigned number_of_DX8_calls;		// retail 0x00DEDA98

void __cdecl bfmeGoELHa(void *a)
{
	BfmeObjELH *o = reinterpret_cast<BfmeObjELH *>(DX8Wrapper::D3DDevice);
	o->m_bfmeVtbl->m_bfmeF89(o, a);
	number_of_DX8_calls++;
}
