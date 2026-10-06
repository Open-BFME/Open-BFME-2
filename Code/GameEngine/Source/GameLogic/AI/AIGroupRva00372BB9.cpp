// cl: /O1 /DNDEBUG /MD
// ?rva00372BB9@AIGroup@@QAEXPBXH@Z @0x00372BB9 76B
// Unlock over AIGroup pin 0x00372571 plus virtual 0x158.
// Evidence: calls pin 0x00372571; callees rowed/pinned; unblocks 0x004ED2ED.
struct Rva00372571Params
{
	const void *m_00;
	bool m_04;
	const void *m_08;
	const void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class V86;
struct VTable86
{
	void *m_pad[86];
	void *(__fastcall *m_f158)(V86 *p);
};

class AIGroup
{
public:
	void rva00372BB9(const void *a, int b);
	void rva00372571(Rva00372571Params *p, int v);
};

void AIGroup::rva00372BB9(const void *a, int b)
{
	(void)b;
	V86 *p = *(V86 *const *)((const char *)a + 0x250);
	if (p == 0)
		return;
	const VTable86 *vt;
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_0C = a;
	params.m_08 = a;
	vt = *(const VTable86 *const *)p;
	params.m_04 = false;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	params.m_00 = vt->m_f158(p);
	rva00372571(&params, 0);
}
