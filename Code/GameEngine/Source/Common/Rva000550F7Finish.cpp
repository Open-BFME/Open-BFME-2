// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Oi /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva000550F7@Rva00699180Owner@@QAEXPAUHolder@@H@Z @0x000550F7 120B.
// Chain from 0x52098: removes a volume entry matching outer float+key then
// refreshes the channel. Outer vector lives at +0xB8 via holder indirection.

struct BfmePod8
{
	int a[2];
};

#include <vector>

namespace _STL
{
// ?erase@?$vector@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEPAUBfmePod8@@PAU3@@Z
// is owned by stlport_pod_vector_malloc_bodies.cpp: declare the explicit
// specialization so this TU calls it without emitting a second definition.
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *);
}

struct VecInner
{
	char m_pad[0xb8];
	_STL::vector<BfmePod8> m_vec;
};

struct Holder
{
	VecInner *m_inner;
};

class Rva00699180Owner
{
public:
	void refreshPair(int a, int b);
	void rva00051FFE(int b);
	void rva00052048(int idx);
	void rva00052098(int b);
	void rva000550F7(Holder *o, int key);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	_STL::vector<BfmePod8> m_vecs[6];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
};

struct Entry
{
	float v;
	int key;
};

void Rva00699180Owner::rva000550F7(Holder *o, int key)
{
	_STL::vector<BfmePod8> &outer = o->m_inner->m_vec;
	BfmePod8 *p = outer.begin();
	BfmePod8 *oend = outer.end();
	for (; p != oend; ++p)
	{
		int idx = p->a[0];
		if (idx == -1)
			continue;
		float outerVal = *(float *)&p->a[1];
		_STL::vector<BfmePod8> &inner = m_vecs[idx];
		BfmePod8 *q = m_vecs[idx].begin();
		BfmePod8 *iend = m_vecs[idx].end();
		bool found = false;
		while (!found && q != iend)
		{
			if (*(float *)&q->a[0] == outerVal && q->a[1] == key)
			{
				inner.erase(q);
				found = true;
			}
			else
				++q;
		}
		rva00052098(idx);
	}
}
