// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00421BF7@Rva00421BF7@@QAEXPAX@Z @0x00421BF7 45B
// Walk +8 chain freeing each node after recursing on its +0xC child:
// while (n) { rva00421BF7(n->m_child); next = n->m_next; free(n); n = next; }
// Evidence: unlock lane; self-call at 0x00421C09; free row 0x00030830;
// caller at 0x00421EF8; neighbours share /O1 flags.
extern "C" void __cdecl free(void *);

struct Rva00421BF7Node
{
	char m_pad[8];
	Rva00421BF7Node *m_next;
	Rva00421BF7Node *m_child;
};

struct Rva00421BF7Header
{
	char m_pad0[4];
	Rva00421BF7Node *m_first;
	Rva00421BF7Header *m_link8;
	Rva00421BF7Header *m_linkC;
};

class Rva00421BF7
{
public:
	void rva00421BF7(void *n);
	void rva00421EEA();
	Rva00421BF7Header *m_header;
	int m_count;
};
void Rva00421BF7::rva00421BF7(void *n)
{
	Rva00421BF7Node *p = (Rva00421BF7Node *)n;
	while (p != 0)
	{
		rva00421BF7(p->m_child);
		Rva00421BF7Node *next = p->m_next;
		free(p);
		p = next;
	}
}
void Rva00421BF7::rva00421EEA()
{
	if (m_count == 0)
		return;
	rva00421BF7(m_header->m_first);
	m_header->m_link8 = m_header;
	m_header->m_first = 0;
	m_header->m_linkC = m_header;
	m_count = 0;
}
class Rva00421C24
{
public:
	void rva00421C24(void *n);
	void rva00421F13();
	Rva00421BF7Header *m_header;
	int m_count;
};
void Rva00421C24::rva00421C24(void *n)
{
	Rva00421BF7Node *p = (Rva00421BF7Node *)n;
	while (p != 0)
	{
		rva00421C24(p->m_child);
		Rva00421BF7Node *next = p->m_next;
		free(p);
		p = next;
	}
}
void Rva00421C24::rva00421F13()
{
	if (m_count == 0)
		return;
	rva00421C24(m_header->m_first);
	m_header->m_link8 = m_header;
	m_header->m_first = 0;
	m_header->m_linkC = m_header;
	m_count = 0;
}
class Rva00421CE9
{
public:
	void rva00421CE9(void *n);
	void rva00421FDE();
	Rva00421BF7Header *m_header;
	int m_count;
};
void Rva00421CE9::rva00421CE9(void *n)
{
	Rva00421BF7Node *p = (Rva00421BF7Node *)n;
	while (p != 0)
	{
		rva00421CE9(p->m_child);
		Rva00421BF7Node *next = p->m_next;
		free(p);
		p = next;
	}
}
void Rva00421CE9::rva00421FDE()
{
	if (m_count == 0)
		return;
	rva00421CE9(m_header->m_first);
	m_header->m_link8 = m_header;
	m_header->m_first = 0;
	m_header->m_linkC = m_header;
	m_count = 0;
}
