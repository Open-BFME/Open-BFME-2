// cl: /MD
// ??4Rva002D0136@@QAEAAU0@ABU0@@Z @0x002D0136 115B.
// Tree assign: self-guard then rowed clear 0x002CF7B5 and size reset; empty
// other root zeroes parent and points left/right at header; else rowed copy
// 0x002CFC7B with header in edi across the call then leftmost/rightmost walks
// set header links and size copies other size. Same shape as rowed map copy.
struct Rva002CFA30Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFA30Node *m_parent;
	Rva002CFA30Node *m_left;
	Rva002CFA30Node *m_right;
	unsigned char m_value[20];
};
struct Rva002CF7B5
{
	void *m_header;
	int m_size;
	void rva002CF7B5();
};
struct Rva002CFC7B
{
	Rva002CFA30Node *rva002CFA30(const Rva002CFA30Node *src);
	Rva002CFA30Node *rva002CFC7B(Rva002CFA30Node *x, Rva002CFA30Node *p);
};
struct Rva002D0136Header
{
	int m_color;
	Rva002CFA30Node *m_parent;
	Rva002CFA30Node *m_left;
	Rva002CFA30Node *m_right;
};
struct Rva002D0136
{
	Rva002D0136Header *m_header;
	int m_size;
	Rva002D0136 &operator=(const Rva002D0136 &other);
};

Rva002D0136 &Rva002D0136::operator=(const Rva002D0136 &other)
{
	if (this != &other) {
		((Rva002CF7B5 *)this)->rva002CF7B5();
		m_size = 0;
		Rva002CFA30Node *root = other.m_header->m_parent;
		if (root == 0) {
			m_header->m_parent = 0;
			m_header->m_left = (Rva002CFA30Node *)m_header;
			m_header->m_right = (Rva002CFA30Node *)m_header;
		} else {
			Rva002D0136Header *h = m_header;
			Rva002CFA30Node *top = ((Rva002CFC7B *)this)->rva002CFC7B(root, (Rva002CFA30Node *)h);
			h->m_parent = top;
			Rva002CFA30Node *leftmost = m_header->m_parent;
			while (leftmost->m_left != 0)
				leftmost = leftmost->m_left;
			m_header->m_left = leftmost;
			Rva002CFA30Node *rightmost = m_header->m_parent;
			while (rightmost->m_right != 0)
				rightmost = rightmost->m_right;
			m_header->m_right = rightmost;
			m_size = other.m_size;
		}
	}
	return *this;
}
