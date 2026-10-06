// cl: /MD /EHs
// ?rva004E7C1C@Rva004E7C1C@@QAEXXZ @0x004E7C1C 49B
// List clear: free each node after running its +8 cleanup then reset sentinel.
// Evidence: callees rva004E7A76 0x004E7A76 free 0x00030830 rowed; callers 0x004E7C8A 0x004E7CDD 0x004E7CFE; node next +0 prev +4 value +8 head reset.
extern "C" void __cdecl free(void *block);

class Rva004E7A76
{
public:
	void rva004E7A76();
	char m_pad[8];
	void *m_p8;
};

struct Rva004E7C1CNode
{
	Rva004E7C1CNode *m_next;
	Rva004E7C1CNode *m_prev;
	Rva004E7A76 m_data;
};

class Rva004E7C1C
{
public:
	void rva004E7C1C();
	void rva004E7C8A();
private:
	Rva004E7C1CNode *m_head;
};

void Rva004E7C1C::rva004E7C1C()
{
	Rva004E7C1CNode *cur = m_head->m_next;
	if (cur != m_head)
	{
		Rva004E7C1CNode *b;
		do
		{
			b = cur;
			cur = cur->m_next;
			b->m_data.rva004E7A76();
			free(b);
		} while (cur != m_head);
	}
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}

void Rva004E7C1C::rva004E7C8A()
{
	rva004E7C1C();
	Rva004E7C1CNode *head = m_head;
	if (head != 0)
		free(head);
}
