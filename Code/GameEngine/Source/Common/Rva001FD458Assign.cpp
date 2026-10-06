// cl: /MD
// ?rva001FD952@Rva001FD458@@QAEPAU1@ABU1@@Z @0x001FD952 115B.
// Tree assign for the Rva001FD458 node family: self-check, clear via rowed
// rva001FD659, reset count, copy non-empty trees via rowed rva001FD7C4,
// fix leftmost via +8 and rightmost via +0xC, copy count, return this.
// Same 115B shape as the rowed Rva001FD42B assign 0x001FD8DF
// (Rva001FD42BAssign.cpp precedent). Callers at 0x001FD709 0x002AFBE0.
struct Rva001FD458Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD458Node *m_parent;
	Rva001FD458Node *m_left;
	Rva001FD458Node *m_right;
	unsigned char m_value[8];
};

struct Rva001FD7C4Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD7C4Node *m_parent;
	Rva001FD7C4Node *m_left;
	Rva001FD7C4Node *m_right;
	unsigned char m_value[8];
};

struct Rva001FD7C4
{
	Rva001FD7C4Node *rva001FD7C4(Rva001FD7C4Node *x, Rva001FD7C4Node *p);
};

struct Rva001FD458
{
	void rva001FD659();
	Rva001FD458 *rva001FD952(const Rva001FD458 &other);
	Rva001FD458Node *m_header;
	unsigned int m_count;
};

Rva001FD458 *Rva001FD458::rva001FD952(const Rva001FD458 &other)
{
	if (this != &other) {
		rva001FD659();
		m_count = 0;
		Rva001FD458Node *otherRoot = other.m_header->m_parent;
		if (otherRoot == 0) {
			m_header->m_parent = 0;
			m_header->m_left = m_header;
			m_header->m_right = m_header;
		} else {
			Rva001FD7C4 *self = (Rva001FD7C4 *)this;
			Rva001FD458Node *hdr = m_header;
			hdr->m_parent = (Rva001FD458Node *)self->rva001FD7C4((Rva001FD7C4Node *)otherRoot, (Rva001FD7C4Node *)hdr);
			Rva001FD458Node *x = m_header->m_parent;
			while (x->m_left != 0)
				x = x->m_left;
			m_header->m_left = x;
			x = m_header->m_parent;
			while (x->m_right != 0)
				x = x->m_right;
			m_header->m_right = x;
			m_count = other.m_count;
		}
	}
	return this;
}
