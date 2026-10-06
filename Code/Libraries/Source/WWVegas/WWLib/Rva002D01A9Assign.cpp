// cl: /MD
// ??4Rva002D01A9@@QAEAAU0@ABU0@@Z @0x002D01A9 115B.
// Tree assign: self-guard then rowed clear 0x002CF7DE and size reset; empty
// other root zeroes parent and points left/right at header; else rowed copy
// 0x002CFCEE with header in edi across the call then leftmost/rightmost walks
// set header links and size copies other size. Same shape as 0x002D0136.
struct Rva002CFA4ENode
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFA4ENode *m_parent;
	Rva002CFA4ENode *m_left;
	Rva002CFA4ENode *m_right;
	unsigned char m_value[20];
};
struct Rva002CF7DE
{
	void *m_header;
	int m_size;
	void rva002CF7DE();
};
struct Rva002CFCEE
{
	Rva002CFA4ENode *rva002CFCEE(Rva002CFA4ENode *x, Rva002CFA4ENode *p);
};
struct Rva002D01A9Header
{
	int m_color;
	Rva002CFA4ENode *m_parent;
	Rva002CFA4ENode *m_left;
	Rva002CFA4ENode *m_right;
};
struct Rva002D01A9
{
	Rva002D01A9Header *m_header;
	int m_size;
	Rva002D01A9 &operator=(const Rva002D01A9 &other);
};

Rva002D01A9 &Rva002D01A9::operator=(const Rva002D01A9 &other)
{
	if (this != &other) {
		((Rva002CF7DE *)this)->rva002CF7DE();
		m_size = 0;
		Rva002CFA4ENode *root = other.m_header->m_parent;
		if (root == 0) {
			m_header->m_parent = 0;
			m_header->m_left = (Rva002CFA4ENode *)m_header;
			m_header->m_right = (Rva002CFA4ENode *)m_header;
		} else {
			Rva002D01A9Header *h = m_header;
			Rva002CFA4ENode *top = ((Rva002CFCEE *)this)->rva002CFCEE(root, (Rva002CFA4ENode *)h);
			h->m_parent = top;
			Rva002CFA4ENode *leftmost = m_header->m_parent;
			while (leftmost->m_left != 0)
				leftmost = leftmost->m_left;
			m_header->m_left = leftmost;
			Rva002CFA4ENode *rightmost = m_header->m_parent;
			while (rightmost->m_right != 0)
				rightmost = rightmost->m_right;
			m_header->m_right = rightmost;
			m_size = other.m_size;
		}
	}
	return *this;
}
