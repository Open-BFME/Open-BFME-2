// cl: /DNDEBUG /MD /EHsc
//
// ?rva007590B0@Rva007590B0@@QAEXPAURva007590B0Node@@@Z retail 0x007590B0 51B
// Evidence: unlock lane; callees rowed self plus _free 0x00030830; callers 0x00759AE0 0x00759B40 0x0075A1A0 plus self; prev Rva009A3300HashTableRemove same dir and flags; sibling 0x00759AE0 same 51B twin.
// ?rva00759AE0@Rva007590B0@@QAEXXZ retail 0x00759AE0 51B
// Evidence: chain via 0x007590B0; no callers; same class reset sentinel after tree free.
struct Rva007590B0Node
{
	char m_pad[8];
	Rva007590B0Node *m_next;
	Rva007590B0Node *m_child;
};

struct Rva007590B0Head
{
	char m_pad0[4];
	Rva007590B0Node *m_child;
	Rva007590B0Head *m_next;
	Rva007590B0Head *m_other;
};

class Rva007590B0
{
public:
	void rva007590B0(Rva007590B0Node *node);
	void rva00759AE0();
private:
	Rva007590B0Head *m_head;
	void *m_state;
};

extern "C" void __cdecl free(void *block);

void Rva007590B0::rva007590B0(Rva007590B0Node *node)
{
	if (node == 0)
		return;
	Rva007590B0Node *cur = node;
	do {
		rva007590B0(cur->m_child);
		Rva007590B0Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur != 0);
}

void Rva007590B0::rva00759AE0()
{
	if (m_state == 0)
		return;
	rva007590B0(m_head->m_child);
	m_head->m_next = m_head;
	m_head->m_child = 0;
	m_head->m_other = m_head;
	m_state = 0;
}
