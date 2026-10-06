// cl: /GX-
//
// ?rva00599FAA@Rva00599FAA@@QAEXPAUNode00599FAA@@@Z @0x00599FAA 45B
// Intrusive list clear with recursive child at +0x0C and next at +0x08
// via game free at 0x00030830. Evidence: self-call at 0x00599FBC,
// free row, ret-4 single pointer arg, 2 callers, address-derived name.
extern "C" void __cdecl free(void *);

struct Node00599FAA
{
	void *m_pad00;
	void *m_pad04;
	void *m_next08;
	Node00599FAA *m_child0C;
};

class Rva00599FAA
{
public:
	void rva00599FAA(Node00599FAA *p);
};

void Rva00599FAA::rva00599FAA(Node00599FAA *p)
{
	if (p == 0)
		return;
	do
	{
		rva00599FAA(p->m_child0C);
		Node00599FAA *next = (Node00599FAA *)p->m_next08;
		free(p);
		p = next;
	} while (p != 0);
}
