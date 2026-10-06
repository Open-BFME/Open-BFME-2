// cl: /EHsc /MD
// ?rva0021C459@Rva0021C459@@QAEXPAUNode0021C459@@@Z @0x0021C459 53B recurse-right via +0xC walk-left via +0x8 clear value at +0x10 via rowed 0x005B804E free 0x00030830.
// Evidence: unlock lane all callees rowed; same 53B shape as rowed erase 0x0021C3B2 but with Unicode StringBase clear; prev-row WideConcatPair proves Unicode family; next-row hero tree proves page.
template <typename T> class StringBase {
public:
	void clear();
private:
	void *m_data;
};
struct Node0021C459 {
	unsigned char m_pad0[4];
	Node0021C459 *m_parent;
	Node0021C459 *m_left;
	Node0021C459 *m_right;
	StringBase<unsigned short> m_value;
};
class Rva0021C459 {
public:
	void rva0021C459(Node0021C459 *node);
	void rva0021CF03();
private:
	Node0021C459 *m_header;
	int m_count;
};
extern "C" void free(void *ptr);
void Rva0021C459::rva0021C459(Node0021C459 *node)
{
	if (node == 0)
		return;
	while (true) {
		rva0021C459(node->m_right);
		Node0021C459 *next = node->m_left;
		node->m_value.clear();
		free(node);
		node = next;
		if (node == 0)
			break;
	}
}
// ?rva0021CF03@Rva0021C459@@QAEXXZ @0x0021CF03 41B clear via rowed cleanup 0x0021C459 with header reset.
void Rva0021C459::rva0021CF03()
{
	if (m_count == 0)
		return;
	rva0021C459(m_header->m_parent);
	m_header->m_left = m_header;
	m_header->m_parent = 0;
	m_header->m_right = m_header;
	m_count = 0;
}
