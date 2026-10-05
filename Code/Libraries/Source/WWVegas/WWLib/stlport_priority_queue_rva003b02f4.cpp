// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// priority_queue<Rva003B02F4Entry, vector<...>, Rva003B02F4Greater>::pop
// @0x003B02F4 (26B) and its STLport heap chain: pop_heap 0x003B02A1,
// __pop_heap_aux 0x003B0176, __pop_heap 0x003AFFF0, __adjust_heap
// 0x003AFE8E, __push_heap 0x003AFE48. Masked twin of the rowed
// priority_queue<int, ..., greater<int> > pop at 0x003B032A with a 12-byte
// element. The bodies prove only: element stride 12, the float at +0 is the
// key, and the one-byte empty comparator (at +0xC of the queue) orders by
// key with '>' (movss/comiss, so /arch:SSE). Element and comparator names
// are address-derived placeholders; the owning game type is unknown.
#include <queue>
#include <vector>

struct Rva003B02F4Entry
{
	float key;
	unsigned int a;
	unsigned int b;
};

struct Rva003B02F4Greater
{
	bool operator()(const Rva003B02F4Entry &x, const Rva003B02F4Entry &y) const
	{
		return x.key > y.key;
	}
};

template void _STL::priority_queue<Rva003B02F4Entry, _STL::vector<Rva003B02F4Entry>, Rva003B02F4Greater>::pop();
