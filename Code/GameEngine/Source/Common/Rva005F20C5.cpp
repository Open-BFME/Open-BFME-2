// cl: /MD
// ?rva005F20C5@Rva005F20C5@@QAEXPAURva005F20C5Node@@@Z, retail 0x005F20C5, 45 bytes.
// Evidence: unlock lane; recursive self-call at 0x005F20D7 plus game free row 0x00030830; callers at 0x005F20D7 self and 0x005F2100 in 0x005F20F2; node +8 next plus +0xC child freed in loop.
extern "C" void __cdecl free(void *p);

struct Rva005F20C5Node
{
	char m_pad00[4];
	Rva005F20C5Node *m_child04;
	Rva005F20C5Node *m_next08;
	Rva005F20C5Node *m_link0C;
};

class Rva005F20C5
{
public:
	void rva005F20C5(Rva005F20C5Node *p);
	void rva005F20F2();
private:
	Rva005F20C5Node *m_head00;
	int m_count04;
};

void Rva005F20C5::rva005F20C5(Rva005F20C5Node *p)
{
	if (p == 0)
		return;
	Rva005F20C5Node *cur = p;
	do {
		rva005F20C5(cur->m_link0C);
		Rva005F20C5Node *next = cur->m_next08;
		free(cur);
		cur = next;
	} while (cur != 0);
}

void Rva005F20C5::rva005F20F2()
{
	if (m_count04 == 0)
		return;
	rva005F20C5(m_head00->m_child04);
	m_head00->m_next08 = m_head00;
	m_head00->m_child04 = 0;
	m_head00->m_link0C = m_head00;
	m_count04 = 0;
}
