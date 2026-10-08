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

// The device and per-frame counters are DX8Wrapper's protected statics
// (dx8wrapper.cpp); number_of_DX8_calls is its file-scope counter.
class DX8Wrapper
{
protected:
	static struct IDirect3DDevice8 *D3DDevice;		// retail 0x00DEDA34
	static unsigned matrix_changes;		// retail 0x00DEDA4C
	friend void __cdecl bfmeGo1054E(int, int);
};
extern unsigned number_of_DX8_calls;		// retail 0x00DEDA98

void __cdecl bfmeGo1054E(int a, int b)
{
	DX8Wrapper::matrix_changes++;

	void *o = DX8Wrapper::D3DDevice;
	BfmeE1054 *p = reinterpret_cast<BfmeE1054 *>(o);

	p->m_bfmeVt->m_bfmeFn(p, a, b);
	number_of_DX8_calls++;
}
