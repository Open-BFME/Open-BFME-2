// cl: /MD
// ?rva002CF7B5@Rva002CF7B5@@QAEXXZ @0x002CF7B5 41B.
// Tree clear: if size at +4 !=0 erase root at header+4 via rowed 0x002CF2D5,
// reset header left/right to self and root to 0, zero size, ret. Same 41B
// shape as the rowed clear 0x00357416. Callers at 0x002D0142 0x0033BD65
// 0x0033D38E unblocks 0x0033BD50 0x002D0136 0x0033D331.
struct Rva002CF2D5Node
{
	unsigned char m_pad00[8];
	Rva002CF2D5Node *m_left;
	Rva002CF2D5Node *m_right;
};

struct Rva002CF2D5
{
	void rva002CF2D5(Rva002CF2D5Node *x);
};

struct Rva002CF7B5Header
{
	unsigned char m_pad00[4];
	Rva002CF2D5Node *m_root;
	void *m_left;
	void *m_right;
};

struct Rva002CF7B5
{
	Rva002CF7B5Header *m_header;
	int m_size;
	void rva002CF7B5();
};

void Rva002CF7B5::rva002CF7B5()
{
	if (m_size != 0) {
		((Rva002CF2D5 *)this)->rva002CF2D5(m_header->m_root);
		m_header->m_left = m_header;
		m_header->m_root = 0;
		m_header->m_right = m_header;
		m_size = 0;
	}
}
