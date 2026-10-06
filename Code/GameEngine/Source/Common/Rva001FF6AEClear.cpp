// cl: /MD
//
// ?rva001FF6AE@Rva001FF6D7@@QAEXXZ @0x001FF6AE 41B
// Chain lane: clears the container by tearing down the node list at
// m_head+4 through the rowed 0x001FF55F body, then reinitialises the head
// as an empty sentinel and zeroes the count. Same pattern as 0x005562DD.
// Caller 0x001FF755.
struct Rva001FF6D7Node;

struct Rva001FF6D7Head
{
	int m_pad0;
	Rva001FF6D7Node *m_list; // +4
	Rva001FF6D7Head *m_next; // +8
	Rva001FF6D7Head *m_prev; // +0xc
};

struct Rva001FF6D7Node
{
	void *m_globalNext; // +0
	int m_pad; // +4
	Rva001FF6D7Node *m_next; // +8
	Rva001FF6D7Node *m_child; // +0xc
};

class Rva001FF6D7
{
public:
	void rva001FF6AE();
	void rva001FF55F(Rva001FF6D7Node *head);

private:
	Rva001FF6D7Head *m_head; // +0
	int m_count; // +4
};

void Rva001FF6D7::rva001FF6AE()
{
	if (m_count == 0)
		return;
	rva001FF55F(m_head->m_list);
	m_head->m_next = m_head;
	m_head->m_list = 0;
	m_head->m_prev = m_head;
	m_count = 0;
}
