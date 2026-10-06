// cl: /EHsc
//
// ?rva00206706@Rva00206706@@QAEXPAURva00206706Node@@@Z @0x00206706 53B: thiscall
// recursive clear over child +0x0C with iteration over next +0x08, destroying
// value +0x10 via rowed dtor 0x00204686 then free. Evidence: rowed dtor
// 0x00204686, rowed free 0x00030830, self-call 0x00206706, caller 0x00206FE6
// same-this clear; unblocks 0x00206FE6.

struct Rva00204686
{
	~Rva00204686();
};

struct Rva00206706Node
{
	char m_pad[8];
	Rva00206706Node *m_next; // +0x08
	Rva00206706Node *m_child; // +0x0C
	Rva00204686 m_value; // +0x10
};

struct Rva00206706Head;

class Rva00206706
{
public:
	void rva00206706(Rva00206706Node *node);
	void rva00206FE6();

private:
	Rva00206706Head *m_head; // +0x00
	int m_count; // +0x04
};

extern "C" void __cdecl free(void *block);

void Rva00206706::rva00206706(Rva00206706Node *node)
{
	if (!node)
		return;
	for (Rva00206706Node *cur = node; cur;) {
		rva00206706(cur->m_child);
		Rva00206706Node *next = cur->m_next;
		cur->m_value.~Rva00204686();
		free(cur);
		cur = next;
	}
}

struct Rva00206706Head
{
	char m_pad[4];
	Rva00206706Node *m_first; // +0x04
	Rva00206706Head *m_link8; // +0x08
	Rva00206706Head *m_linkC; // +0x0C
};

void Rva00206706::rva00206FE6()
{
	if (m_count == 0)
		return;
	rva00206706(m_head->m_first);
	m_head->m_link8 = m_head;
	m_head->m_first = 0;
	m_head->m_linkC = m_head;
	m_count = 0;
}
