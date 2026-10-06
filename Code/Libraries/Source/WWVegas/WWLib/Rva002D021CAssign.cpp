// cl: /MD
// ??4Rva002D021C@@QAEAAU0@ABU0@@Z @0x002D021C 115B.
// Tree assign: self-guard then rowed clear 0x002CF807 and size reset; empty
// other root zeroes parent and points left/right at header; else rowed copy
// 0x002CFD96 with header in edi across the call then leftmost/rightmost walks
// set header links and size copies other size. Same shape as 0x002D0136.
struct Rva002CFD96Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFD96Node *m_parent;
	Rva002CFD96Node *m_left;
	Rva002CFD96Node *m_right;
	unsigned char m_value[20];
};
struct Rva002CF807
{
	void *m_header;
	int m_size;
	void rva002CF807();
};
struct Rva002CFD96
{
	Rva002CFD96Node *rva002CFD96(Rva002CFD96Node *x, Rva002CFD96Node *p);
};
struct Rva002D021CHeader
{
	int m_color;
	Rva002CFD96Node *m_parent;
	Rva002CFD96Node *m_left;
	Rva002CFD96Node *m_right;
};
struct Rva002D021C
{
	Rva002D021CHeader *m_header;
	int m_size;
	Rva002D021C &operator=(const Rva002D021C &other);
};

Rva002D021C &Rva002D021C::operator=(const Rva002D021C &other)
{
	if (this != &other) {
		((Rva002CF807 *)this)->rva002CF807();
		m_size = 0;
		Rva002CFD96Node *root = other.m_header->m_parent;
		if (root == 0) {
			m_header->m_parent = 0;
			m_header->m_left = (Rva002CFD96Node *)m_header;
			m_header->m_right = (Rva002CFD96Node *)m_header;
		} else {
			Rva002D021CHeader *h = m_header;
			Rva002CFD96Node *top = ((Rva002CFD96 *)this)->rva002CFD96(root, (Rva002CFD96Node *)h);
			h->m_parent = top;
			Rva002CFD96Node *leftmost = m_header->m_parent;
			while (leftmost->m_left != 0)
				leftmost = leftmost->m_left;
			m_header->m_left = leftmost;
			Rva002CFD96Node *rightmost = m_header->m_parent;
			while (rightmost->m_right != 0)
				rightmost = rightmost->m_right;
			m_header->m_right = rightmost;
			m_size = other.m_size;
		}
	}
	return *this;
}
