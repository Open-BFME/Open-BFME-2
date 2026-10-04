// ?rva000550A0@Rva00699180Owner@@QAEXH@Z
// partial score=0.90 date=2026-09-30
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /arch:SSE2 /Oi /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva000550A0@Rva00699180Owner@@QAEXH@Z @0x000550A0 87B.
// Chain from 0x52098: drops entries matching key from all six channel
// vectors then refreshes touched channels.

struct BfmePod8
{
	int a[2];
};

#include <vector>

class Rva00699180Owner
{
public:
	void rva00052098(int b);
	void rva000550A0(int key);

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

void Rva00699180Owner::rva000550A0(int key)
{
	for (int idx = 0; idx < 6; ++idx)
	{
		_STL::vector<BfmePod8> *v = &m_vecs[idx];
		BfmePod8 *p = v->begin();
		unsigned char erased = 0;
		if (p == v->end())
			continue;
		for (; p != v->end();)
		{
			if (p->a[1] == key)
			{
				p = v->erase(p);
				erased = 1;
			}
			else
				++p;
		}
		if (erased)
			rva00052098(idx);
	}
}
