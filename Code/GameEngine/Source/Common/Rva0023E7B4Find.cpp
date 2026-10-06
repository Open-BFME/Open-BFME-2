// cl: /MD
// ?rva0023E7B4@Rva0023E7B4@@QAEPAXG@Z — RVA 0x0023E7B4, 37B.
// Circular intrusive-list search: head ptr at +0x1c0, node next at +0,
// key word at +0xc, hit returns node+8 else NULL.
// Evidence: retail loop bytes; caller at 0x0024797E; neighbours in
// Code/GameEngine/Source/Common/Disp32FirstChaseGetters.cpp.
struct Rva0023E7B4Node
{
	Rva0023E7B4Node *m_next;
	char m_pad[8];
	unsigned short m_key;
};

class Rva0023E7B4
{
public:
	void *rva0023E7B4(unsigned short key);
	char m_lead[0x1c0];
	Rva0023E7B4Node *m_head;
};

void *Rva0023E7B4::rva0023E7B4(unsigned short key)
{
	Rva0023E7B4Node *head = m_head;
	for (Rva0023E7B4Node *p = head->m_next; p != head; p = p->m_next)
	{
		if (p->m_key == key)
			return (char *)p + 8;
	}
	return 0;
}
