// ?rva0020E9A1@Rva0020E9A1Inner@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020E9A1@Rva0020E9A1Inner@@QAEXXZ @0x0020E9A1 47B
// Vector-clear loop over this+0x2C/+0x30 calling pinned 0x003EFDF5 with 1.
// Same idiom as Rva0020EE29 but direct on this; no SSE per Rva0020E9D0 family.

class Rva003EFDF5Host
{
public:
	void rva003EFDF5(void *v);
};

struct Rva0020E9A1Inner
{
	char m_pad[0x2C];
	Rva003EFDF5Host **m_begin;
	Rva003EFDF5Host **m_end;
	void rva0020E9A1();
};

void Rva0020E9A1Inner::rva0020E9A1()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_end - (char *)m_begin) >> 2); ++i)
		m_begin[i]->rva003EFDF5((void *)1);
}
