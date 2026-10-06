// cl: /MD
// ?rva004D9A62@Rva004D9A62@@QAEXXZ @0x004D9A62 (41B):
// Reset: if +4 zero return; else recurse rowed 0x004D968D on ptr+4, reinit
// ptr+8/self ptr+4/0 ptr+0xC/self and +4/0. Evidence: chain lane, calls
// 0x004D968D just landed, cmp-je plus 3x reload shape, caller 0x004D9AF5,
// unblocks 0x004D9AE0.
struct Rva004D968DNode
{
	char m_pad[8];
	Rva004D968DNode *m_next;
	Rva004D968DNode *m_child;
};

class Rva004D968D
{
public:
	void rva004D968D(Rva004D968DNode *node);
};

struct Rva004D9A62Block
{
	int m_0;
	Rva004D968DNode *m_4;
	Rva004D968DNode *m_8;
	Rva004D968DNode *m_c;
};

class Rva004D9A62 : public Rva004D968D
{
public:
	void rva004D9A62();
private:
	Rva004D9A62Block *m_ptr;
	int m_4;
};

void Rva004D9A62::rva004D9A62()
{
	if (m_4 == 0)
		return;
	rva004D968D(m_ptr->m_4);
	m_ptr->m_8 = (Rva004D968DNode *)m_ptr;
	m_ptr->m_4 = 0;
	m_ptr->m_c = (Rva004D968DNode *)m_ptr;
	m_4 = 0;
}
