// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva00142BE0@Rva00142BE0@@QAEXXZ, RVA 0x00142BE0, 52B.
// Single-step release from inline array at +0x30 with counts at +0xB0/+0xB4.
// Evidence: if +0xB4 nonzero dec it and return else dec +0xB0 and release
// element at [ecx+eax*4+0x30] via refcount at +4 plus slot-0 call; same array
// zeroed by ctor 0x00142EE0 and read by indexer 0x00142C30; callers at
// 0x000704FD 0x0007051D 0x000EE7D9; honest address name.

struct Rva00142BE0Ref
{
	virtual void release();
	int m_ref;
};

class Rva00142BE0
{
	char m_pad[0x30];
	Rva00142BE0Ref *m_items[32];
	int m_cntB0;
	int m_cntB4;

public:
	void rva00142BE0();
};

void Rva00142BE0::rva00142BE0()
{
	if (m_cntB4 == 0) {
		--m_cntB0;
		Rva00142BE0Ref *p = m_items[m_cntB0];
		if (p && --p->m_ref == 0)
			p->release();
		return;
	}
	--m_cntB4;
}
