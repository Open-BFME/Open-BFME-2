// ?reset@NetCommandList@@QAEXXZ
// cl: /O1 /G6 /DNDEBUG /MD
//
// NetCommandList::reset, retail 0x0058B283, 67 bytes. Zero Hour's loop: unlink
// and destroy the head node until the list is empty, then clear the counters.
// Each node's +4/+8 links are cleared before it is detached and deleted.

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
	while (m_head != 0)
	{
		NetCommandNode *temp = m_head->m_next;
		m_head->m_next = 0;
		m_head->m_unreconstructed_08 = 0;
		NetCommandNode *node = m_head;
		if (node != 0)
		{
			node->detach();
			delete node;
		}
		m_head = temp;
	}
	m_count = 0;
	m_unreconstructed_0C = 0;
}
