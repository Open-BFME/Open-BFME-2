// cl: /MD
// ?Rva002E3714Unlink@@YAXPAURva002E36D5Node@@@Z, retail 0x002E3714, 40 bytes.
// Leaf __cdecl unlink of a node from the singly linked list whose head is
// the global at 0x00DFF0B8 (next pointer at +0x3C, as in the rowed
// Rva002E36D5Find 0x002E36D5 next door): walk the links until the one that
// holds the node, splice it out and clear its next pointer. Callers
// 0x00397E6E, 0x004B083C (AIGateUpdate dtor) and 0x004EB61A, each right
// after Rva002E36D5Find. Owning class unproven, so address names.
struct Rva002E36D5Node
{
	unsigned char m_pad[0x3C];
	Rva002E36D5Node *m_next3C;
};

extern Rva002E36D5Node *g_00DFF0B8;
// g_00DFF0B8: matched references place it at VA 0xdff0b8 (zero-filled .bss).
Rva002E36D5Node * g_00DFF0B8;

void Rva002E3714Unlink(Rva002E36D5Node *node)
{
	Rva002E36D5Node **link = &g_00DFF0B8;
	while (*link != node) {
		if (*link == 0)
			return;
		link = &(*link)->m_next3C;
	}
	*link = node->m_next3C;
	node->m_next3C = 0;
}
