// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// ?rva00156640@Rva001553C0@@QAEXXZ at 0x00156640 50B: clear child-sibling tree via rva001553C0 then reset sentinel.
// Evidence: callee 0x001553C0 rowed, chain from 0x001553C0 landing, prev Reset 0x00155A20 same dir.

struct Rva001553C0_Node
{
	void *unk00;
	Rva001553C0_Node *unk04;
	Rva001553C0_Node *next;
	Rva001553C0_Node *child;
};

class Rva001553C0
{
public:
	void rva001553C0(Rva001553C0_Node *node);
	void rva00156640();
private:
	Rva001553C0_Node *m_head;
	int m_count;
};

void Rva001553C0::rva00156640()
{
	if (m_count == 0)
		return;
	rva001553C0(m_head->unk04);
	m_head->next = m_head;
	m_head->unk04 = 0;
	m_head->child = m_head;
	m_count = 0;
}
