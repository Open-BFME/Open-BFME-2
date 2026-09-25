// ?reset@NetCommandList@@QAEXXZ
// cl: /O1 /G6 /DNDEBUG /MD
//
// NetCommandList::reset, retail 0x0058B283, 67 bytes. Zero Hour's loop: unlink
// and destroy the head node until the list is empty, then clear the counters.
// Each node's +4/+8 links are cleared before it is detached and deleted.

class NetCommandMsg
{
public:
	void detach();
};

class NetCommandNode
{
public:
	void detach();

	NetCommandMsg *m_msg; ///< retail this+0x00, released by detach
	NetCommandNode *m_next; ///< retail this+0x04, cleared by reset
	NetCommandNode *m_prev; ///< retail this+0x08, cleared by reset
};

// BFME2's message handle shares the node layout (command at +0, next at
// +4, prev at +8) under its own name, which is what removeMessage's
// mangling carries.
class NetCommandRef
{
public:
	NetCommandMsg *m_command;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
};

class NetCommandList
{
	void *m_unreconstructed_00;
	NetCommandNode *m_first;
	NetCommandNode *m_last;
	NetCommandNode *m_lastMessageInserted;

public:
	void reset();
	void removeMessage(NetCommandRef *msg);
};

void NetCommandList::reset()
{
	while (m_first != 0)
	{
		NetCommandNode *temp = m_first->m_next;
		m_first->m_next = 0;
		m_first->m_prev = 0;
		NetCommandNode *node = m_first;
		if (node != 0)
		{
			node->detach();
			delete node;
		}
		m_first = temp;
	}
	m_last = 0;
	m_lastMessageInserted = 0;
}

// ?detach@NetCommandNode@@QAEXXZ
void NetCommandNode::detach()
{
	if (m_msg)
		m_msg->detach();
}

// ?removeMessage@NetCommandList@@QAEXPAVNetCommandRef@@@Z
void NetCommandList::removeMessage(NetCommandRef *msg)
{
	NetCommandNode *ref = (NetCommandNode *)msg;
	if (m_lastMessageInserted == ref) {
		m_lastMessageInserted = ref->m_next;
	}
	if (ref->m_prev != 0) {
		ref->m_prev->m_next = ref->m_next;
	}
	if (ref->m_next != 0) {
		ref->m_next->m_prev = ref->m_prev;
	}
	if (ref == m_first) {
		m_first = ref->m_next;
	}
	if (ref == m_last) {
		m_last = ref->m_prev;
	}
	ref->m_next = 0;
	ref->m_prev = 0;
}
