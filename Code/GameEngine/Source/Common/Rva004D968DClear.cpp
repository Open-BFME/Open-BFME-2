// cl: /MD
// ?rva004D968D@Rva004D968D@@QAEXPAURva004D968DNode@@@Z @0x004D968D (45B):
// Recursive list/tree free: if null return; recurse on +0xC child, free node
// via rowed _free 0x00030830, iterate via +0x8 sibling. Evidence: unlock lane,
// self-call plus free plus loop shape, callers 0x004D969F 0x004D9A70,
// unblocks 0x004D9A62.
extern "C" void __cdecl free(void *block);

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

void Rva004D968D::rva004D968D(Rva004D968DNode *node)
{
	if (node == 0)
		return;
	do {
		rva004D968D(node->m_child);
		Rva004D968DNode *next = node->m_next;
		free(node);
		node = next;
	} while (node != 0);
}
