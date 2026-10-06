// cl: /DNDEBUG /MD
// ?rva00398257@Rva00397C94@@QAEXXZ @0x00398257 41B evidence: same class as callee 0x00397C94 rowed Rva00397C94Clear (this unchanged across call); caller 0x0039928D 0x0039A09D plus jmp 0x00399273; resets list-like head after clear per prev comment; this+4 zero guard then head+8 self head+4 zero head+0xc self this+4 zero.

struct Rva00397C94Node
{
	void *m_pad00;
	void *m_pad04;
	Rva00397C94Node *m_next;
	Rva00397C94Node *m_child;
	char m_marker[4];
};

struct Rva00397C94Head
{
	void *m_00;
	Rva00397C94Node *m_04;
	Rva00397C94Head *m_08;
	Rva00397C94Head *m_0c;
};

class Rva00397C94
{
public:
	void rva00397C94(Rva00397C94Node *node);
	void rva00398257();
private:
	Rva00397C94Head *m_head;
	int m_04;
};

void Rva00397C94::rva00398257()
{
	if (m_04 == 0)
		return;
	rva00397C94(m_head->m_04);
	m_head->m_08 = m_head;
	m_head->m_04 = 0;
	m_head->m_0c = m_head;
	m_04 = 0;
}
