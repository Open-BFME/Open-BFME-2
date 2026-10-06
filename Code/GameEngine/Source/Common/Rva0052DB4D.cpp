// cl: /DNDEBUG /MD
// ?rva0052DB4D@Rva0052DB4D@@QAE_NH@Z, retail 0x0052DB4D, 38 bytes.
// Single-list mismatch search returning true on first id not equal to arg.
// Evidence: unlock lane; no callees; callers 0x002EFF09 0x002F051D.
struct Rva0052DB4DObj
{
	char _pad00[0x74];
	int m_74;
};

struct Rva0052DB4DNode
{
	Rva0052DB4DNode *m_next;
	char _pad04[4];
	void *m_8;
};

struct Rva0052DB4DHead
{
	char _pad00[0x1c];
	Rva0052DB4DNode *m_1c;
};

class Rva0052DB4D
{
public:
	bool rva0052DB4D(int arg);
private:
	Rva0052DB4DHead *m_0;
};

bool Rva0052DB4D::rva0052DB4D(int arg)
{
	Rva0052DB4DHead *h = m_0;
	if (!h)
		return false;
	for (Rva0052DB4DNode *n = h->m_1c; n; n = n->m_next)
	{
		if (((Rva0052DB4DObj *)n->m_8)->m_74 != arg)
			return true;
	}
	return false;
}
