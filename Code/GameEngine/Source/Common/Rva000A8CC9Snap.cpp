// cl: /MD /EHsc /DNDEBUG
//
// ?rva000A8CC9@Rva000A8CC9@@QAEXXZ @0x000A8CC9 28B: snapshot-and-clear.
// When the +0x0 member is set, copies its +0x20 int into +0x4 and calls
// the pinned no-arg method 0x0010F9F1 on it, then tail-jumps to the
// rowed Rva000A8C9B::clear (0x000A8C9B) on this. Honest address-derived
// names; boundary verified (push esi at 0xA8CC9, jmp at end).

class Rva0010F9F1
{
public:
	void rva0010F9F1();

	char m_pad00[0x20];
	int m_20;
};

struct Rva000A8C9B
{
	void clear();
};

class Rva000A8CC9
{
public:
	void rva000A8CC9();

private:
	Rva0010F9F1 *m_0;
	int m_4;
};

// ?rva000A8CC9@Rva000A8CC9@@QAEXXZ
void Rva000A8CC9::rva000A8CC9()
{
	if (m_0)
	{
		m_4 = m_0->m_20;
		m_0->rva0010F9F1();
	}
	((Rva000A8C9B *)this)->clear();
}
