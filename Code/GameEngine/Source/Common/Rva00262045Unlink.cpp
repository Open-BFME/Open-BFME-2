// cl: /DNDEBUG /MD
//
// ?rva00262045@Rva00262045@@QAEXPAUNode00262045@@@Z, retail 0x00262045, 50 bytes.
// Doubly-linked unlink: if arg null or head +0x0C null return; if arg next
// non-null set next prev to arg prev; then if arg prev non-null set prev
// next to arg next else set head to arg next. Next at +0x0C prev at +0x10.
// Honest address-derived owner and node; layout from the +0x0C/+0x10 pair
// shared with the Rva0026201C ctor. Outer ret 4. No callees.

struct Node00262045
{
	char m_pad00[0x0C];
	Node00262045 *m_next;
	Node00262045 *m_prev;
};

class Rva00262045
{
	char m_pad00[0x0C];
	Node00262045 *m_head;
public:
	void rva00262045(Node00262045 *n);
};

void Rva00262045::rva00262045(Node00262045 *n)
{
	if (!n)
		return;
	if (m_head == 0)
		return;
	if (n->m_next)
		n->m_next->m_prev = n->m_prev;
	if (n->m_prev)
		n->m_prev->m_next = n->m_next;
	else
		m_head = n->m_next;
}
