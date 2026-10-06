// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00204136@Rva00204136@@QAEXPAX@Z at retail 0x00204136 (45B).
// Frees a malloc'd node tree with links at +8 (next) and +0xC (other) via rowed _free;
// recurses on +0xC then loops on +8. Target evidence: caller 0x00204984 re-inits list head
// after call; self-recursion at 0x00204148; _free row GameMemoryFree.cpp.
extern "C" void __cdecl free(void *p);

class Rva00204136 {
	struct Node {
		char pad0[4];
		void *pFirst;
		Node *pNext;
		Node *pOther;
	};
	Node *m_sentinel; // +0
	int m_size; // +4
public:
	void rva00204136(void *p);
	void rva00204984();
};

void Rva00204136::rva00204136(void *p)
{
	Node *n = (Node *)p;
	if (!n)
		return;
	while (n) {
		rva00204136(n->pOther);
		Node *next = n->pNext;
		free(n);
		n = next;
	}
}

void Rva00204136::rva00204984()
{
	if (m_size == 0)
		return;
	rva00204136(m_sentinel->pFirst);
	m_sentinel->pNext = m_sentinel;
	m_sentinel->pFirst = 0;
	m_sentinel->pOther = m_sentinel;
	m_size = 0;
}
