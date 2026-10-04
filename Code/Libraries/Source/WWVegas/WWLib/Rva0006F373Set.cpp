// cl: /O1 /DNDEBUG /MD
// ?rva0006F373@Rva0006F373@@QAE_NPAXHH000@Z @0x0006F373 63B: conditional member stores then grow-or-false. Evidence: calls rowed Grow 0x0006EFC8 with middle ints; caller 0x0006FB23; unlocks 0x0006FAEC; neighbours share /O1.
class Rva0006EFC8
{
public:
	bool rva0006EFC8(int a, int b);
};

class Rva0006F373
{
public:
	bool rva0006F373(void *a, int b, int c, void *d, void *e, void *f);
	Rva0006F373(void *a, int b, int c, void *d, void *e, void *f);
private:
	void *m_00;
	int m_04;
	int m_08;
	void *m_0C;
	void *m_10;
	void *m_14;
};

void *__cdecl Rva0002FFC0Alloc(int a, int b);
void __cdecl Rva0002FFE0Free(void *p, int a);

bool Rva0006F373::rva0006F373(void *a, int b, int c, void *d, void *e, void *f)
{
	if (a)
		m_00 = a;
	if (d)
		m_0C = d;
	if (e)
		m_10 = e;
	m_14 = f;
	if (m_04 == 0)
		return ((Rva0006EFC8 *)this)->rva0006EFC8(b, c);
	return false;
}

// ??0Rva0006F373@@QAE@PAXHH000@Z @0x0006FAEC 67B: pool ctor initing size 0x80 nulls and alloc/free pins then forwarding to setter. Evidence: calls rowed setter 0x0006F373 with same six args and pin-only Alloc 0x0002FFC0 Free 0x0002FFE0; no callers; chain from 0x0006F373.
Rva0006F373::Rva0006F373(void *a, int b, int c, void *d, void *e, void *f)
{
	m_00 = (void *)0x80;
	m_04 = 0;
	m_08 = 0;
	m_0C = (void *)Rva0002FFC0Alloc;
	m_10 = (void *)Rva0002FFE0Free;
	m_14 = 0;
	rva0006F373(a, b, c, d, e, f);
}
