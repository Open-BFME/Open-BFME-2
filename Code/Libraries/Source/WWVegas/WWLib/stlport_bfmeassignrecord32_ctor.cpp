// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0BfmeAssignRecord32@@QAE@XZ @0x001736D6 62B default ctor of 32-byte record.
// Evidence: neighbours push_heap 0x00173572 and copy 0x00173731 prove layout s+0 x+4 arr[6]+8 stride 0x20; retail clears [esi] then ehvec ??_L size4 count6 ctor 0x002A79A5 dtor 0x0007B724; caller 0x00174A8A builds stack temp.
struct Rva00087A93 {
	void *m_data;
	Rva00087A93() { m_data = 0; }
	~Rva00087A93();
};

struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	BfmeAssignRecord32();
};

BfmeAssignRecord32::BfmeAssignRecord32() : s()
{
}
