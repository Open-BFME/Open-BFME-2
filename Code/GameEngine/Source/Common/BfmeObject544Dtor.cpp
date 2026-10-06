// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1BfmeObject544@@QAE@XZ @0x004CACB8 67B.
// Nonvirtual dtor destroying array plus Rb_tree set.
// Evidence: callees rowed 0x0025742C 0x004C9F38 0x00629110; callers deleting dtor plus vector destroy.
#include <set>

class Rva002390CB
{
public:
	~Rva002390CB();
private:
	char m_pad[8];
};

struct BfmeStringRecord002CF550
{
	bool operator<(const BfmeStringRecord002CF550 &other) const { return false; }
	char m_pad[0x10];
};

class BfmeObject544
{
public:
	~BfmeObject544();
private:
	char m_pad0[0x4C];
	Rva002390CB m_arr[0x38];
	_STL::set<BfmeStringRecord002CF550> m_set;
};

BfmeObject544::~BfmeObject544()
{
}
