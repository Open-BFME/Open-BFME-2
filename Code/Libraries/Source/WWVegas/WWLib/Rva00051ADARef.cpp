// cl: /DNDEBUG /MD
//
// ?rva00051ADA@Rva00051ADA@@QAEAAV1@ABV1@H@Z @0x00051ADA 31B.
// Evidence: this+0 store of other+0 with null check and InterlockedIncrement
// of ptr+4 then return this; caller 0x00059F2C; prev/next /O1 WWLib.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

struct Rva00051ADAPtr
{
	int m_pad0;
	volatile long m_refs;
};

class Rva00051ADA
{
public:
	Rva00051ADA &rva00051ADA(const Rva00051ADA &other, int unused);

private:
	Rva00051ADAPtr *m_ptr;
};

Rva00051ADA &Rva00051ADA::rva00051ADA(const Rva00051ADA &other, int unused)
{
	(void)unused;
	Rva00051ADAPtr *p = other.m_ptr;
	m_ptr = p;
	if (p != 0)
		InterlockedIncrement(&p->m_refs);
	return *this;
}
