// cl: /MD
// ?rva002CF807@Rva002CF807@@QAEXXZ @0x002CF807 41B.
// Tree clear: if size at +4 !=0 erase root at header+4 via rowed 0x002CF32F,
// reset header left/right to self and root to 0, zero size, ret. Same 41B
// shape as the rowed clear 0x002CF7DE. Callers at 0x002D0228 0x0033BDD5
// unblocks 0x0033BDC0 0x002D021C.
struct Rva002CF32FNode
{
	unsigned char m_pad00[8];
	Rva002CF32FNode *m_left;
	Rva002CF32FNode *m_right;
};

struct Rva002CF32F
{
	void rva002CF32F(Rva002CF32FNode *x);
};

struct Rva002CF807Header
{
	unsigned char m_pad00[4];
	Rva002CF32FNode *m_root;
	void *m_left;
	void *m_right;
};

struct Rva002CF807
{
	Rva002CF807Header *m_header;
	int m_size;
	void rva002CF807();
};

void Rva002CF807::rva002CF807()
{
	if (m_size != 0) {
		((Rva002CF32F *)this)->rva002CF32F(m_header->m_root);
		m_header->m_left = m_header;
		m_header->m_root = 0;
		m_header->m_right = m_header;
		m_size = 0;
	}
}
