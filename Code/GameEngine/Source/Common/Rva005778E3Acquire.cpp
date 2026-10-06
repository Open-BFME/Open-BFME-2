// cl: /MD
// ?rva005778E3@Rva005778E3@@QAEHXZ @ 0x005778E3 (25B):
// Acquire counterpart to 0x005778FC release on double-indirect holder at +0x40;
// bumps flag at +0xC and count at +0x10 returning the old flag. Evidence: caller
// 0x00577FE2 stores return at [esi+0x10]; old-in-eax explains esi plus lea shape.

struct Rva005778E3Inner
{
	char m_pad[0xC];
	int m_flag;
	int m_count;
};

struct Rva005778E3Holder
{
	Rva005778E3Inner *m_ptr;
};

class Rva005778E3
{
	char m_pad[0x40];
	Rva005778E3Holder *m_holder;

public:
	int rva005778E3();
};

int Rva005778E3::rva005778E3()
{
	Rva005778E3Holder *h = m_holder;
	Rva005778E3Inner *p = h->m_ptr;
	int old = p->m_flag;
	p->m_flag = old + 1;
	p = m_holder->m_ptr;
	++p->m_count;
	return old;
}
