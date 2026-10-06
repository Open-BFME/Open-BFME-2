// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00504112@Rva00504112@@QAEPAXPAX@Z @0x00504112 (38B):
// Tree lower_bound over control-point nodes keyed by m_18 at node+0x28.
// Header at [this], root at [header+4], left at [node+8], right at [node+0xC].
// Unsigned compare (jb), returns header when empty or no lower bound.
// Evidence: callers 0x005041A6 0x0050433F, unblocks 0x005042F2, node key at
// +0x28 matches Rva00064390 m_18 at value+0x18, header parent/left/right shape.
class Rva00504112
{
public:
	void *rva00504112(void *rec);
private:
	struct Node
	{
		int m_color;
		Node *m_parent;
		Node *m_left;
		Node *m_right;
		char m_pad[0x18];
		unsigned int m_key;
	};
	Node *m_header;
	int m_count;
};

void *Rva00504112::rva00504112(void *rec)
{
	Node *header = m_header;
	Node *cur = header->m_parent;
	if (cur == 0)
		return header;
	unsigned int key = *(unsigned int *)((char *)rec + 0x18);
	Node *res = header;
	do {
		if (*(unsigned int *)((char *)cur + 0x28) >= key) {
			res = cur;
			cur = cur->m_left;
		} else
			cur = cur->m_right;
	} while (cur != 0);
	return res;
}
