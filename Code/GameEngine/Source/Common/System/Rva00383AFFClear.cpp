// cl: /MD
// ?rva00383AFF@Rva00383AFF@@QAEXXZ, retail 0x00383AFF, 49 bytes.
// List clear over BuddyMessage nodes via rowed dtor 0x0038215B plus rowed
// free 0x00030830. Identity from unlock (makes 0x00383F3C ready) and callers
// 0x00383F3F/0x00385D6C.
class BuddyMessage
{
public:
	~BuddyMessage() throw();
};

struct BuddyListNode
{
	BuddyListNode *m_next;
	BuddyListNode *m_prev;
	BuddyMessage m_msg;
};

struct Rva00383AFF
{
	BuddyListNode *m_head;

	void rva00383AFF();
	~Rva00383AFF();
};

extern "C" void __cdecl free(void *block);

void Rva00383AFF::rva00383AFF()
{
	BuddyListNode *cur = m_head->m_next;
	if (cur == m_head)
		goto empty;
	do {
		BuddyListNode *node = cur;
		cur = node->m_next;
		node->m_msg.~BuddyMessage();
		free(node);
	} while (cur != m_head);
empty:
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}

Rva00383AFF::~Rva00383AFF()
{
	rva00383AFF();
	if (m_head)
		free(m_head);
}
