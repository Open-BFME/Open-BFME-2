// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00173572PushHeap@@YAXPAUBfmeAssignRecord32@@HHU1@P6A_NABU1@2@Z@Z @0x00173572 135B push_heap helper for vector<BfmeAssignRecord32>.
// Retail percolates hole up while comp(parent value) true with 0x20 stride; value by value needs EH dtor.
// Evidence: chain from landed assign 0x00173499; caller 0x001738C3 adjust_heap passes first hole top value comp; binary-search-free parent walk.
// Callees: assignment at 0x00173499 and dtor at 0x0017330A; honest Rva free-function name via caller pushes.
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	~BfmeAssignRecord32();
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &other);
};
typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
void __cdecl Rva00173572PushHeap(BfmeAssignRecord32 *first, int hole, int top, BfmeAssignRecord32 value, BfmePred comp)
{
	int parent = (hole - 1) / 2;
	while (hole > top && comp(first[parent], value)) {
		first[hole] = first[parent];
		hole = parent;
		parent = (hole - 1) / 2;
	}
	first[hole] = value;
}
