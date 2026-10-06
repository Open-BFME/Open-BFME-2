// cl: /MD
// ?rva001F4882@Rva001F4882@@QAEXPAUNode001F4882@@@Z @0x001F4882 (93B)
// Unlink node from doubly-linked prev at +0x6c next at +0x70 with in-use
// flag at +0x75. Slot from rowed get at 0x001F45DF indexes head arrays at
// this+0x10 and this+0x2c. Clears links and flag then dec count at +0x50.
// Ret 4. Caller 0x001F4C67. Evidence unlock lane plus get row plus prev
// destroy plus leaf getters.
class ParticleSystem;
ParticleSystem *Make001FCBD7();
struct Rva001F45DFInner {
	char m_pad[0x7c];
	int m_value;
};
class Rva001F45DFSlot {
public:
	int get() const;
	char m_lead[0x3c];
	Rva001F45DFInner *m_ptr;
};
struct Node001F4882 : public Rva001F45DFSlot
{
	char m_pad2[0x6c - 0x40];
	Node001F4882 *m_prev;
	Node001F4882 *m_next;
	char m_gap;
	unsigned char m_flag;
};
class Rva001F4882
{
public:
	void rva001F4882(Node001F4882 *node);
private:
	char m_pad0[0x10];
	Node001F4882 *m_arr1[7];
	Node001F4882 *m_arr2[9];
	int m_count;
};
void Rva001F4882::rva001F4882(Node001F4882 *node)
{
	if (node->m_flag == 0)
		return;
	int slot = node->get();
	if (node->m_prev != 0)
		node->m_prev->m_next = node->m_next;
	if (node->m_next != 0)
		node->m_next->m_prev = node->m_prev;
	if (node == m_arr1[slot])
		m_arr1[slot] = node->m_prev;
	Node001F4882 **pp = &m_arr2[slot];
	if (node == *pp)
		*pp = node->m_next;
	node->m_next = 0;
	node->m_prev = 0;
	node->m_flag = 0;
	--m_count;
}
