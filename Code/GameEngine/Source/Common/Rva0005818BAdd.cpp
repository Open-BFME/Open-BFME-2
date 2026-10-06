// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Oi /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0005818B@Rva00699180Owner@@QAEXPAUHolder@@H@Z @0x0005818B 96B.
// Add counterpart of the remove at 0x000550F7: for each (channel, value)
// entry in the holder's outer vector at +0xB8, append (value, key) to that
// channel's vector and refresh the channel through rowed rva00052098.
// Target facts: outer entries are 8 bytes with the channel index first
// (-1 skips) and a float second; channel vectors sit at +0x4C with a 12-byte
// stride; the append is the rowed vector<BfmeE8>::push_back at 0x00539A2E.
// Caller 0x000581FA indexes three owners of 0x1C4 bytes at manager +0x12C.

struct BfmeE8
{
	int a, b;
};

#include <vector>

namespace _STL
{
// ?push_back@?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@QAEXABUBfmeE8@@@Z
// is owned by its own vector unit: declare the explicit specialization so
// this TU calls it without emitting a second definition.
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
}

struct VecInner
{
	char m_pad[0xb8];
	_STL::vector<BfmeE8> m_vec;
};

struct Holder
{
	VecInner *m_inner;
};

class Rva00699180Owner
{
public:
	void rva00052098(int b);
	void rva0005818B(Holder *o, int key);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	_STL::vector<BfmeE8> m_vecs[6];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
};

void Rva00699180Owner::rva0005818B(Holder *o, int key)
{
	_STL::vector<BfmeE8> &outer = o->m_inner->m_vec;
	BfmeE8 *p = outer.begin();
	BfmeE8 *oend = outer.end();
	for (; p != oend; ++p)
	{
		int idx = p->a;
		if (idx == -1)
			continue;
		BfmeE8 entry;
		*(float *)&entry.a = *(float *)&p->b;
		entry.b = key;
		m_vecs[idx].push_back(entry);
		rva00052098(idx);
	}
}
