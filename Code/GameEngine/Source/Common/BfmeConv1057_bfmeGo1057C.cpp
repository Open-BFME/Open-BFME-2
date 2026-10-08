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

// The device and per-frame counters are DX8Wrapper's protected statics
// (dx8wrapper.cpp); number_of_DX8_calls is its file-scope counter.
class DX8Wrapper
{
protected:
	static struct IDirect3DDevice8 *D3DDevice;		// retail 0x00DEDA34
	static unsigned texture_stage_state_changes;		// retail 0x00DEDA68
	friend void __cdecl bfmeGo1057C(int, int, int);
};
extern unsigned number_of_DX8_calls;		// retail 0x00DEDA98

void __cdecl bfmeGo1057C(int a, int b, int c)
{
	void *o = DX8Wrapper::D3DDevice;
	BfmeE1057 *p = reinterpret_cast<BfmeE1057 *>(o);

	p->m_bfmeVt->m_bfmeFn(p, a, b, c);
	number_of_DX8_calls++;
	DX8Wrapper::texture_stage_state_changes++;
}
