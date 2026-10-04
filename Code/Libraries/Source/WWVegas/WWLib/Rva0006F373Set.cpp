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
private:
	void *m_00;
	int m_04;
	int m_08;
	void *m_0C;
	void *m_10;
	void *m_14;
};

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
