// cl: /MD
// ?rva002D02FD@Rva002D02FD@@QAEXXZ @0x002D02FD 41B.
// Tree clear: if size at +4 !=0 erase root at header+4 via rowed 0x002CFD61,
// reset header left/right to self and root to 0, zero size, ret. Same 41B
// shape as the rowed clear 0x002CF807. Callers at 0x002D0873 0x0033D01F
// 0x0033DBCD unblocks 0x002D0867 0x0033D00A 0x0033DB2F.
struct Rva002CFD61Node
{
	unsigned char m_pad00[8];
	Rva002CFD61Node *m_left;
	Rva002CFD61Node *m_right;
};

struct Rva002CFD61
{
	void rva002CFD61(Rva002CFD61Node *x);
};

struct Rva002D02FDHeader
{
	unsigned char m_pad00[4];
	Rva002CFD61Node *m_root;
	void *m_left;
	void *m_right;
};

struct Rva002D02FD
{
	Rva002D02FDHeader *m_header;
	int m_size;
	void rva002D02FD();
};

void Rva002D02FD::rva002D02FD()
{
	if (m_size != 0) {
		((Rva002CFD61 *)this)->rva002CFD61(m_header->m_root);
		m_header->m_left = m_header;
		m_header->m_root = 0;
		m_header->m_right = m_header;
		m_size = 0;
	}
}
