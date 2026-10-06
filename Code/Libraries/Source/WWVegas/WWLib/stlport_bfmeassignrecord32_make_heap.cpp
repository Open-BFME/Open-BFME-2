// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00173A60MakeHeap@@YAXPAUBfmeAssignRecord32@@0P6A_NABU1@1@Z@Z @0x00173A60 83B make_heap helper for vector<BfmeAssignRecord32>.
// Retail builds heap via adjust_heap 0x001738C3 walk from (len-2)/2 down with 0x20 stride; frameless no EH.
// Evidence: chain from adjust_heap 0x001738C3; caller at 0x00173BE4; len from last-first stride.
// Callees: copy at 0x00173731 and adjust_heap at 0x001738C3; honest Rva free-function name.
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	BfmeAssignRecord32(const BfmeAssignRecord32 &o);
	~BfmeAssignRecord32();
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &other);
};
typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
void __cdecl Rva001738C3AdjustHeap(BfmeAssignRecord32 *first, int hole, int len, BfmeAssignRecord32 value, BfmePred comp);
void __cdecl Rva00173A60MakeHeap(BfmeAssignRecord32 *first, BfmeAssignRecord32 *last, BfmePred comp)
{
	int len = (int)(last - first);
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	BfmeAssignRecord32 *p = first + parent;
	for (;;) {
		Rva001738C3AdjustHeap(first, parent, len, *p, comp);
		if (parent == 0)
			break;
		--parent;
		--p;
	}
}
