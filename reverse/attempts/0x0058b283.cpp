// ?reset@NetCommandList@@QAEXXZ
// partial score=0.95 date=2026-09-10
// cl: /O1 /G6 /DNDEBUG /MD
//
// NetCommandList::reset, retail 0x0058B283, 67 bytes.
// Walks the head list at +4, clears each node's +4/+8, deletes the node,
// then zeros the two counters at +8 and +0xC.

class NetCommandNode
{
public:
	void detach();

	NetCommandNode *m_unreconstructed_00;
	NetCommandNode *m_next;
	void *m_unreconstructed_08;
};

class NetCommandList
{
	void *m_unreconstructed_00;
	NetCommandNode *m_head;
	int m_count;
	int m_unreconstructed_0C;

public:
	void reset();
};

void NetCommandList::reset()
{
	NetCommandNode *none = 0;
	if (m_head != none)
	{
		NetCommandNode *next;
		do
		{
			next = m_head->m_next;
			m_head->m_next = none;
			m_head->m_unreconstructed_08 = none;
			NetCommandNode *node = m_head;
			if (node != none)
			{
				node->detach();
				delete node;
			}
			m_head = next;
		} while (next != none);
	}
	m_count = (int)none;
	m_unreconstructed_0C = (int)none;
}
