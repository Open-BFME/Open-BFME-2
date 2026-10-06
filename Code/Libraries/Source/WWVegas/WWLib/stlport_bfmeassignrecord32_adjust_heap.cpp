// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva001738C3AdjustHeap@@YAXPAUBfmeAssignRecord32@@HHU1@P6A_NABU1@2@Z@Z @0x001738C3 172B adjust_heap helper for vector<BfmeAssignRecord32>.
// Retail sifts hole down via second-child walk with 0x20 stride then tail-calls push_heap 0x00173572; value by value needs EH dtor.
// Evidence: chain from push_heap 0x00173572; callers at 0x00173A25 and 0x00173A9C; second-child compare via funcptr at +0x34.
// Callees: assignment at 0x00173499 copy at 0x00173731 and dtor at 0x0017330A plus push_heap at 0x00173572; honest Rva free-function name.
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
void __cdecl Rva00173572PushHeap(BfmeAssignRecord32 *first, int hole, int top, BfmeAssignRecord32 value, BfmePred comp);
void __cdecl Rva001738C3AdjustHeap(BfmeAssignRecord32 *first, int hole, int len, BfmeAssignRecord32 value, BfmePred comp)
{
	int top = hole;
	int second = 2 * hole + 2;
	while (second < len) {
		if (comp(first[second], first[second - 1]))
			--second;
		first[hole] = first[second];
		hole = second;
		second = 2 * (second + 1);
	}
	if (second == len) {
		first[hole] = first[second - 1];
		hole = second - 1;
	}
	Rva00173572PushHeap(first, hole, top, value, comp);
}
