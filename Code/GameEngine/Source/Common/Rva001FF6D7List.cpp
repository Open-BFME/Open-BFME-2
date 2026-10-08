// cl: /MD
//
// ?rva001FF6D7@Rva001FF6D7@@QAEXXZ @0x001FF6D7 20B
// Unlock lane: if m_ptr null return else prepend node to global list at
// 0x009B9448 (node->next = global; global = node). Caller 0x001FF75D.
// Unwind funclet 0x0076C22E jmps here.
#include "../../Include/Common/Rva002E8548Pool.h"

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
	void rva001FF6D7();
	void rva001FF55F(Rva001FF6D7Node *head);

private:
	void *m_ptr;
};

void Rva001FF6D7::rva001FF6D7()
{
	void *node = m_ptr;
	if (node == 0)
		return;
	*(void **)node = g_Va00DB9440.m_head;
	g_Va00DB9440.m_head = node;
}

void Rva001FF6D7::rva001FF55F(Rva001FF6D7Node *head)
{
	Rva001FF6D7Node *cur = head;
	if (cur == 0)
		return;
	do
	{
		rva001FF55F(cur->m_child);
		Rva001FF6D7Node *next = cur->m_next;
		cur->m_globalNext = g_Va00DB9440.m_head;
		g_Va00DB9440.m_head = cur;
		cur = next;
	} while (cur != 0);
}
