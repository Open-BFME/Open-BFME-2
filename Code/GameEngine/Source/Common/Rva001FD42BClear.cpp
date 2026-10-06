// cl: /MD
// ?rva001FD630@Rva001FD42B@@QAEXXZ @0x001FD630 41B.
// Tree clear for the Rva001FD42B node family: if the count at +4 is nonzero,
// erase the root via the rowed rva001FD42B, reset the header sentinel at
// +0 (left/right to self, parent to 0) and zero the count. Same this flows
// to the erase call, proving the shared owner. Callers at 0x001FD6D1
// 0x001FD8EB 0x002AFBB4 and jmp at 0x002ABFFD; unblocks 0x001FD6BC 0x001FD8DF.
struct Rva001FD42BNode
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD42BNode *m_parent;
	Rva001FD42BNode *m_left;
	Rva001FD42BNode *m_right;
	unsigned char m_value[8];
};

struct Rva001FD42B
{
	void rva001FD42B(Rva001FD42BNode *x);
	void rva001FD630();
	Rva001FD42BNode *m_header;
	unsigned int m_count;
};

void Rva001FD42B::rva001FD630()
{
	if (m_count != 0) {
		rva001FD42B(m_header->m_parent);
		m_header->m_left = m_header;
		m_header->m_parent = 0;
		m_header->m_right = m_header;
		m_count = 0;
	}
}
