// cl: /MD
// ?Rva002E36D5Find@@YAPAXH@Z, retail 0x002E36D5, 26 bytes.
// Leaf __cdecl find-by-ID over global list at 0x00DBD0F4 (holder head at +0).
// Node next at +0x3C ID at +0x44. Callers 0x00058880 0x004B082F. Owning
// class unproven so honest Rva names. Shape is while-find with jmp-to-test.
struct Rva002E36D5Node
{
	unsigned char m_pad[0x3C];
	Rva002E36D5Node *m_next3C;
	unsigned char m_pad40[4];
	int m_id44;
};
struct Rva002E36D5Holder
{
	Rva002E36D5Node *m_head;
};

struct Rva002E373CHolder;
extern Rva002E373CHolder *g_Va00DBD0F4;

void *Rva002E36D5Find(int id)
{
	Rva002E36D5Node *cur = ((Rva002E36D5Holder *)g_Va00DBD0F4)->m_head;
	while (cur != 0) {
		if (cur->m_id44 == id)
			break;
		cur = cur->m_next3C;
	}
	return cur;
}
